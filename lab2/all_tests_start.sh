
if [[ "$1" == "-g" ]]; then
    echo "Режим генерации включен"
    ./all_tests_generate.sh
fi

mkdir -p tests_results/part_1/small_tests
mkdir -p tests_results/part_1/big_tests
mkdir -p tests_results/part_1/test_most_dublicates

gcc testing.c tester.c quadratic_sorts.c part_1.c  -o part1.exe
echo "--------------- PART 1 ---------------"
./part1.exe