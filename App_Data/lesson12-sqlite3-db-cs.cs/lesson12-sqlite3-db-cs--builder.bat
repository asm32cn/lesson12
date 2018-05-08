@echo off
set cscdir=%SystemRoot%\Microsoft.NET\Framework\v2.0.50727\
set ProjName=lesson12-sqlite3-db-cs
echo %cscdir%
echo.

rem %cscdir%\csc /target:winexe /resource:res\%ProjName%.resources /win32icon:res\%ProjName%.ico %ProjName%.cs
%cscdir%\csc /target:winexe %ProjName%.cs /win32icon:res\sqlite3-db.ico /r:System.Data.SQLite.dll

pause
