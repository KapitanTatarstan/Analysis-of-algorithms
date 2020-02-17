@echo off

SET START1=100
SET END1=1000
SET STEP1=100

SET START2=1000
SET END2=10000
SET STEP2=1000

for /l %%i in (%START1%, %STEP1%, %END1%) do ( 
call "cmd /c Debug\ConApp.exe 10 %%i% -5 5" 
)

for /l %%i in (%START2%, %STEP2%, %END2%) do ( 
call "cmd /c Debug\ConApp.exe 10 %%i% -5 5"
)

pause
exit