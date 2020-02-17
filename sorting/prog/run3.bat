@echo off

SET START1=10000
SET END1=100000
SET STEP1=10000

for /l %%i in (%START1%, %STEP1%, %END1%) do ( 
call "cmd /c Debug\ConApp.exe 10 %%i% -5 5" 
)

pause
exit