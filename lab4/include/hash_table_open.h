#ifndef HASH_TABLE_OPEN_H
#define HASH_TABLE_OPEN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "err_def.h"

/**
 * @file hash_table_open.h
 * @brief Хеш-таблица с открытой адресацией.
 */

/**
 * @enum status
 * @brief Статусы ячеек для внутренней логики.
 */
typedef enum
{
    empty = 0,            /**< Пусто. */
    deleted = 0xFFFFFFFF, /**< Удалено. */
} status;

#define EMPTY ((void *) 0)   /**< Указатель на пустую ячейку. */
#define DELETED ((void *) 1) /**< Указатель на удаленный элемент (сохраняет цепочку пробирования). */

typedef int (*cmp_t) (void *, void *);
typedef unsigned (*hash_f_t) (unsigned, void *);

/**
 * @struct Open_Hash_Table
 * @brief Контекст таблицы с открытой адресацией.
 */
struct Open_Hash_Table
{
    void **arr;              /**< Массив указателей на данные. */
    size_t size;             /**< Размер массива ячеек. */
    size_t count;            /**< Количество элементов в таблице. */
    float load_factor;       /**< Предельный коэффициент заполнения. */
    cmp_t cmp;               /**< Функция сравнения ключей. */
    hash_f_t hash_f1;        /**< Первая хеш-функция. */
    unsigned koef_for_f1;    /**< Коэффициент для hash_f1. */
    hash_f_t hash_f2;        /**< Вторая хеш-функция. */
    unsigned koef_for_f2;    /**< Коэффициент для hash_f2. */
    
    /**
     * @brief Функция пробирования.
     * @param table Таблица.
     * @param key Ключ.
     * @param attempt Номер попытки (итерации) пробирования.
     * @return Вычисленный индекс.
     */
    unsigned (*idx_f) (struct Open_Hash_Table *, void *, unsigned);
    unsigned max_iterations; /**< Максимальное число шагов при поиске/вставке. */
};

typedef struct Open_Hash_Table open_hash_table_t;
typedef unsigned (*idx_f_t)   (open_hash_table_t *, void *, unsigned);

/**
 * @brief Создает хеш-таблицу.
 * @return Указатель на таблицу или NULL при ошибке.
 */
open_hash_table_t *open_hash_table_ctr (size_t size, float load_factor, hash_f_t hash_f1, unsigned koef_for_f1,
                                        hash_f_t hash_f2, unsigned koef_for_f2, idx_f_t idx_f, cmp_t cmp);

/**
 * @brief Освобождает память таблицы. Ключи не удаляет.
 */
void open_hash_table_dtr (open_hash_table_t *table);

/**
 * @brief Рехеширует таблицу, увеличивая размер в 2 раза.
 * @return OK или код ошибки.
 */
int open_hash_table_rehash (open_hash_table_t *table, int add_f (open_hash_table_t *, void *));

/**
 * @brief Стандартная мультипликативная хеш-функция.
 */
unsigned hash (void *key);

/**
 * @brief Альтернативная хеш-функция. Всегда нечетная (для двойного хеширования).
 */
unsigned hash_2 (void *key);

/**
 * @brief Добавляет ключ в таблицу. При переполнении делает рехеш.
 * @return OK, ALLOC_ERR или ERR.
 */
int open_hash_table_add (open_hash_table_t *table, void *key);

/**
 * @brief Ищет ключ в таблице.
 * @return Индекс ячейки или -1, если не найден.
 */
long open_hash_table_search (open_hash_table_t *table, void *key);

/**
 * @brief Удаляет элемент из таблицы, помечая ячейку как DELETED.
 * @return OK или ERR.
 */
int open_hash_table_delete (open_hash_table_t *table, void *key);

#endif