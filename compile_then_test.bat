@echo off
echo:
echo Compiling...
setlocal
set start=%time%

@echo on
"C:\msys64\mingw64\bin\g++.exe" -std=c++23 -static-libgcc -static-libstdc++ -static -pthread -o spinningload spinningload.cpp
@echo off

set end=%time%
set /A hours=((1%end:~0,2% - 1%start:~0,2% + 24) %% 24)
set /A mins=((1%end:~3,2% - 1%start:~3,2% + 60) %% 60)
set /A secs=((1%end:~6,2% - 1%start:~6,2% + 60) %% 60)
set /A csecs=((1%end:~9,2% - 1%start:~9,2% + 100) %% 100)

echo Compile complete.
echo Compile Time: %hours%:%mins%:%secs%.%csecs%

timeout 1

echo:
echo Running...
echo:

.\spinningload.exe

echo:
echo Run complete.
endlocal
