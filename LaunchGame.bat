@echo off
setlocal

set BUILD_DIR=%~dp0build
set CONFIG=Debug
set EXE=%BUILD_DIR%\00_Game\%CONFIG%\ThirdPersonSandbox.exe
set LOG_FILE=%~dp0FullGame.log

if not exist "%EXE%" (
    set EXE=%BUILD_DIR%\00_Game\ThirdPersonSandbox.exe
)

if not exist "%EXE%" (
    echo Game executable not found.
    echo Build first with:
    echo   cmake -S . -B build
    echo   cmake --build build --config %CONFIG%
    pause
    exit /b 1
)

echo Launching %EXE%
"%EXE%"
set GAME_EXIT_CODE=%ERRORLEVEL%

echo.
echo Game exited with code %GAME_EXIT_CODE%.
if exist "%LOG_FILE%" (
    echo Log file: %LOG_FILE%
)
if not "%GAME_EXIT_CODE%"=="0" (
    echo Non-zero exit means startup failed. Open FullGame.log and share the last 30 lines.
)

pause
exit /b %GAME_EXIT_CODE%
