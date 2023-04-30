#!/bin/bash

# Compile the C project
rm -f main
rm -f test.exe
rm -f *.o
gcc main.c -o test

# Run the executable
./test.exe