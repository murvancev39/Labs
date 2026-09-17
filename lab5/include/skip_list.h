/**
 * @file skip_list.h
 * @brief Интерфейс списка с пропусками (Skip List).
 * 
 * Список с пропусками — это структура данных, позволяющая выполнять поиск, 
 * вставку и удаление за ожидаемое время O(log n). Она реализована как 
 * многоуровневый связный список.
 */

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "status_def.h"

/** @brief Узел списка с пропусками. */
typedef struct skip_Node_t
{
    unsigned key;                /**< Ключ узла */
    struct skip_Node_t *next;    /**< Ссылка на следующий узел на текущем уровне */
    struct skip_Node_t *down;    /**< Ссылка на соответствующий узел уровнем ниже */
} skip_node_t;

/** @brief Структура списка с пропусками. */
typedef struct skip_List_t
{
    unsigned height;     /**< Текущая высота списка */
    unsigned max_height; /**< Максимальная вместимость уровней */
    skip_node_t **lists_arr; /**< Массив указателей на головы уровней */
} skip_list_t;

/** @brief Инициализация пустого списка. */
void *skip_init();

/** @brief Создание нового пустого уровня (голова и хвост с INT_MIN/INT_MAX). */
skip_node_t *skip_ctr_list();

/** @brief Генерация случайной высоты для нового узла (на основе подбрасывания монетки). */
unsigned skip_get_rand_height();

/** @brief Увеличение массива уровней при достижении текущего максимума. */
int skip_re_max_height(skip_list_t *list);

/** @brief Полная деструкция списка и освобождение всех уровней и узлов. */
void skip_destructor(void *list_v);

/** @brief Поиск узла по ключу, начиная с верхнего уровня. */
skip_node_t *skip_search(skip_node_t *top, unsigned key);

/** @brief Вставка ключа в список. */
int skip_add(void *list_v, unsigned key);

/** @brief Удаление ключа из списка. */
int skip_delete(void *list_v, unsigned key);

/** @brief Динамическое добавление уровней до `new_height`. */
int skip_re_height(skip_list_t *list, unsigned new_height);

/** @brief Вставка узла `this` после узла `after_that` на одном уровне. */
int skip_insert_node(skip_node_t *after_that, skip_node_t *this);

/** @brief Создание нового узла с заданными ссылками. */
skip_node_t *skip_ctr_node(unsigned key, skip_node_t *down, skip_node_t *next);

#endif