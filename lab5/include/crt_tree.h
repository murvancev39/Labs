/**
 * @file crt_tree.h
 * @brief Интерфейс декартова дерева (Treap).
 * 
 * Декартово дерево объединяет свойства бинарного дерева поиска (по ключу)
 * и кучи (по приоритету). Обеспечивает O(log n) операций в среднем.
 */

#ifndef CRT_TREE_H
#define CRT_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status_def.h"

/** @brief Узел декартова дерева. */
typedef struct crt_Node
{
    unsigned key;          /**< Ключ поиска */
    int priority;          /**< Приоритет для кучи (рандомизированный) */
    unsigned size;         /**< Размер поддерева (для порядковых статистик) */
    struct crt_Node *left;  /**< Левый потомок */
    struct crt_Node *right; /**< Правый потомок */
    struct crt_Node *dad;   /**< Указатель на родителя */
} crt_node_t;

/** @brief Структура декартова дерева. */
typedef struct crt_tree_t
{
    crt_node_t *root; /**< Корневой узел */
} crt_tree_t;

/** @brief Инициализация пустого дерева. */
void *crt_init();

/** @brief Пересчет размера узла на основе размеров его детей. */
void crt_update_size(crt_node_t *node);

/** @brief Рекурсивное освобождение узлов дерева. */
void crt_clear_nodes(crt_node_t *node);

/** @brief Деструкция дерева: освобождение памяти всех узлов. */
void crt_destroy_tree(void *tree_v);

/** 
 * @brief Слияние двух деревьев T1 и T2.
 * @note Ключи в T1 должны быть строго меньше ключей в T2.
 */
crt_node_t *crt_merge(crt_node_t *T1, crt_node_t *T2);

/** @brief Поиск ключа в дереве. @return 1 если найден, 0 иначе. */
int crt_search(crt_tree_t *tree, unsigned key);

/** @brief Вставка ключа. Использует split и merge. */
int crt_add(void *tree_v, unsigned key);

/** @brief Удаление ключа. Использует split и merge. */
int crt_delete(void *tree_v, unsigned key);

/** 
 * @brief Разрезание дерева по ключу.
 * @param node Корневой узел дерева.
 * @param key Ключ разделения.
 * @param L Указатель на корень левого результата (все ключи <= key).
 * @param R Указатель на корень правого результата (все ключи > key).
 */
void crt_split(crt_node_t *node, unsigned key, crt_node_t **L, crt_node_t **R);

#endif