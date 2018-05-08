@echo off
set cscdir=%SystemRoot%\Microsoft.NET\Framework\v2.0.50727\
set assemblies=System.dll,System.Web.dll

set outdir=..\bin\page.RArticleM.dll
set CmdLine1=%cscdir%csc /t:library /out:%outdir% /r:%assemblies%,..\bin\SqlHelper.dll RArticleM.aspx.cs
echo #%CmdLine1%
%CmdLine1%

pause