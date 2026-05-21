/**
 * @file list_stack.h
 * @author Михаил Урванцев
 * @brief Реализация универсального стека на базе односвязного списка.
 */

#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "status.h"

/**
 * @struct node_t
 * @brief Узел односвязного списка.
 */
typedef struct node_t
{
    void *elem;         /**< Указатель на данные элемента */
    struct node_t *next;  /**< Указатель на следующий узел (ниже по стеку) */
} node_t;

/**
 * @struct list_stack_t
 * @brief Структура стека на основе списка.
 */
typedef struct list_stack_t
{
    node_t *head;    /**< Указатель на верхний узел */
    size_t count;    /**< Текущее количество элементов */
    size_t element_size;  /**< Размер одного элемента в байтах */
} list_stack_t;

/**
 * @brief Конструктор стека на списке.
 * @param[in] element_size Размер одного элемента данных.
 * @return Указатель на структуру стека или NULL при ошибке.
 */
void *list_stack_ctr (size_t element_size);

/**
 * @brief Деструктор стека. Очищает все узлы и освобождает данные.
 * @param[in] stack_ptr Указатель на стек.
 * @return Всегда NULL.
 */
void *list_stack_dtr (void *stack_ptr);

/**
 * @brief Добавляет новый элемент в начало (голову) списка.
 * @details Для каждого элемента аллоцируется новый узел node_t и память под сами данные.
 * @param[in] stack_ptr Указатель на стек.
 * @param[in] buffer Указатель на данные для копирования.
 * @return 1 при успехе, 0 при ошибке аллокации.
 */
status_t list_push (void *stack_ptr, void *buffer);

/**
 * @brief Копирует данные из верхнего узла в буфер.
 * @param[in] stack_ptr Указатель на стек.
 * @param[out] buffer Указатель на память для копирования данных.
 * @return 1 при успехе, 0 если стек пуст.
 */
status_t list_top (void *stack_ptr, void *buffer);

/**
 * @brief Удаляет верхний узел списка и освобождает его память.
 * @param[in] stack_ptr Указатель на стек.
 * @return 1 при успехе, 0 если стек пуст.
 */
status_t list_pop (void *stack_ptr);

/**
 * @brief Возвращает количество элементов в стеке.
 * @param[in] stack_ptr Указатель на стек.
 * @return Количество элементов или -1, если указатель NULL.
 */
int list_get_count (void *stack_ptr);

#endif