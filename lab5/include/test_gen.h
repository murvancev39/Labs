/**
 * @file test_gen.h
 * @brief Утилиты для генерации тестовых данных.
 * 
 * Содержит функции для создания массивов `unsigned` с различным распределением 
 * значений для оценки производительности структур данных.
 */

#ifndef TEST_GEN_H
#define TEST_GEN_H

#include <stdio.h>
#include <stdlib.h>
#include "status_def.h"

/** 
 * @brief Генерирует массив случайных чисел.
 * @param size Размер массива.
 * @return Указатель на массив или NULL при ошибке выделения памяти.
 */
unsigned *rand_unsigned_arr(unsigned size);

/** 
 * @brief Генерирует массив, отсортированный в обратном порядке (от size до 1).
 * @note Удобно для проверки худшего случая в деревьях поиска.
 * @param size Размер массива.
 * @return Указатель на массив или NULL при ошибке выделения памяти.
 */
unsigned *sorted_unsigned_arr(unsigned size);

#endif