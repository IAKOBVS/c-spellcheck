#!/bin/sh
# cc -O3 main.c -o main
# cc -O3 main.c -o main -g
cc -O3 main.c -o main -g -fsanitize=address
