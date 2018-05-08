@echo off

set ProjName=PaLesson12JFrame
echo Begin ...
echo --------------------
md classes
ren md classes\res
javac -d classes %ProjName%.java
echo --------------------
echo Done.

if exist %ProjName%.manifest.txt del /f %ProjName%.manifest.txt

echo Manifest-Version: 1.0> %ProjName%.manifest.txt
echo Created-By: 1.4.2_12 (Sun Microsystems Inc.)>> %ProjName%.manifest.txt
echo Class-Path: lib/sqlite-jdbc-3.7.2.jar>> %ProjName%.manifest.txt
echo Main-Class: %ProjName%>> %ProjName%.manifest.txt

echo Release ...
echo --------------------
md Release
cd classes
rem jar cvfm ..\Release\%ProjName%.jar ..\%ProjName%.manifest.txt %ProjName%.class lib/
jar cvfm ..\Release\%ProjName%.jar ..\%ProjName%.manifest.txt %ProjName%.class
cd ..
del %ProjName%.manifest.txt
echo --------------------
echo Done.

pause