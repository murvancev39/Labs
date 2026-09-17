#ifndef HASH_F_PART_2
#define HASH_F_PART_2

#include <stdio.h>
#include <stdlib.h>
#include "err_def.h"

/**
 * @file hash_f_part_2.h
 * @brief Хеш-функции и компаратор для типа float через битовые маски и union.
 */

/**
 * @union float_u
 * @brief Объединение для побитового доступа к представлению float (IEEE 754).
 */
typedef union
{
    float f;    /**< Значение как число с плавающей точкой. */
    unsigned u; /**< Значение как беззнаковое целое для битовых операций. */
} float_u;

/**
 * @brief Хеширование путем простого приведения float к unsigned int.
 */
unsigned hash_f_f_int (void *key);

/**
 * @brief Хеширование всего битового представления со сдвигом на 3 бита.
 */
unsigned hash_f_f_union (void *key);

/**
 * @brief Хеширование на основе мантиссы числа (младшие 23 бита).
 */
unsigned hash_f_f_mantiss (void *key);

/**
 * @brief Хеширование на основе экспоненты числа (8 бит порядка).
 */
unsigned hash_f_f_exp (void *key);

/**
 * @brief Хеширование перемножением мантиссы на экспоненту.
 */
unsigned hash_f_f_mant_exp (void *key);

/**
 * @brief Компаратор для типа float.
 * @return 0 при равенстве, 1 если key1 > key2, -1 если key1 < key2.
 */
int float_cmp (void *key1, void *key2);

#endif