@set dir=%SystemRoot%\Microsoft.NET\Framework\v2.0.50727\
@set ProjectName=lesson12-sqlite3-db-js

@echo %dir%
@echo.

@%dir%\jsc /target:winexe %ProjectName%.js
@rem %dir%\jsc /target:winexe /resource:res\%ProjectName%.resources /r:System.Data.SQLite.dll %ProjectName%.js

@pause
