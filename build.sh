#!/bin/bash

# Compile the C project
rm -f main
rm -f *.o
gcc -c lnode.c
gcc -c mnode.c
gcc -c main.c
gcc -o main main.o lnode.o mnode.o

# Run the executable
./main