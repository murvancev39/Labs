#!/bin/bash

gcc get_max_rand.c -o get_max_rand.exe
gcc arr_generator.c  -o arr_generator.exe
gcc sorted_arr_generator.c  -o sorted_arr_generator.exe

MAX_VAL=$(./get_max_rand.exe)

mkdir -p tests/small_tests

echo "small tests generating"

for (( size=0 ; size<=1000; size+=50))
do
    echo -ne "Processing: size $size\r"
    for (( i=0 ; i < 5; i++ ))
    do
        ./arr_generator.exe $size $MAX_VAL> tests/small_tests/"${size}_${i}.in"
        cat tests/small_tests/"${size}_${i}.in" | ./sorted_arr_generator.exe $size > tests/small_tests/"${size}_${i}.out"

    done
done

mkdir -p tests/big_tests
echo "big tests generating"
for (( size=0 ; size<=1000000; size+=10000))
do
    echo -ne "Processing: size $size\r"
    for (( i=0 ; i < 5; i++ ))
    do
        ./arr_generator.exe $size $MAX_VAL> tests/big_tests/"${size}_${i}.in"
        cat tests/big_tests/"${size}_${i}.in" | ./sorted_arr_generator.exe $size > tests/big_tests/"${size}_${i}.out"

    done
done

mkdir -p tests/test_most_dublicates

echo "test most dublicates generating"

MAX_VAL=$(( 10000 ))

for (( size=0 ; size<=1000000; size+=10000))
do
    echo -ne "Processing: size $size\r"
    for (( i=0 ; i < 5; i++ ))
    do
        ./arr_generator.exe $size $MAX_VAL> tests/test_most_dublicates/"${size}_${i}.in"
        cat tests/test_most_dublicates/"${size}_${i}.in" | ./sorted_arr_generator.exe $size > tests/test_most_dublicates/"${size}_${i}.out"

    done
done

