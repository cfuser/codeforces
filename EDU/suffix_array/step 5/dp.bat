@echo off
:loop
data.exe
Refrain.exe
brute_force.exe
fc out.txt brute.txt
if not errorlevel 1 goto loop
pause