@echo off
set cscdir=%SystemRoot%\Microsoft.NET\Framework\v2.0.50727\
set assemblies=System.dll,System.Web.dll

set outdir=..\bin\SqlHelper.dll
set CmdLine1=%cscdir%csc /t:library /out:%outdir% /r:%assemblies% SqlHelper.cs
echo #%CmdLine1%
%CmdLine1%

set outdir=..\bin\lesson12.dll
set CmdLine1=%cscdir%csc /t:library /out:%outdir% /r:%assemblies% lesson12.cs
echo #%CmdLine1%
%CmdLine1%

set outdir=..\bin\page.RArticleM.dll
set CmdLine1=%cscdir%csc /t:library /out:%outdir% /r:%assemblies%,..\bin\SqlHelper.dll RArticleM.aspx.cs
echo #%CmdLine1%
%CmdLine1%

rem set outdir=..\bin\conn_oledb.dll
rem set CmdLine1=%cscdir%csc /t:library /out:%outdir% /r:%assemblies% conn_oledb.cs
rem echo #%CmdLine1%
rem %CmdLine1%

pause