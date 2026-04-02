
if [[ "$1" == "-g" ]]; then
    echo "Режим генерации включен"
    ./all_tests_generate.sh
fi

mkdir -p tests_results/part_1/small_tests

gcc testing.c tester.c quadratic_sorts.c part_1.c  -o part1.exe
echo "--------------- PART 1 ---------------"
./part1.exe

mkdir -p tests_results/part_2/big_tests

gcc testing.c tester.c heap_sort.c part_2.c  -o part2.exe
echo "--------------- PART 2 ---------------"
./part2.exe

mkdir -p tests_results/part_3/big_tests

gcc testing.c tester.c merge_sort.c part_3.c  -o part3.exe
echo "--------------- PART 3 ---------------"
./part3.exe


mkdir -p tests_results/part_4/big_tests
mkdir -p tests_results/part_4/test_most_dublicates

gcc testing.c tester.c quick_sorts_partition.c part_4.c  -o part4.exe
echo "--------------- PART 4 ---------------"
./part4.exe



mkdir -p tests_results/part_5/big_tests

gcc testing.c tester.c quick_sorts_partition.c quick_sorts_pivot.c part_5.c  -o part5.exe
echo "--------------- PART 5 ---------------"
./part5.exe


mkdir -p tests_results/part_10/big_tests

gcc testing.c tester.c heap_sort.c merge_sort.c quick_sorts_partition.c quick_sorts_pivot.c part_10.c  -o part10.exe
echo "--------------- PART 10 ---------------"
./part10.exe

python plotter.py