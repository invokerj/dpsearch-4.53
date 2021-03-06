<!--variables
DBAddr		searchd://localhost/?label=rutube
StoredocURL     /cgi-bin/storedoc.cgi
LocalCharset 	koi8-r
BrowserCharset  UTF-8
DoExcerpt no

MinWordLength 1
MaxWordLength 64
DetectClones no
DateFormat %d %b %Y
ExcerptSize 128
ExcerptPadding 32
HlBeg <span class="rhl">
HlEnd </span>
GrBeg <!-- -->
GrEnd <!-- -->
Locale ru_RU.UTF-8

ReplaceVar head.lng "Видео @ 43N 39E"
ReplaceVar pages.lng "Страницы"
ReplaceVar main.lng "Поиск видео"
ReplaceVar prev.lng "Пред."
ReplaceVar next.lng "След."
ReplaceVar foot.lng "&nbsp;"
ReplaceVar error.lng "Ошибка!"
ReplaceVar notfound.lng "По данному запросу ничего не найдено."
ReplaceVar SearchFor.lng "Искать"
ReplaceVar otherse.lng "в других поисковых машинах"
ReplaceVar yandex.lng "Яндекс"
ReplaceVar rambler.lng "Рамблер"
ReplaceVar nigma.lng "Нигма"
ReplaceVar 43n39e.ru.lng "Вершки Рунета"

ReplaceVar sortedby.lng "отсортировано по"
ReplaceVar isort.lng "важности"
ReplaceVar rsort.lng "соответствию"
ReplaceVar dsort.lng "дате"
ReplaceVar psort.lng "популярности"

ReplaceVar showndocs.lng "Показаны документы"
ReplaceVar iz.lng "из"
ReplaceVar found.lng "найденных"
ReplaceVar stime.lng "Время поиска"
ReplaceVar sec.lng "сек."
ReplaceVar results.lng "Результаты поиска"
ReplaceVar ToFind.lng "Найти"

-->

<!--top-->
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">
<html lang="ru">
  <head>
    <title>$&(head.lng): $&(q)</title>
    <link href="http://sochi.org.ru/css/therm2.css" rel="stylesheet" type="text/css">
    <link href="http://sochi.org.ru/favicon.ico" rel="shortcut icon" type="image/x-icon">
</head>
<!-- BrowserCharset: $(BrowserCharset) -->
<body id="dir"> 
<table border="0" cellpadding="2" cellspacing="0">
<tr><td><div id="topmenu"><a href="http://www.43n39e.ru/video">$(main.lng)</a></div></td><td rowspan="6" width="160" align="center" valign="top" style="border-left: 1px solid #EEE">
<!-- ads here -->
<iframe src="http://sbe.sochi-info.com/ru.cgi?id=372&amp;net=6" width="88" height="31" frameborder="0" vspace="0" hspace="0" marginwidth="0" marginheight="0" scrolling="no"></iframe>
</td></tr>
<tr><td id="form" class="headruler" align="center" style="background: url(/tdbg2.png) repeat-x #f4f4f4;">
	   <form name="s" method="GET" action="/cgi-bin/search.cgi" enctype="application/x-www-form-urlencoded" style="margin:0; padding:0">
			<INPUT TYPE="hidden" NAME="ps" VALUE="10">
			<INPUT TYPE="hidden" NAME="np" VALUE="0">
			<input type="hidden" name="dt" value="back">
			<input type="hidden" name="sy" value="$*(sy)">
			<input type="hidden" name="sp" value="$*(sp)">
			<input type="hidden" name="s" value="$*(s)">
			<input type="hidden" name="tmplt" value="vi8.htm.ru">
		        <input type="hidden" name="m" value="all">
			<input type="hidden" name="label" value="rutube">
			<input type="hidden" name="GroupBySite" value="no">
			<input type="hidden" name="wf" value="F1F1">
			<table width="100%" border="0" cellpadding="2" cellspacing="0">
			    <tr>
			      <td width="99%" style="vertical-align: middle;">
				  <input class="inputsearch" type="text" name="q" size="60" value="$&(q)" style="width:100%;">
			      </td><td>
				  <input class="inputsearch" type="submit" value="$(ToFind.lng)">
			      </td>
			    </tr>
			    <!--tr>
			      <td class="inputrev">&nbsp;</td>
			    </tr-->
			</table>
	    </form>
</td></tr>
<!--/top-->

<!--bottom-->
<tr><td><br>
<div class="topmenu"><small>$(foot.lng)</small></div></td></tr>
</table>
<!IFNOT NAME="q" CONTENT="">
<small>$(SearchFor.lng) &laquo;$&(q)&raquo; $(otherse.lng):<br>&nbsp;&nbsp;&nbsp;
<a href="http://www.43n39e.ru/cgi-bin/search.cgi?q=$%(q:utf-8)&m=$&(m)&g=$&(g)&sp=$&(sp)&sy=$&(sy)&np=0&GroupBySite=$&(GroupBySite)&s=IRPD&ps=10&wf=F1F1&tmplt=janus.htm.ru">$(43n39e.ru.lng)</a> &#150;
<a href="http://www.google.com/search?ie=UTF-8&amp;hl=en&amp;q=$%(q:utf-8)">Google</a> &#150;
<a href="http://www.yandex.ru/yandsearch?text=$%(q:cp1251)&amp;stype=www">$(yandex.lng)</a> &#150;
<a href="http://search.rambler.ru/cgi-bin/rambler_search?english=0&and=1&words=$%(q:koi8-r)">$(rambler.lng)</a> &#150;
<a href="http://gogo.ru/go?q=$%(q:cp1251)">GoGo</a> &#150;
<a href="http://www.nigma.ru/index.php?0=1&1=1&2=1&3=1&4=1&5=1&6=1&7=1&q=$%(q:cp1251)">$(nigma.lng)</a>
</small>
<!ENDIF>
</body>
</html>
<!--/bottom-->

<!--restop-->
<tr><td style="color: #666"><div align="left" style="float: left">
<small>&nbsp;$(showndocs.lng) <b>$(first)</b>-<b>$(last)</b> $(iz.lng) <b>$(total)</b> $(found.lng).</small>
</div>
<div align="right">
<small>$(stime.lng):&nbsp;<b>$(SearchTime)</b> $(sec.lng)&nbsp;</small>
</div>
</td></tr>
<tr><td valign="bottom">
<table align="center" border="0" cellspacing="0" cellpadding="3"><tr><td>$(pages.lng):</td>$(NL)$(NB)$(NR)</tr></table></td></tr>
<tr><td align="left" valign="middle"><small>&nbsp;$(sortedby.lng):&nbsp;
<!IF NAME="s" CONTENT="DRP">
<a href="$(FirstPage)&s=RPD">$(rsort.lng)</a>&nbsp;|&nbsp;<span class="hl">$(dsort.lng)</span><!ELSE>
<span class="hl">$(rsort.lng)</span>&nbsp;|&nbsp;<a href="$(FirstPage)&s=DRP">$(dsort.lng)</a>
<!ENDIF></small></td></tr>
<tr><td align="left" valign="top">
<!--/restop-->


<!--res-->
<!-- $(DP_ID) -->
<div class="serp1" style="float: left; padding: 0.5em; width: 200px">
<small class="restop"><a class="restop" href="$(url)">$&(title:128)</a></small><br>
<small class="restop"><a class="restop" href="$(url)">
<!IFNOT NAME="ytid" VALUE=""><img src="http://img.youtube.com/vi/$(ytid)/default.jpg" border="0" style="padding: 0.5em; border: #777 1px solid; background-color: #eee"></a> 
<!ELSEIFNOT NAME="myvi" VALUE=""><!IF NAME="ruid" VALUE=""><!SET NAME="ruid" CONTENT="a"><!ENDIF><img src="http://fs-$(ruid).myvi.ru/$*(myvi).th1" border="0" style="padding: 0.5em; border: #777 1px solid; background-color: #eee"></a>
<!ELSE><img src="http://img.rutube.ru/thumbs/$&(ruid)-2.jpg" border="0" style="padding: 0.5em; border: #777 1px solid; background-color: #eee"></a><!ENDIF>
</small><br>
<!IFNOT NAME="meta.description" CONTENT=""><div class="serp2"><small>$&(meta.description:256)</small></div>
<!ELSE>
  <!IFNOT NAME="meta.keywords" CONTENT=""><div class="serp2"><small>$&(meta.keywords:256)</small></div><!ENDIF>
<!ENDIF>
<small class="result">$(Last-Modified) - $(Score)</small>
</div>
<!--/res-->

<!--clone-->
<li><A HREF="$(URL)">$(URL:50)</A>,&nbsp; $(Last-Modified)
<!--/clone-->

<!--navleft-->
<TD><A class="leftmenu" HREF="$(self)$(NH)"><small>&laquo;&laquo;$(prev.lng)&laquo;</small></A></TD>
<!--/navleft-->

<!--navbar0-->
<TD><b class="hl">$(NP)</b></TD>
<!--/navbar0-->

<!--navbar1-->
<TD><A class="leftmenu" HREF="$(self)$(NH)">$(NP)</A></TD>
<!--/navbar1-->

<!--navright-->
<TD><A class="leftmenu" HREF="$(self)$(NH)"><small>&raquo;$(next.lng)&raquo;&raquo;</small></A></TD>
<!--/navright-->

<!--navigator-->
<table border="0" cellspacing="0" cellpadding="3"><tr><td><small>$(pages.lng):</small></td>$(NL) $(NB) $(NR)</tr></table>
<!--/navigator-->

<!--resbot-->
</td></tr>
<tr><td valign="bottom">
<table align="center" border="0" cellspacing="0" cellpadding="3"><tr><td>$(pages.lng):</td>$(NL)$(NB)$(NR)</tr></table></td></tr>
<tr><td align="left" valign="middle"><small>&nbsp;$(sortedby.lng):&nbsp;
<!IF NAME="s" CONTENT="DRP">
<a href="$(FirstPage)&s=RPD">$(rsort.lng)</a>&nbsp;|&nbsp;<span class="hl">$(dsort.lng)</span><!ELSE>
<span class="hl">$(rsort.lng)</span>&nbsp;|&nbsp;<a href="$(FirstPage)&s=DRP">$(dsort.lng)</a>
<!ENDIF></small></td></tr>
<!--/resbot-->


<!--notfound-->
<tr><td>
<br>
$(notfound.lng)
<br><br>
<td></tr>
<!--/notfound-->

<!--noquery-->
&nbsp;
<!--/noquery-->

<!--error-->
<tr><td>
<CENTER>
<FONT COLOR="#FF0000">$(error.lng)</FONT>
<P>
<B>$(E)</B>
</CENTER>
</td></tr>
<!--/error-->


