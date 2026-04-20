@echo off
setlocal

set BUILD_DIR=%~dp0build
set CONFIG=Debug
set EXE=%BUILD_DIR%\00_Game\%CONFIG%\ThirdPersonSandbox.exe

if exist "%EXE%" (
    echo Launching %EXE%
    "%EXE%"
    exit /b %ERRORLEVEL%
)

set EXE=%BUILD_DIR%\00_Game\ThirdPersonSandbox.exe
if exist "%EXE%" (
    echo Launching %EXE%
    "%EXE%"
    exit /b %ERRORLEVEL%
)

echo Game executable not found.
echo Build first with:
echo   cmake -S . -B build
echo   cmake --build build --config %CONFIG%
exit /b 1
