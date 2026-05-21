/**
 * @file spl_tree.h
 * @brief Интерфейс Splay-дерева.
 * 
 * Splay-дерево — это самобалансирующееся дерево поиска, которое использует 
 * операцию splay для перемещения узла к корню после доступа к нему.
 * Это обеспечивает амортизированную сложность O(log n) для всех операций.
 */

#ifndef SPL_TREE_H
#define SPL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status_def.h"

/** @brief Узел Splay-дерева. */
typedef struct spl_Node
{
    unsigned key;              /**< Ключ узла */
    struct spl_Node *dad;      /**< Родительский узел */
    struct spl_Node *left;     /**< Левый потомок */
    struct spl_Node *right;    /**< Правый потомок */
} spl_node_t;

/** @brief Структура Splay-дерева. */
typedef struct spl_Tree_t
{
    unsigned count;    /**< Количество узлов в дереве */
    spl_node_t *root;  /**< Корневой узел */
} spl_tree_t;

/** @brief Направления для вставки. */
typedef enum spl_Side 
{
    Left = 0,
    Right = 1,
    Root = -1
} spl_side;

/** @brief Инициализация пустого дерева. */
void *spl_ctr_tree();

/** @brief Рекурсивное освобождение памяти узлов. */
void spl_destroy_nodes(spl_node_t *node);

/** @brief Деструктор: освобождение дерева и всех его узлов. */
void spl_destructor(void *tree_v);

/** @brief Поиск узла с максимальным ключом в поддереве. */
spl_node_t *spl_max_node(spl_node_t *node);

/** @brief Поиск ключа в дереве с выполнением splay на найденном или последнем посещенном узле. */
int spl_search(spl_tree_t *tree, unsigned key);

/** @brief Вставка ключа в дерево с последующим splay нового узла. */
int spl_add(void *tree_v, unsigned key);

/** @brief Удаление ключа из дерева. */
int spl_delete(void *tree_v, unsigned key);

/** @brief Основная операция splay: перемещение узла в корень через повороты. */
void splay(spl_tree_t *tree, spl_node_t *node);

/** @brief Поворот узла вокруг его родителя (базовая операция балансировки). */
void spl_rotate(spl_tree_t *tree, spl_node_t *node);

#endif