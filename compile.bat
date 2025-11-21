@echo off
set SCRIPT_DIR=%~dp0.
echo ========================================
echo   pawn-ini - compilation script
echo   Version: v0.1.0
echo   Platform: Windows
echo ========================================

if /I "%1"=="clean" (
    echo [*] Cleaning build and output directories...
    if exist build (
        rmdir /s /q build
        echo Build directory removed
    ) else (
        echo Build directory does not exist
    )
    if exist output (
        rmdir /s /q output
        echo Output directory removed
    ) else (
        echo Output directory does not exist
    )
    echo.
)

where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo ! ERROR: CMake not found in PATH
    echo ! Please install CMake from: https://cmake.org/download/
    echo.
    pause
    exit /b 1
)

echo * CMake found

if not exist build (
    echo * Creating build directory...
    mkdir build
)

echo.
echo ========================================
echo   Building 32-bit (Win32)
echo ========================================
call :build_arch Win32 x32
if %errorlevel% neq 0 goto :build_failed

echo.
echo ========================================
echo   Building 64-bit (x64)
echo ========================================
call :build_arch x64 x64
if %errorlevel% neq 0 goto :build_failed

echo.
echo All builds successful!

REM Copy final artifacts to repo root (32-bit plugin + include)
if exist output\x32\pawn-ini.dll copy /Y output\x32\pawn-ini.dll pawn-ini.dll >nul
if exist output\pawn-ini.inc copy /Y output\pawn-ini.inc pawn-ini.inc >nul

echo Compilation has been completed
echo Compiled files in output/:
dir /b output
echo.
echo Root artifacts:
if exist pawn-ini.dll echo   pawn-ini.dll (32-bit)
if exist pawn-ini.inc echo   pawn-ini.inc
echo.
echo Plugin size (32-bit in root):
for %%F in (pawn-ini.dll) do if exist %%F echo   pawn-ini.dll: %%~zF bytes
echo.
echo Files are ready in the repo root (pawn-ini.dll / pawn-ini.inc) and in 'output/x32' and 'output/x64'.
echo.
echo Installation (typical SA-MP 32-bit server):
echo   1. Copy pawn-ini.dll from output\x32 or repo root to your server's plugins folder
echo   2. Copy pawn-ini.inc to your server's pawno\include folder
echo   3. Add 'plugins pawn-ini' to server.cfg
echo   4. Include ^<pawn-ini^> in your gamemode
echo.
pause
exit /b 0

:build_arch
REM %1 = CMake -A value (Win32/x64)
REM %2 = architecture label (x32/x64)
setlocal ENABLEDELAYEDEXPANSION
set ARCH_GENERATOR=%1
set ARCH_LABEL=%2
set BUILD_SUBDIR=build\%ARCH_LABEL%

echo * Using build directory: !BUILD_SUBDIR!
if not exist "!BUILD_SUBDIR!" (
    mkdir "!BUILD_SUBDIR!"
)

pushd "!BUILD_SUBDIR!"

echo * Configuring project with CMake for !ARCH_LABEL!...
cmake "%SCRIPT_DIR%" -G "Visual Studio 17 2022" -A !ARCH_GENERATOR! -DPAWN_INI_ARCH=!ARCH_LABEL!

if %errorlevel% neq 0 (
    echo.
    echo ! ERROR: CMake configuration failed for !ARCH_LABEL! with VS 2022
    echo ! Trying with Visual Studio 16 2019...
    echo.
    cmake "%SCRIPT_DIR%" -G "Visual Studio 16 2019" -A !ARCH_GENERATOR! -DPAWN_INI_ARCH=!ARCH_LABEL!
    
    if %errorlevel% neq 0 (
        echo.
        echo ! ERROR: CMake configuration failed for !ARCH_LABEL!
        echo ! Please check that the corresponding Visual Studio toolset is installed
        popd
        endlocal & exit /b 1
    )
)

echo * Configuration successful for !ARCH_LABEL!
echo * Building project in Release mode for !ARCH_LABEL!...
echo.
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo.
    echo ! ERROR: Build failed for !ARCH_LABEL!
    popd
    endlocal & exit /b 1
)

echo * Installing files to output directory for !ARCH_LABEL!...
cmake --install . --config Release

if %errorlevel% neq 0 (
    echo.
    echo ! ERROR: Install failed for !ARCH_LABEL!
    popd
    endlocal & exit /b 1
)

popd
endlocal & exit /b 0

:build_failed
echo.
echo ! ERROR: One or more builds failed. See messages above.
echo.
pause
exit /b 1
