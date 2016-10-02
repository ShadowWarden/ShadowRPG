#!/bin/bash
x86_64-w64-mingw32-gcc -o ../main.exe ../src/main.c ../src/map.c ../src/character.c ../src/move.c ../src/inst.c -lncurses
