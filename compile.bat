@echo off
echo ========================================
echo   pawn-ini - compilation script
echo   Version: v0.1.0
echo   Platform: Windows
echo ========================================

if /I "%1"=="clean" (
    echo [*] Cleaning build directory...
    if exist build (
        rmdir /s /q build
        echo Build directory removed
    ) else (
        echo Build directory does not exist
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

cd build

echo * Configuring project with CMake...
cmake .. -G "Visual Studio 17 2022"

if %errorlevel% neq 0 (
    echo.
    echo ! ERROR: CMake configuration failed
    echo ! Trying with Visual Studio 16 2019...
    echo.
    cmake .. -G "Visual Studio 16 2019"
    
    if %errorlevel% neq 0 (
        echo.
        echo ! ERROR: CMake configuration failed
        echo ! Please check that Visual Studio is installed
        cd ..
        pause
        exit /b 1
    )
)

echo * Configuration successful
echo * Building project in Release mode...
echo.
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo.
    echo ! ERROR: Build failed
    cd ..
    pause
    exit /b 1
)

echo Build successful!

echo Installing files to output directory...
cmake --install . --config Release

cd ..

echo Compilation has been complete
echo Compiled files:
dir /b output
echo.
echo Plugin size:
for %%F in (output\pawn-ini.dll) do echo   pawn-ini.dll: %%~zF bytes
echo.
echo Files are ready in the 'output' directory
echo.
echo Installation:
echo   1. Copy output\pawn-ini.dll to your server's plugins folder
echo   2. Copy output\pawn-ini.inc to your server's pawno\include folder
echo   3. Add 'plugins pawn-ini' to server.cfg
echo   4. Include ^<pawn-ini^> in your gamemode
echo.
pause
