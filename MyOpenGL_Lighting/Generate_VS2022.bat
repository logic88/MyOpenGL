@echo off
setlocal

set "SOURCE_DIR=%~dp0."
set "BUILD_DIR=%~dp0build_vs2022"

echo Generating Visual Studio 2022 project...
echo Source: "%SOURCE_DIR%"
echo Build : "%BUILD_DIR%"
echo.

cmake -S "%SOURCE_DIR%" -B "%BUILD_DIR%" -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (
    echo.
    echo CMake generation failed.
    pause
    exit /b 1
)

echo.
echo Done. Open "%BUILD_DIR%\MyOpenGL_Lighting.sln" with Visual Studio 2022.
pause
