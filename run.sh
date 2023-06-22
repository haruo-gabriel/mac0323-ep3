#!/bin/bash

g++ -std=c++11 -Wall main.cpp -o a.out

./a.out < medium.txt > medium-output.txt

#gdb a.out -x script.gdb

rm -f a.out
