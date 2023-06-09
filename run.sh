#!/bin/bash

# Compile the code
g++ -std=c++11 -Wall -o main main.cpp lib.cpp

# Execute the compiled program with input.txt as input and redirect the output to output.txt
./main < input.txt > output.txt

# Clean up the executable
rm -f main
