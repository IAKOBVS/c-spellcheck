#!/bin/sh
cc -O3 main.c -o main -g -fsanitize=address
