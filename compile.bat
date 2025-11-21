@echo off
setlocal ENABLEDELAYEDEXPANSION

echo ========================================
echo   pawn-ini - compilation script
echo   Version: v0.1.0
echo   Platform: Windows
echo ========================================

set SCRIPT_DIR=%~dp0
set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

echo.
echo === Building Win32 (x32) ===
call :build_arch Win32 x32
if %errorlevel% neq 0 goto :error

echo.
echo === Building Win64 (x64) ===
call :build_arch x64 x64
if %errorlevel% neq 0 goto :error

echo.
echo ========================================
echo      Compilacion completada
echo ========================================
pause
exit /b 0

:error
echo ERROR: Fallo una de las compilaciones.
pause
exit /b 1


:build_arch
set PLATFORM=%1
set ARCH=%2

set BUILD_DIR=build\%ARCH%
set OUT_DIR=.output\%ARCH%

echo * Build dir: %BUILD_DIR%
echo * Output dir: %OUT_DIR%

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
if not exist ".output" mkdir ".output"
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

pushd "%BUILD_DIR%"

echo * Configurando CMake...
cmake "%SCRIPT_DIR%" -G "Visual Studio 17 2022" -A %PLATFORM% -DPAWN_INI_ARCH=%ARCH%
if %errorlevel% neq 0 (
    popd
    exit /b 1
)

echo * Compilando...
cmake --build . --config Release
if %errorlevel% neq 0 (
    popd
    exit /b 1
)

echo * Instalando...
cmake --install . --config Release --prefix "%SCRIPT_DIR%\.output\%ARCH%"
if %errorlevel% neq 0 (
    popd
    exit /b 1
)

popd
exit /b 0
