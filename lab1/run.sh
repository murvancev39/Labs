#!/bin/bash

gcc -O2 tests_arr.c arr_stack.c -o tests_arr.exe
gcc -O2 tests_list.c list_stack.c -o tests_list.exe
echo "compile"

echo "arr:"
./tests_arr.exe
echo "list:"
./tests_list.exe
echo "python:"
python laba.py