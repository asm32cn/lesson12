@set dir=%SystemRoot%\Microsoft.NET\Framework\v2.0.50727\
@set ProjName=lesson12-sqlite3-db-vb

@echo %dir%
@echo.

@rem %dir%\vbc /target:winexe /win32icon:res\%ProjName%.ico /resource:res\%ProjName%.resources /optimize %ProjName%.vb
@%dir%\vbc /target:winexe /win32icon:res\sqlite3-db.ico /optimize %ProjName%.vb /r:System.Data.SQLite.dll

@pause
