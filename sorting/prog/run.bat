@echo off


FOR %%i IN (10 100 1000 10000 100000 10000000) DO (
call "cmd /c Debug\ConApp.exe 10 %%i% -5 5"
)


pause
exit