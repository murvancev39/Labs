#!/bin/bash

if [ "$#" -ne 6 ]; then
    echo "Ошибка: Нужно передать 6 аргументов, а получено $#"
    echo "Шаблон: <from> <to> <step> <max val> <test_dir_path> <gen_files_path> <res_dir>"
    exit 1
fi

from=$1
to=$2
step=$3
MAX_VAL=$4
TEST_DIR=$5
TESTS_GEN_PATH=$6



mkdir -p "$TEST_DIR"



for (( size=from ; size<=to; size+=step))
do
    echo -ne "Processing: size $size\r"
    for (( i=0 ; i < 5; i++ ))
    do
        "./${TESTS_GEN_PATH}/gen.exe" $size $MAX_VAL> "$TEST_DIR/${size}_${i}.in"
        "./${TESTS_GEN_PATH}/sorted_gen.exe" $size < "$TEST_DIR/${size}_${i}.in" > "$TEST_DIR/${size}_${i}.out"
    done
done


