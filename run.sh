#!/bin/bash

# Compile the code
g++ -std=c++11 -Wall -g main.cpp -o a.out

# Execute the compiled program with input.txt as input and redirect the output to output.txt
#./a.out < carlinhos.txt > output.txt

# Debug the code with gdb
gdb a.out -x script.gdb

# Clean up the executable
rm -f a.out
