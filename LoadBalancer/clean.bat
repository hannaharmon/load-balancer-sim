@echo off
REM Clean script for Load Balancer Simulation (Windows)

echo Cleaning build artifacts...

if exist *.obj del /Q *.obj
if exist *.exe del /Q *.exe
if exist *.ilk del /Q *.ilk
if exist *.pdb del /Q *.pdb
if exist *.log del /Q *.log
if exist simulation.txt del /Q simulation.txt

echo Clean complete!
