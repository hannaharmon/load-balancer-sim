@echo off
REM Build script for Load Balancer Simulation (Windows)

echo Compiling Load Balancer...
cl /EHsc /W3 /Fe:loadbalancer.exe main.cpp LoadBalancer.cpp Webserver.cpp Request.cpp RequestGenerator.cpp Firewall.cpp Logger.cpp Colors.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Run with:
    echo   .\loadbalancer.exe config.txt
) else (
    echo.
    echo Build failed!
)
