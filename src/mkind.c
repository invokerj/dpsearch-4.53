/* Copyright (C) 2003-2009 Datapark corp. All rights reserved.
   Copyright (C) 2000-2002 Lavtech.com corp. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/

#include "dpsearch.h"
#include "dps_mkind.h"
#include "dps_carry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
              
#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_MMAN_H
#include <sys/mman.h>
#elif HAVE_SYS_SHM_H
#include <sys/shm.h>
#endif

#define DPS_INDEX_CATEGORY     0
#define DPS_INDEX_TAG          1
#define DPS_INDEX_TIME_HOUR    2
#define DPS_INDEX_TIME_MIN     3
#define DPS_INDEX_HOSTNAME     4
#define DPS_INDEX_LANGUAGE     5
#define DPS_INDEX_SITEID       6
#define DPS_INDEX_CONTENT_TYPE 7

#ifdef O_BINARY
#define DPS_BINARY O_BINARY
#else
#define DPS_BINARY 0
#endif


static int cmp_ind8(const DPS_UINT8URLID *c1, const DPS_UINT8URLID *c2) {
     if (c1->hi < c2->hi) return -1;
     if (c1->hi > c2->hi) return 1;
     if (c1->lo < c2->lo) return -1;
     if (c1->lo > c2->lo) return 1;
     if (c1->url_id < c2->url_id) return -1;
     if (c1->url_id > c2->url_id) return 1;
     return 0;
}

static int cmp_ind4(const DPS_UINT4URLID *c1, const DPS_UINT4URLID *c2) {
     if (c1->val < c2->val) return -1;
     if (c1->val > c2->val) return 1;
     if (c1->url_id < c2->url_id) return -1;
     if (c1->url_id > c2->url_id) return 1;
     return 0;
}

static void ClearIndex4(DPS_UINT4URLIDLIST *L) {
     if (L->mapped) {
#ifdef HAVE_SHAREDMEM_POSIX
       if (munmap(L->Item, (L->nitems + 1) * sizeof(DPS_UINT4URLID))) {
	 fprintf(stderr, "Can't shmdt '%s': %s\n", L->shm_name, strerror(errno));
       }
#elif defined(HAVE_SHAREDMEM_SYSV)
       if (shmdt(L->Item)) {
	 fprintf(stderr, "Can't shmdt '%s': %s\n", L->shm_name, strerror(errno));
       }
#endif       
       unlink(L->shm_name);
     } else {
       DPS_FREE(L->Item);
     }
     bzero(L, sizeof(DPS_UINT4URLIDLIST));
}

static void ClearIndex8(DPS_UINT8URLIDLIST *L) {
  DPS_FREE(L->Item);
  bzero(L, sizeof(DPS_UINT8URLIDLIST));
}

static int MakeNestedIndex(DPS_AGENT *Indexer, DPS_UINT8URLIDLIST *L, const char *lim_name, DPS_DB *db) {
     DPS_ENV   *Conf = Indexer->Conf;
     size_t    k, prev;
     urlid_t   *data=NULL;
     DPS_UINT8_POS_LEN *ind=NULL;
     size_t    mind=1000, nind=0, ndata;
     char fname[PATH_MAX];
     int  dat_fd=0, ind_fd=0;
     int  rc=DPS_OK;
     const char	*vardir = (db->vardir) ? db->vardir : DpsVarListFindStr(&Conf->Vars, "VarDir", DPS_VAR_DIR);
     
     if(!L->Item)return(1);
     
     if (L->nitems > 1) DpsSort(L->Item, L->nitems, sizeof(DPS_UINT8URLID), (qsort_cmp)cmp_ind8);
     
     data = (urlid_t*)DpsMalloc((L->nitems + 1) * sizeof(urlid_t));
     if(!data){
       DpsLog(Indexer, DPS_LOG_ERROR, "Can't alloc %d bytes [%s:%d]", (L->nitems + 1) * sizeof(urlid_t), __FILE__, __LINE__);
       goto err1;
     }
     ind=(DPS_UINT8_POS_LEN*)DpsMalloc(mind*sizeof(DPS_UINT8_POS_LEN));
     if(!ind){
       DpsLog(Indexer, DPS_LOG_ERROR, "Can't alloc %d bytes [%s:%d]", mind * sizeof(DPS_UINT8_POS_LEN), __FILE__, __LINE__);
       goto err1;
     }
     prev=0;
     for(k=0; k < L->nitems; k++) {
          data[k] = L->Item[k].url_id;
          if((k == L->nitems-1) || (L->Item[k].hi != L->Item[prev].hi) || (L->Item[k].lo != L->Item[prev].lo)) {
               if(nind==mind){
                    mind+=1000;
                    ind=(DPS_UINT8_POS_LEN*)DpsRealloc(ind,mind*sizeof(DPS_UINT8_POS_LEN));
                    if(!ind) {
		      DpsLog(Indexer, DPS_LOG_ERROR, "Can't alloc %d bytes [%s:%d]", mind * sizeof(DPS_UINT8_POS_LEN), __FILE__, __LINE__);
		      goto err1;
                    }
               }
               /* Fill index */
               ind[nind].hi = L->Item[prev].hi;
               ind[nind].lo = L->Item[prev].lo;
               ind[nind].pos = prev * sizeof(*data);
               if (k == L->nitems - 1) ind[nind].len = (k - prev + 1) * sizeof(*data);
               else ind[nind].len = (k - prev) * sizeof(*data);
               DpsLog(Indexer, DPS_LOG_DEBUG, "%08X%08X - %d %d\n", ind[nind].hi, ind[nind].lo, (int)ind[nind].pos, ind[nind].len);
               nind++;
               
               prev=k;
          }
     }
     ndata = L->nitems;
     ClearIndex8(L);
     
     dps_snprintf(fname,sizeof(fname)-1,"%s%c%s%c%s.dat", vardir,DPSSLASH, DPS_TREEDIR,DPSSLASH, lim_name);
     if((dat_fd = DpsOpen3(fname, O_CREAT | O_WRONLY | O_TRUNC | DPS_BINARY, DPS_IWRITE)) < 0) {
       DpsLog(Indexer, DPS_LOG_ERROR, "Can't open '%s': %s [%s:%d]", fname, strerror(errno), __FILE__, __LINE__);
       goto err1;
     }
     DpsWriteLock(dat_fd);
     if((ndata * sizeof(*data)) != (size_t)write(dat_fd, data, ndata * sizeof(*data))) {
       DpsLog(Indexer, DPS_LOG_ERROR, "Can't write '%s': %s [%s:%d]", fname, strerror(errno), __FILE__, __LINE__);
       goto err1;
     }
     DpsUnLock(dat_fd);
     DpsClose(dat_fd);
     DPS_FREE(data);

     dps_snprintf(fname,sizeof(fname)-1,"%s%c%s%c%s.ind", vardir, DPSSLASH,DPS_TREEDIR, DPSSLASH, lim_name);
     if((ind_fd = DpsOpen3(fname, O_CREAT | O_WRONLY | O_TRUNC | DPS_BINARY, DPS_IWRITE)) < 0) {
       DpsLog(Indexer, DPS_LOG_ERROR, "Can't open '%s': %s [%s:%d]", fname, strerror(errno), __FILE__, __LINE__);
       goto err1;
     }
     DpsWriteLock(ind_fd);
     if((nind*sizeof(DPS_UINT8_POS_LEN)) != (size_t)write(ind_fd,ind,nind*sizeof(DPS_UINT8_POS_LEN))){
       DpsLog(Indexer, DPS_LOG_ERROR, "Can't write '%s': %s [%s:%d]", fname, strerror(errno), __FILE__, __LINE__);
          goto err1;
     }
     DpsUnLock(ind_fd);
     DpsClose(ind_fd);
     DPS_FREE(ind);
     
     return(0);
     
err1:
     ClearIndex8(L);
     DPS_FREE(data);
     DPS_FREE(ind);
     if(dat_fd) DpsClose(dat_fd);
     if(ind_fd) DpsClose(ind_fd);
     return(1);
}

static int MakeLinearIndex(DPS_AGENT *Indexer, DPS_UINT4URLIDLIST *L, const char *lim_name, DPS_DB *db) {
     DPS_ENV *Conf = Indexer->Conf;
     size_t    k,prev;
     urlid_t   *data = NULL;
     DPS_UINT4_POS_LEN *ind=NULL;
     size_t    mind=1000,nind=0, ndata;
     char fname[PATH_MAX];
     int  dat_fd=0, ind_fd=0, rc;
     const char	*vardir = (db->vardir) ? db->vardir : DpsVarListFindStr(&Conf->Vars, "VarDir", DPS_VAR_DIR);

     if(!L->Item)return(1);
     
     if (L->nitems > 1) DpsSort(L->Item, L->nitems, sizeof(DPS_UINT4URLID), (qsort_cmp)cmp_ind4);
     
     data = (urlid_t*)DpsMalloc((L->nitems + 1) * sizeof(*data));
     if(!data){
          fprintf(stderr,"Error1: %s\n",strerror(errno));
          goto err1;
     }
     ind=(DPS_UINT4_POS_LEN*)DpsMalloc(mind*sizeof(DPS_UINT4_POS_LEN));
     if(!ind){
          fprintf(stderr,"Error2: %s\n",strerror(errno));
          goto err1;
     }
     prev=0;
     for(k=0; k < L->nitems; k++) {
          data[k] = L->Item[k].url_id;
          if((k == L->nitems-1) || (L->Item[k].val != L->Item[prev].val)) {
               if(nind==mind){
                    mind+=1000;
                    ind=(DPS_UINT4_POS_LEN*)DpsRealloc(ind,mind*sizeof(DPS_UINT4_POS_LEN));
                    if(!ind){
                         fprintf(stderr,"Error3: %s\n",strerror(errno));
                         goto err1;
                    }
               }
               /* Fill index */
               ind[nind].val = L->Item[prev].val;
               ind[nind].pos = prev * sizeof(*data);
               if (k == L->nitems - 1) ind[nind].len = (k - prev + 1) * sizeof(*data);
               else ind[nind].len = (k - prev) * sizeof(*data);
               DpsLog(Indexer, DPS_LOG_DEBUG, "%d - pos:%x len:%d\n", ind[nind].val, (int)ind[nind].pos, ind[nind].len);
               nind++;
               
               prev=k;
          }
     }
     ndata = L->nitems;
     ClearIndex4(L);
    
     dps_snprintf(fname,sizeof(fname),"%s%c%s%c%s.dat", vardir,DPSSLASH, DPS_TREEDIR, DPSSLASH, lim_name);
     if((dat_fd = DpsOpen3(fname, O_CREAT | O_WRONLY | O_TRUNC | DPS_BINARY, DPS_IWRITE)) < 0) {
          fprintf(stderr,"Can't open '%s': %s\n",fname,strerror(errno));
          goto err1;
     }
     DpsWriteLock(dat_fd);
     if((ndata * sizeof(*data)) != (size_t)write(dat_fd, data, ndata * sizeof(*data))) {
          fprintf(stderr,"Can't write '%s': %s\n",fname,strerror(errno));
          goto err1;
     }
     DpsUnLock(dat_fd);
     DpsClose(dat_fd);
     DPS_FREE(data);

     dps_snprintf(fname,sizeof(fname),"%s%c%s%c%s.ind", vardir,DPSSLASH, DPS_TREEDIR, DPSSLASH, lim_name);
     if((ind_fd = DpsOpen3(fname, O_CREAT | O_WRONLY | O_TRUNC | DPS_BINARY, DPS_IWRITE)) < 0) {
          fprintf(stderr,"Can't open '%s': %s\n",fname,strerror(errno));
          goto err1;
     }
     DpsWriteLock(ind_fd);
     if((nind*sizeof(DPS_UINT4_POS_LEN)) != (size_t)write(ind_fd,ind,nind*sizeof(DPS_UINT4_POS_LEN))){
          fprintf(stderr,"Can't write '%s': %s\n",fname,strerror(errno));
          goto err1;
     }
     DpsUnLock(ind_fd);
     DpsClose(ind_fd);
     DPS_FREE(ind);
     
     return(0);
     
err1:
     ClearIndex4(L);
     DPS_FREE(data);
     DPS_FREE(ind);
     if(dat_fd) DpsClose(dat_fd);
     if(ind_fd) DpsClose(ind_fd);
     return(1);
}


__C_LINK int __DPSCALL DpsCacheMakeIndexes(DPS_AGENT *Indexer, DPS_DB *db) {
  DPS_UINT8URLIDLIST  L8;
  DPS_UINT4URLIDLIST  L4;
  DPS_VARLIST *v = &Indexer->Conf->Vars;
  size_t i, r;
  char *ind, *nm, *lfname;

  bzero(&L4, sizeof(DPS_UINT4URLIDLIST));
  bzero(&L8, sizeof(DPS_UINT8URLIDLIST));
  
  r = (size_t) 'l';
  for (i = 0; i < v->Root[r].nvars; i++) {
    if (!strncasecmp("Limit-", v->Root[r].Var[i].name, 6)) {
      ind = v->Root[r].Var[i].val;
      lfname = v->Root[r].Var[i].name;
      nm = lfname + 6;
      if (!strcasecmp(ind, "category")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Category index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating category index");
	if (DPS_OK == DpsLimit8(Indexer, &L8, "Category",  DPS_IFIELD_TYPE_HEX8STR, db)) {
	  MakeNestedIndex(Indexer, &L8, DPS_LIMFNAME_CAT, db);
	}

      } else if (!strcasecmp(ind, "tag")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Tag index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating tag index");
	if (DPS_OK == DpsLimit4(Indexer, &L4, "Tag",  DPS_IFIELD_TYPE_STRCRC32, db)) {
	  MakeLinearIndex(Indexer, &L4, DPS_LIMFNAME_TAG, db);
	}

      } else if (!strcasecmp(ind, "link")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Link index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating link index");
	if (DPS_OK == DpsLimit4(Indexer, &L4, "link",  DPS_IFIELD_TYPE_INT, db)) {
	  MakeLinearIndex(Indexer, &L4, DPS_LIMFNAME_LINK, db);
	}

      } else if (!strcasecmp(ind, "time")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Time index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating time index");
	if (DPS_OK == DpsLimit4(Indexer, &L4, "last_mod_time",  DPS_IFIELD_TYPE_HOUR, db)) {
	  MakeLinearIndex(Indexer, &L4, DPS_LIMFNAME_TIME, db);
	}

      } else if (!strcasecmp(ind, "hostname")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Hostname index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating hostname index");
	if (DPS_OK == DpsLimit4(Indexer, &L4, "url",  DPS_IFIELD_TYPE_HOSTNAME, db)) {
	  MakeLinearIndex(Indexer, &L4, DPS_LIMFNAME_HOST, db);
	}

      } else if (!strcasecmp(ind, "language")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Language index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating language index");
	if (DPS_OK == DpsLimit4(Indexer, &L4, "Content-Language",  DPS_IFIELD_TYPE_STR2CRC32, db)) {
	  MakeLinearIndex(Indexer, &L4, DPS_LIMFNAME_LANG, db);
	}

      } else if (!strcasecmp(ind, "content")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Content-Type index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating Content-Type index");
	if (DPS_OK == DpsLimit4(Indexer, &L4, "Content-Type",  DPS_IFIELD_TYPE_STRCRC32, db)) {
	  MakeLinearIndex(Indexer, &L4, DPS_LIMFNAME_CTYPE, db);
	}

      } else if (!strcasecmp(ind, "siteid")) {

	/* To see the URL being indexed in "ps" output on xBSD */
	dps_setproctitle("[%d] Site_id index creation", Indexer->handle);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating Site_id index");
	if (DPS_OK == DpsLimit4(Indexer, &L4, "site_id",  DPS_IFIELD_TYPE_INT, db)) {
	  MakeLinearIndex(Indexer, &L4, DPS_LIMFNAME_SITE, db);
	}

      } else {
	char *buf, *req, *dbaddr;
	DPS_DB ldb, *pdb = &ldb;
	size_t buf_len = dps_strlen(nm) + 16;
	if ((buf = (char*) DpsMalloc(buf_len * sizeof(char))) == NULL) {
	  DpsLog(Indexer, DPS_LOG_ERROR, "Can't alloc %d chars at %s:%d", buf_len, __FILE__, __LINE__);
	  return DPS_ERROR;
	}
	dps_setproctitle("[%d] %s index creation", Indexer->handle, nm);
	DpsLog(Indexer, DPS_LOG_EXTRA, "Creating %s index", nm);
	dps_snprintf(buf, buf_len, "Req-%s", nm);
	req = DpsVarListFindStr(&Indexer->Conf->Vars, buf, NULL);
	if (req != NULL) {
	  dps_snprintf(buf, buf_len, "dbaddr-%s", nm);
	  dbaddr = DpsVarListFindStr(&Indexer->Conf->Vars, buf, NULL);
	  if (dbaddr != NULL) {
	    DpsDBSetAddr(pdb, dbaddr, DPS_OPEN_MODE_READ);
	  } else {
	    pdb = db;
	  }
	  if (!strcasecmp(ind, "nex8str")) {
	    if (DPS_OK == DpsSQLLimit8(Indexer, &L8, req, DPS_IFIELD_TYPE_HEX8STR, pdb)) {
	      MakeNestedIndex(Indexer, &L8, lfname, pdb);
	    }
	  } else {
	    int field_type = DPS_IFIELD_TYPE_INT;
	    if (!strcasecmp(ind, "strcrc32")) field_type = DPS_IFIELD_TYPE_STRCRC32;
	    else if (!strcasecmp(ind, "hour")) field_type = DPS_IFIELD_TYPE_HOUR;
	    else if (!strcasecmp(ind, "hostname")) field_type = DPS_IFIELD_TYPE_HOSTNAME;
	    else if (!strcasecmp(ind, "char2")) field_type = DPS_IFIELD_TYPE_STR2CRC32;
	    else if (!strcasecmp(ind, "int")) field_type = DPS_IFIELD_TYPE_INT;
	    if (DPS_OK == DpsSQLLimit4(Indexer, &L4, req,  field_type, db)) {
	      MakeLinearIndex(Indexer, &L4, lfname, db);
	    }
	  }
	}

      }
      /* To see the URL being indexed in "ps" output on xBSD */
      dps_setproctitle("[%d] Indexes done.", Indexer->handle);
      DpsLog(Indexer, DPS_LOG_EXTRA, "Done");
    }
  }
  return DPS_OK;
}

