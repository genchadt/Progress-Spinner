#!/bin/bash

echo
echo "Compiling..."

# Record the start time
start=$(date +%s%N)

# Compile the C++ code
g++ -std=c++11 -static-libgcc -static-libstdc++ -static -pthread -o spinningload spinningload.cpp

# Record the end time
end=$(date +%s%N)

# Calculate elapsed time in seconds and nanoseconds
elapsed_ns=$((end - start))
elapsed_sec=$((elapsed_ns / 1000000000))
elapsed_ns=$((elapsed_ns % 1000000000))

# Format the time components
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
