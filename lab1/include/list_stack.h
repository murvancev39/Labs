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

/**
 * @struct node
 * @brief Узел односвязного списка.
 */
struct node
{
    void *elem;         /**< Указатель на данные элемента */
    struct node *next;  /**< Указатель на следующий узел (ниже по стеку) */
};

/**
 * @struct list_stack
 * @brief Структура стека на основе списка.
 */
struct list_stack
{
    struct node *head;    /**< Указатель на верхний узел */
    size_t employment;    /**< Текущее количество элементов */
    size_t element_size;  /**< Размер одного элемента в байтах */
};

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
 * @details Для каждого элемента аллоцируется новый узел struct node и память под сами данные.
 * @param[in] stack_ptr Указатель на стек.
 * @param[in] buffer Указатель на данные для копирования.
 * @return 1 при успехе, 0 при ошибке аллокации.
 */
int list_push (void *stack_ptr, void *buffer);

/**
 * @brief Копирует данные из верхнего узла в буфер.
 * @param[in] stack_ptr Указатель на стек.
 * @param[out] buffer Указатель на память для копирования данных.
 * @return 1 при успехе, 0 если стек пуст.
 */
int list_top (void *stack_ptr, void *buffer);

/**
 * @brief Удаляет верхний узел списка и освобождает его память.
 * @param[in] stack_ptr Указатель на стек.
 * @return 1 при успехе, 0 если стек пуст.
 */
int list_pop (void *stack_ptr);

/**
 * @brief Возвращает количество элементов в стеке.
 * @param[in] stack_ptr Указатель на стек.
 * @return Количество элементов или -1, если указатель NULL.
 */
int list_get_employment (void *stack_ptr);

#endif