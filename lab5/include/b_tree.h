/**
 * @file b_tree.h
 * @brief Реализация B-дерева (сбалансированного дерева поиска).
 * 
 * B-дерево поддерживает логарифмическое время поиска, вставки и удаления.
 * Каждый узел может содержать до (2*degree - 1) ключей.
 */

#ifndef B_TREE_H
#define B_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "status_def.h"

/** @brief Минимальная степень (t), определяющая емкость узлов. */
#define MIN_TREE_SIZE 64

/** @brief Узел B-дерева. */
typedef struct b_Node_t
{
    int leaf;                      /**< Истина (1), если узел является листом */
    unsigned count;                /**< Текущее количество ключей в узле */
    unsigned *key_arr;             /**< Динамический массив ключей размера (2*t - 1) */
    struct b_Node_t **children_arr; /**< Массив указателей на потомков размера (2*t) */
} b_node_t;

/** @brief Структура для управления B-деревом. */
typedef struct b_Tree_t
{
    unsigned degree; /**< Степень дерева (t), определяет min/max число детей */
    b_node_t *root;  /**< Указатель на корневой узел */
} b_tree_t;

/** 
 * @brief Создает дерево с параметром MIN_TREE_SIZE. 
 * @return Указатель на b_tree_t или NULL при ошибке аллокации.
 */
void *b_init();

/** @brief Рекурсивно освобождает память узла и всех его поддеревьев. */
void b_free_node(b_node_t *node);

/** @brief Полная деструкция дерева и освобождение всех узлов. */
void b_free_tree(void *tree_v);

/** @brief Инициализирует дерево с заданным параметром степени (degree >= 2). */
b_tree_t *b_tree_init(unsigned degree);

/** @brief Выделяет память для узла и его массивов ключей/детей. */
b_node_t *b_node_init(unsigned degree);

/** 
 * @brief Поиск ключа в дереве.
 * @return Узел, содержащий ключ, или NULL, если ключ не найден.
 */
b_node_t *b_search(b_tree_t *tree, unsigned key);

/** 
 * @brief Вставка ключа. Использует расщепление узлов (splitting) при переполнении.
 * @return OK в случае успеха, ERROR если память не выделена.
 */
int b_add(void *tree_v, unsigned key);

/** 
 * @brief Бинарный поиск индекса ключа внутри узла.
 * @return Индекс в массиве ключей или позиция для вставки.
 */
unsigned b_find_idx(b_node_t *node, unsigned key);

/** 
 * @brief Удаление ключа. Выполняет слияние (merging) и перераспределение ключей (rebalancing).
 * @return OK при успешном удалении, ERROR если ключ отсутствует или возникла ошибка.
 */
int b_delete(void *tree_v, unsigned key);

#endif