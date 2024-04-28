@echo off
g++ -std=c++11 -static-libgcc -static-libstdc++ -static -pthread -o spinningload spinningload.cpp
echo Compilation completed.
