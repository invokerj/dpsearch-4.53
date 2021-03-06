/* include/dps_config.h.  Generated from dps_config.h.in by configure.  */
/* include/dps_config.h.in.  Generated automatically from configure.in by autoheader.  */
/* --- BEGIN 'top' portion of acconfig.h --- */

/* acconfig.h is here to make autoheader happy and smile. -kir */

#ifndef _DPS_CONFIG_H
#define _DPS_CONFIG_H

#if defined(APACHE1) || defined(APACHE2)
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_main.h"
#include "http_protocol.h"
#ifdef APACHE2
#include "http_request.h"
#endif
#include "util_script.h"
#ifdef APACHE2
#include "http_connection.h"
/*#include "apr_strings.h"*/
#endif
#endif

/* --- END 'top' portion of acconfig.h --- */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef mode_t */

/* Define to `long' if <sys/types.h> doesn't define.  */
/* #undef off_t */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef pid_t */

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
/* #undef WORDS_BIGENDIAN */

/* Define if you have tm_gmtoff in struct tm */
#define HAVE_TM_GMTOFF 1

/* Define if you have POSIX type signal handling routines */
#define HAVE_POSIX_SIGNALS 1

/* Define if you have union semun in sys/sem.h */
#define HAVE_UNION_SEMUN 1

/* Define if you want to use syslog for logging indexer messages */
#define WITH_SYSLOG 1

/* Define if you want tracing for debugging */
/* #undef WITH_TRACE */

/* Define if you want Google-like grouping by site */
#define WITH_GOOGLEGRP 1

/* Define if you want multi DBAddr support */
#define WITH_MULTIDBADDR 1

/* Define what method of relevance calculation to be used. */
#define FULL_RELEVANCE 1
/* #undef FAST_RELEVANCE */
/* #undef ULTRA_RELEVANCE */

/* Define if you want to take hops into account for the Neo Popularity Rank calculation */
/* #undef WITH_POPHOPS */

/* hops factor in the Neo Popularity Rank calculation */
#define DPS_POPHOPS_FACTOR 0.1

/* Define if you want average word distance in relevancy calculation */
#define WITH_REL_DISTANCE 1

/* Define if you want average word position in relevncy calculation */
#define WITH_REL_POSITION 1

/* Define if you want word count in relevancy calculation */
#define WITH_REL_WRDCOUNT 1

/* Define if you want to track relevance commands */
#define WITH_REL_TRACK 1

/* best first word position for relevancy calculation */
#define DPS_BEST_POSITION 13

/* best average word position for relevancy calculation */
#define DPS_AVG_POSITION 390

/* best average distance between words for relevancy calculation */
#define DPS_AVG_DISTANCE 20

/* best words count for relevancy calculation */
#define DPS_BEST_WRD_CNT 30

/* word counts factor for relevancy calculation */
#define DPS_WRD_CNT_FACTOR 3.5

/* word less counts factor for relevancy calculation */
#define DPS_LESS_WRD_CNT_FACTOR 70.5

/* first word position factor for relevancy calculation */
#define DPS_POSITION_FACTOR 1.5

/* first word less position factor for relevancy calculation */
#define DPS_LESS_POSITION_FACTOR 0.31

/* first word distance factor for relevancy calculation */
#define DPS_DISTANCE_FACTOR 25

/* first word less distance factor for relevancy calculation */
#define DPS_LESS_DISTANCE_FACTOR 1.0

/* border value for non-uniform word count distribution in relevancy calculation */
#define DPS_UNICNT_BORDER 10

/* non-uniform word count distribution factor for relevancy calculation */
#define DPS_UNICNT_FACTOR 2000

/* non-uniform word less count distribution factor for relevancy calculation */
#define DPS_LESS_UNICNT_FACTOR 20

/* Define if you want to use external parser */
#define WITH_PARSER 1

/* Define if you want to use GNU libidn */
/* #undef WITH_IDN */

/* Define if you want to use Solaris libidnkit */
/* #undef WITH_IDNKIT */

/* Define if you want mp3 id3 tags support */
#define WITH_MP3 1

/* Define if you want to support file:// URL schema */
#define WITH_FILE 1

/* Define if you want to support http:// URL schema */
#define WITH_HTTP 1

/* Define if you want to support https:// URL schema */
#define WITH_HTTPS 1

/* Define if you want to support ftp:// URL schema */
#define WITH_FTP 1

/* Define if you want to support news:// URL schema */
#define WITH_NEWS 1

/* Define if you want to use MySQL */
#define HAVE_DP_MYSQL 1

/* Define if you want to use PostgreSQL */
#define HAVE_DP_PGSQL 1

/* Define if you want to use mSQL */
/* #undef HAVE_DP_MSQL */

/* Define if you want to use iODBC */
/* #undef HAVE_IODBC */

/* Define if you want to use unixODBC */
/* #undef HAVE_UNIXODBC */

/* Define if you want to use IBM DB2 */
/* #undef HAVE_DB2 */

/* Define if you want to use Solid SQL Server */
/* #undef HAVE_SOLID */

/* Define if you want to use OpenLink ODBC (Virtuoso) */
/* #undef HAVE_VIRT */

/* Define if you want to use EasySoft ODBC */
/* #undef HAVE_EASYSOFT */

/* Define if you want to use SAPDB ODBC library */
/* #undef HAVE_SAPDB */

/* Define if you want to use Interbase SQL Server */
/* #undef HAVE_IBASE */

/* Define if you want to use CT-LIB SyBase SQL Server */
/* #undef HAVE_CTLIB */

/* Define if you want to use sqlite  */
/* #undef HAVE_SQLITE */

/* Define if you want to use sqlite3 */
/* #undef HAVE_SQLITE3 */

/* Define if you want to use Oracle 8 SQL Server */
/* #undef HAVE_ORACLE8 */

/* Define if you want to use Oracle 7 SQL Server */
/* #undef HAVE_ORACLE7 */

/* Define VERSION_ID */
#define DPS_VERSION_ID 453

/* Define DPS_DBTYPE */
#define DPS_DBTYPE "mysql-pqsql"

/* Define if you havnt socklen_t type */
/* #undef socklen_t */

/* Define if you want DMALLOC */
/* #undef DMALLOC */

/* Define if you want Boehm's garbage collector support */
/* #undef BOEHMGC */

/* Define if you want internal memory debugger based on Electric Fence 2.2 */
/* #undef EFENCE */

/* Define if you want internal file handlers debugger */
/* #undef FILENCE */

/* Define if you want HTTP Content Encoding support */
#define HAVE_ZLIB 1

/* Define if you want readline support */
/* #undef HAVE_READLINE */

/* Define if you want Chinese support */
#define HAVE_CHARSET_chinese 1

/* Define if you want Japanese support */
#define HAVE_CHARSET_japanese 1

/* Define if you want Korean euc-kr support */
#define HAVE_CHARSET_euc_kr 1

/* Define if you want gujarati support */
#define HAVE_CHARSET_gujarati 1

/* Define if you want tscii support */
#define HAVE_CHARSET_tscii 1

/* Define if you want ChaSen support */
/* #undef CHASEN */

/* Define if you want MeCab support */
/* #undef MECAB */

/* The number of bytes in a char*.  */
#define SIZEOF_CHARP 4

/* The number of bytes in a void*.  */
#define SIZEOF_VOIDP 4

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 8

/* The number of bytes in a short.  */
#define SIZEOF_SHORT 2

/* Define if you have the bzero function.  */
#define HAVE_BZERO 1

/* Define if you have the hstrerror function.  */
#define HAVE_HSTRERROR 1

/* Define if you have timegm function */
#define HAVE_TIMEGM 1

/* Define if you have the mergesort function.  */
#define HAVE_MERGESORT 1

/* Define if you have the heapsort function.  */
#define HAVE_HEAPSORT 1

/* Define if you have the putenv function.  */
#define HAVE_PUTENV 1

/* Define if you have the regcomp function.  */
#define HAVE_REGCOMP 1

/* Define if you have the setenv function.  */
#define HAVE_SETENV 1

/* Define if you have the setproctitle function.  */
#define HAVE_SETPROCTITLE 1

/* Define if you have the snprintf function.  */
#define HAVE_SNPRINTF 1

/* Define if you have the socket function.  */
#define HAVE_SOCKET 1

/* Define if you have the strcasecmp function.  */
#define HAVE_STRCASECMP 1

/* Define if you have the strcasestr function.  */
#define HAVE_STRCASESTR 1

/* Define if you have the strdup function.  */
#define HAVE_STRDUP 1

/* Define if you have the strncasecmp function.  */
#define HAVE_STRNCASECMP 1

/* Define if you have the strndup function.  */
/* #undef HAVE_STRNDUP */

/* Define if you have the strnlen function.  */
/* #undef HAVE_STRNLEN */

/* Define if you have the strstr function.  */
#define HAVE_STRSTR 1

/* Define if you have the strtok_r function.  */
#define HAVE_STRTOK_R 1

/* Define if you have the unsetenv function.  */
#define HAVE_UNSETENV 1

/* Define if you have the daemon function.  */
#define HAVE_DAEMON 1

/* Define if you have the vsnprintf function.  */
#define HAVE_VSNPRINTF 1

/* Define if you have the getaddrinfo function. */
#define HAVE_GETADDRINFO 1

/* Define if you have the inet_net_pton function. */
#define HAVE_INET_NET_PTON 1

/* Define if you have strerror_r function. */
#define HAVE_STRERROR_R 1

/* Define if you have gmtime_r function. */
#define HAVE_GMTIME_R 1

/* Define to use the three-argument variant of gethostbyname_r */
/* #undef HAVE_GETHOSTBYNAME_R_3 */

/* Define to use the five-argument variant of gethostbyname_r */
/* #undef HAVE_GETHOSTBYNAME_R_5 */

/* Define to use the six-argument variant of gethostbyname_r */
#define HAVE_GETHOSTBYNAME_R_6 1

/* Define if you have the pthread_setconcurrency function. */
#define HAVE_PTHREAD_SETCONCURRENCY_PROTO 1

/* Define if you have the pthread_yeild function. */
#define HAVE_PTHREAD_YIELD_PROTO 1

/* Define if you have the thr_setconcurrency function. */
/* #undef HAVE_THR_SETCONCURRENCY_PROTO */

/* Define if you have the <arpa/inet.h> header file.  */
#define HAVE_ARPA_INET_H 1

/* Define if you have the <arpa/nameser.h> header file.  */
#define HAVE_ARPA_NAMESER_H 1

/* Define if you have the <fcntl.h> header file.  */
#define HAVE_FCNTL_H 1

/* Define if you have the <getopt.h> header file.  */
/* #undef HAVE_GETOPT_H */

/* Define if you have the <libutil.h> header file.  */
#define HAVE_LIBUTIL_H 1

/* Define if you have the <netdb.h> header file.  */
#define HAVE_NETDB_H 1

/* Define if you have the <netinet/in.h> header file.  */
#define HAVE_NETINET_IN_H 1

/* Define if you have the <netinet/in_systm.h> header file.  */
#define HAVE_NETINET_IN_SYSTM_H 1

/* Define if you have the <netinet/ip.h> header file.  */
#define HAVE_NETINET_IP_H 1

/* Define if you have the <netinet/tcp.h> header file.  */
#define HAVE_NETINET_TCP_H 1

/* Define if you have the <resolv.h> header file.  */
#define HAVE_RESOLV_H 1

/* Define if you have the <select.h> header file.  */
/* #undef HAVE_SELECT_H */

/* Define if you have the <sched.h> header file.  */
#define HAVE_SCHED_H 1

/* Define if you have the <sys/ioctl.h> header file.  */
#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/mman.h> header file.  */
#define HAVE_SYS_MMAN_H 1

/* Define if you have Posix style shared memory interface */
#define HAVE_SHAREDMEM_POSIX 1

/* Define if you have the <sys/shm.h> header file.  */
#define HAVE_SYS_SHM_H 1

/* Define if you have SysV style shared memory interface */
/* #undef HAVE_SHAREDMEM_SYSV */

/* Define if you have the <sys/msg.h> header file. */
#define HAVE_SYS_MSG_H 1

#if 0
/* Define if you have the <semaphore.h> header file. */
#define HAVE_SEMAPHORE_H 1
#endif

/* Define if you have the <sys/sem.h> header file. */
#define HAVE_SYS_SEM_H 1

#ifndef HAVE_SYS_SEM_H
/* Define if you have the <semaphore.h> header file. */
#define HAVE_SEMAPHORE_H 1
#endif


/* Define if you have the <sys/ipc.h> header file.  */
#define HAVE_SYS_IPC_H 1

/* Define if you have the <sys/param.h> header file.  */
#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/select.h> header file.  */
#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/socket.h> header file.  */
#define HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/times.h> header file.  */
#define HAVE_SYS_TIMES_H 1

/* Define if you have the <sys/wait.h> header file.  */
#define HAVE_SYS_WAIT_H 1

/* Define if you have the <sys/sysctl.h> header file. */
#define HAVE_SYS_SYSCTL_H 1

/* Define if you have the <tre/regex.h> header file. */
/* #undef HAVE_TRE_REGEX_H */

/* Define if you have the <syslog.h> header file.  */
#define HAVE_SYSLOG_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */

/* Define if you have the bind library (-lbind) */
/* #undef HAVE_LIBBIND */

/* Define if you have the dns library (-ldns) */
/* #undef HAVE_LIBDNS */

/* Define if you have the ares library (-lares) */
/* #undef HAVE_LIBARES */

/* Define if you have the c-ares library (-lcares) */
#define HAVE_LIBCARES 1

/* Define if you have the aspell library (libaspell) */
/* #undef HAVE_ASPELL */

/* Define if you have the libextractor library */
#define HAVE_LIBEXTRACTOR 1

/* Name of package */
#define PACKAGE "dpsearch"

/* Version number of package */
#ifndef VERSION
#define VERSION "4.53"
#endif

/* syslog facility */
/* #undef LOG_FACILITY */

/* libparanoia usage */
/* #undef WITH_PARANOIA */

/* compatible with old hash function */
#define WITH_OLDHASH 1

/* cache mode version of mod_dpsearch */
#if defined(APACHE1) || defined(APACHE2)
/* #undef APACHE_CACHEONLY */
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to enable large file support on some Linuxes, Red Hat 8.0, for example (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */


/* --- BEGIN 'bottom' portion from acconfig.h --- */

/* ODBC Library */
#if (HAVE_IODBC|| HAVE_UNIXODBC||HAVE_SOLID||HAVE_VIRT||HAVE_EASYSOFT||HAVE_SAPDB||HAVE_DB2)
#define HAVE_ODBC 1
#endif

/* Backend */
#if (HAVE_ODBC||HAVE_DP_MYSQL||HAVE_DP_PGSQL||HAVE_DP_MSQL||HAVE_IBASE||HAVE_ORACLE8||HAVE_ORACLE7||HAVE_CTLIB||HAVE_SQLITE||HAVE_SQLITE3) && !defined(APACHE_CACHEONLY)
#define HAVE_SQL 1
#endif

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

#include <sys/types.h>




#define __C_LINK
#define __DPSCALL

#define DPSSLASH		'/'
#define DPSSLASHSTR		"/"
#define DPSSLEEP(x)		sleep(x)
#define DPS_MSLEEP(x)		usleep(1000*(x))
#define dps_closesocket(x)		close(x)
#define DPS_IWRITE		0644

#if SIZEOF_SHORT == 2
typedef unsigned short dps_uint2;
#elif SIZEOF_INT == 2
typedef unsigned int dps_uint2;
#else
typedef unsigned int dps_uint2;
#endif

#if SIZEOF_SHORT == 4
typedef short dpshash32_t;
typedef unsigned short dps_uint4;
typedef short dps_int4;
#elif SIZEOF_INT == 4
typedef int dpshash32_t;
typedef unsigned int dps_uint4;
typedef int dps_int4;
#else
typedef long dpshash32_t;
typedef unsigned long dps_uint4;
typedef long dps_int4;
#endif

#if SIZEOF_INT == 8
typedef unsigned int dpshash64_t;
typedef unsigned int dps_uint8;
#elif SIZEOF_LONG == 8
typedef unsigned long dpshash64_t;
typedef unsigned long dps_uint8;
#else
typedef unsigned long long dpshash64_t;
typedef unsigned long long dps_uint8;
#endif

#if (SIZEOF_CHARP == SIZEOF_INT)
#define SDPALIGN int
#elif (SIZEOF_CHARP == SIZEOF_LONG)
#define SDPALIGN long
#elif (SIZEOF_CHARP == SIZEOF_SHORT)
#define SDPALIGN short
#else
#define SDPALIGN long long
#endif

#if (SIZEOF_VOIDP == SIZEOF_INT)
#define DPS_PNTYPE unsigned int
#elif (SIZEOF_VOIDP == SIZEOF_LONG)
#define DPS_PNTYPE unsigned long
#elif (SIZEOF_VOIDP == SIZEOF_SHORT)
#define DPS_PNTYPE short
#else
#define DPS_PNTYPE unsigned long long
#endif



typedef dps_int4 urlid_t;
typedef dps_uint4 dpscrc32_t;
typedef dps_uint4 dpsunicode_t;
typedef unsigned int dps_word;
typedef unsigned int dps_uintptr_t;


#define HT_CHAR (char)9
#define NL_CHAR (char)10
#define CR_CHAR	(char)13
#define HT_INT 	(int)9
#define NL_INT 	(int)10
#define CR_INT 	(int)13



#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define __USE_GNU
#endif

/* For strtok_r() */
#ifndef _REENTRANT
#define _REENTRANT
#endif


#ifndef dps_max
#define dps_max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef dps_min
#define dps_min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#include "dps_filence.h"


#ifdef EFENCE

#include "dps_efence.h"

#elif defined(BOEHMGC)

#include <stdlib.h>

#define GC_DEBUG
#include "gc.h"
#define malloc(n) GC_MALLOC(n)
#define calloc(m,n) GC_MALLOC((m)*(n))
#define free(p) GC_FREE(p)
#define realloc(p,n) GC_REALLOC((p),(n))

#define DpsMalloc(n) GC_MALLOC(n)
#define DpsCalloc(m,n) GC_MALLOC((m)*(n))
#define DpsFree(p) GC_FREE(p)
#define DpsRealloc(p,n) GC_REALLOC((p),(n))

#define CHECK_LEAKS() GC_gcollect()
#define DpsStrdup(x)     _DpsStrdup(x)
extern char * _DpsStrdup(const char *str);

#else

extern void *DpsRealloc(void *p, size_t size);

#define DpsFree free
#define DpsMalloc malloc
#define DpsCalloc calloc
#define DpsValloc valloc
#define DpsStrdup _DpsStrdup
#define DpsStrndup _DpsStrndup

#endif /* EFENCE */


#define DpsSort qsort

#ifdef HAVE_MERGESORT
#define DpsPreSort mergesort
#elif defined(HAVE_HEAPSORT)
#define DpsPreSort heapsort
#else
#define DpsPreSort qsort
#endif


#ifdef WITH_PARANOIA
#define DpsViolationExit(h,A) _DpsViolationExit(A, __FILE__, __LINE__, h)
#define DpsViolationCheck(h,A) _DpsViolationCheck(A,__FILE__, __LINE__, h)
extern void *DpsViolationEnter(void *);
extern void _DpsViolationExit(void*, const char*, int, int h);
extern void _DpsViolationCheck(void*, const char*, int, int h);
#endif






#endif /* _DPS_CONFIG_H */
/* --- END 'bottom' portion from acconfig.h --- */
