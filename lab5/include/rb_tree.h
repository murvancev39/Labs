/**
 * @file rb_tree.h
 * @brief Интерфейс красно-черного дерева (RBT).
 * 
 * Самобалансирующееся дерево поиска, гарантирующее высоту O(log n).
 * Инварианты: 
 * 1. Каждый узел либо красный, либо черный.
 * 2. Корень всегда черный.
 * 3. Красный узел не может иметь красных потомков.
 * 4. Путь от узла до любого листового узла содержит одинаковое число черных узлов.
 */

#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "side.h"
#include "status_def.h"

/** @brief Цветовая схема узлов. */
typedef enum clr
{
    red = 0,    /**< Красный */
    black = 1   /**< Черный */
} color_t;

/** @brief Узел красно-черного дерева. */
typedef struct rb_nd
{
    unsigned key;              /**< Ключ узла */
    color_t color;             /**< Цвет узла */
    struct rb_nd *parent;      /**< Родительский узел */
    struct rb_nd *left_node;   /**< Левый потомок */
    struct rb_nd *right_node;  /**< Правый потомок */
} rb_node_t;

/** @brief Структура красно-черного дерева. */
typedef struct rb_Tree_t
{
    unsigned count;    /**< Количество узлов */
    rb_node_t *root;   /**< Указатель на корень */
} rb_tree_t;

/** @brief Инициализация пустого дерева. */
void *rb_init();

/** @brief Полная деструкция дерева и освобождение всех узлов. */
void rb_destroy_tree(void *tree_v);

/** @brief Рекурсивное освобождение памяти поддерева. */
void rb_destroy_nodes(rb_node_t *node);

/** @brief Вставка ключа в дерево с последующей балансировкой. */
int rb_add(void *tree_v, unsigned key);

/** @brief Удаление ключа с восстановлением свойств RBT. */
int rb_delete(void *tree_v, unsigned key);

/** @brief Поиск узла по ключу (вспомогательная). */
rb_node_t *rb_search_n(rb_node_t *tree, unsigned key);

/** @brief Поиск узла по ключу (интерфейсная). */
rb_node_t *rb_search(rb_tree_t *tree, unsigned key);

/** @brief Выполнение левого или правого поворота вокруг узла. */
rb_node_t *rb_rotate(rb_node_t *node, side_t side);

/** @brief Восстановление свойств RBT после вставки. */
void rb_fix(rb_tree_t *tree, rb_node_t *node);

/** @brief Рекурсивная вставка узла в дерево поиска. */
rb_node_t *rb_insert(rb_node_t *tree, rb_node_t *parent, unsigned key);

/** @brief Восстановление свойств RBT после удаления. */
void rb_fix_delete(rb_tree_t *tree, rb_node_t *node, rb_node_t *dod);

/** @brief Замена поддерева `first` на поддерево `second` в структуре дерева. */
void rb_transplant(rb_tree_t *tree, rb_node_t *first, rb_node_t *second);

#endif