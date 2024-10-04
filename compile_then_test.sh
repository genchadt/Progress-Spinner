#!/bin/bash

echo
echo "Compiling..."

start=$(date +%s%N)

g++ -std=c++23 -static-libgcc -static-libstdc++ -static -pthread -o spinningload spinningload.cpp

end=$(date +%s%N)

elapsed_ns=$((end - start))
elapsed_sec=$((elapsed_ns / 1000000000))
elapsed_ns=$((elapsed_ns % 1000000000))

hours=$((elapsed_sec / 3600))
mins=$(( (elapsed_sec % 3600) / 60))
secs=$((elapsed_sec % 60))
csecs=$((elapsed_ns / 10000000))

echo "Compile complete."
echo "Compile Time: $hours:$mins:$secs.$csecs"

sleep 1

echo
echo "Running..."
echo

./spinningload

echo
echo "Run complete."
