@echo off

SET START1=100
SET END1=1000

SET START2=101
SET END2=1001
SET STEP=100

for /l %%i in (%START1%, %STEP%, %END1%) do ( 
call "cmd /c Debug\ConApp.exe %%i% 10 -5 5" 
)

for /l %%i in (%START2%, %STEP%, %END2%) do ( 
call "cmd /c Debug\ConApp.exe %%i% 10 -5 5"
)

pause
exit