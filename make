#!/bin/sh
cc -O3 main.c -o c-spellcheck -g -fsanitize=address
