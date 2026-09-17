/**
 * @file avl_tree.h
 * @brief Интерфейс АВЛ-дерева (самобалансирующееся бинарное дерево поиска).
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "side.h"
#include "status_def.h"

/** @brief Узел АВЛ-дерева. */
typedef struct avl_nd
{
    unsigned key;           /**< Ключ узла */
    int avl_height;         /**< Высота поддерева */
    struct avl_nd *right_node; /**< Правый потомок */
    struct avl_nd *left_node;  /**< Левый потомок */
    struct avl_nd *parent;     /**< Родительский узел */
} avl_node_t;

/** @brief Структура АВЛ-дерева. */
typedef struct avl_Tree_t
{
    avl_node_t *root;   /**< Корневой узел */
    unsigned count;     /**< Количество элементов */
} avl_tree_t;

/** @brief Инициализация пустого дерева. @return Указатель на структуру дерева. */
void *avl_init();

/** @brief Удаление дерева и освобождение памяти. */
void avl_destructor(void *tree_v);

/** @brief Обновление высоты узла на основе высот его потомков. */
void avl_change_avl_height(avl_node_t *tree);

/** @brief Получение высоты узла. @return Высота или 0, если узел NULL. */
int avl_height(avl_node_t *node);

/** @brief Поиск узла с минимальным ключом в поддереве. */
avl_node_t *avl_find_min(avl_node_t *node);

/** @brief Рекурсивное удаление узлов дерева. */
void avl_destroy_node(avl_node_t *tree);

/** @brief Балансировка дерева: повороты узлов. */
avl_node_t *avl_rotate(avl_node_t *node, side_t side);

/** @brief Вставка ключа в поддерево. */
avl_node_t *avl_insert(avl_node_t *tree, unsigned key);

/** @brief Удаление ключа из поддерева. */
avl_node_t *avl_remove(avl_node_t *tree, unsigned key);

/** @brief Поиск узла по ключу. @return Указатель на найденный узел или NULL. */
avl_node_t *avl_search(avl_tree_t *tree, unsigned key);

/** @brief Добавление ключа в дерево (с обновлением счетчика). */
int avl_add(void *tree_v, unsigned key);

/** @brief Удаление ключа из дерева (с обновлением счетчика). */
int avl_delete(void *tree_v, unsigned key);

/** @brief Поиск следующего ключа (successor). @return Ключ или -1. */
int avl_next(avl_node_t *node, unsigned key);

#endif