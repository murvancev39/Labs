#ifndef HASH_F_PART_1
#define HASH_F_PART_1

#include <stdio.h>
#include <stdlib.h>
#include "err_def.h"

/**
 * @file hash_f_part_1.h
 * @brief Хеш-функции и компаратор для типа unsigned int.
 */

/**
 * @brief Хеширование методом деления (остаток от деления на 1000).
 */
unsigned hash_f_u_rem (void *key);

/**
 * @brief Хеширование со сдвигом бит (исключение младших 3 бит).
 */
unsigned hash_f_u_bits (void *key);

/**
 * @brief Мультипликативное хеширование Кнута (золотое сечение).
 */
unsigned hash_f_u_knuth (void *key);

/**
 * @brief Компаратор для unsigned int.
 * @return 0 при равенстве, 1 если key1 > key2, -1 если key1 < key2.
 */
int unsigned_cmp (void *key1, void *key2);

#endif