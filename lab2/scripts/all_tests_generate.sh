#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Ошибка: Нужно передать 3 аргумента, а получено $#"
    echo    "Шаблон -   <путь до папки в которой лежат файлы генераторы тестов> 
                        <путь до папки со скриптами>
                        <путь до папки куда складывать результаты генерации>"
    exit 1
fi

TESTS_GEN_PATH=$1
SCRIPT_DIR=$2
TEST_RES_DIR=$3

MAX_VAL=$("${TESTS_GEN_PATH}/get_max_rand.exe") 
# если что эта штука тут потому, что на разных системах MAX_RAND разный


SMALL_TESTS_DIR="${TEST_RES_DIR}/small_tests"
BIG_TESTS_DIR="${TEST_RES_DIR}/big_tests"
MOST_DUB_TESTS_DIR="${TEST_RES_DIR}/most_dub_tests"

mkdir -p "$SMALL_TESTS_DIR"
mkdir -p "$BIG_TESTS_DIR"
mkdir -p "$MOST_DUB_TESTS_DIR"

to=1000
step=50
from=$step

echo "small tests generating"

"./${SCRIPT_DIR}/test_gen.sh" $from $to $step $MAX_VAL "$SMALL_TESTS_DIR" "$TESTS_GEN_PATH"

if [ $? -ne 0 ]; then
    echo "ERROR: ошибка запуска генератора тестов!"
    exit 1
fi

echo "big tests generating"

to=1000000
step=50000
from=$step

"./${SCRIPT_DIR}/test_gen.sh" $from $to $step $MAX_VAL "$BIG_TESTS_DIR" "$TESTS_GEN_PATH"


if [ $? -ne 0 ]; then
    echo "ERROR: ошибка запуска генератора тестов!"
    exit 1
fi

MAX_VAL=$(( 10000 ))

echo "test most dublicates generating"

"./${SCRIPT_DIR}/test_gen.sh" $from $to $step $MAX_VAL "$MOST_DUB_TESTS_DIR" "$TESTS_GEN_PATH"

if [ $? -ne 0 ]; then
    echo "ERROR: ошибка запуска генератора тестов!"
    exit 1
fi

