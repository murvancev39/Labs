/**
 * @file arr_stack.h
 * @author Михаил Урванцев
 * @brief Реализация универсального стека на базе динамического массива.
 */

#ifndef ARR_STACK_H
#define ARR_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * @struct arr_stack
 * @brief Структура стека.
 * * Использует void* для для универсальности.
 */
struct arr_stack
{
    void *array;          /**< Указатель на массив данных */
    size_t employment;    /**< Текущее количество элементов в стеке */
    size_t capacity;      /**< Максимальная вместимость без переаллокации */
    size_t element_size;  /**< Размер одного элемента в байтах */
};

/**
 * @brief Конструктор стека с заданной начальной вместимостью.
 * @param[in] size Начальный размер массива.
 * @param[in] element_size Размер одного элемента (sizeof).
 * @return Указатель на созданный стек или NULL при ошибке памяти.
 */
void *arr_stack_ctr (size_t size, size_t element_size);

/**
 * @brief Упрощенный конструктор для тестов (начальный размер = 1).
 * @param[in] element_size Размер одного элемента.
 * @return Указатель на созданный стек или NULL.
 */
void *arr_stack_ctr_for_tests (size_t element_size);

/**
 * @brief Деструктор стека. Освобождает всю выделенную память.
 * @param[in] stack_ptr Указатель на стек.
 * @return Всегда возвращает NULL.
 */
void *arr_stack_dtr (void *stack_ptr);

/**
 * @brief Добавляет элемент в стек. При необходимости расширяет массив в 2 раза.
 * @param[in] stack_ptr Указатель на стек.
 * @param[in] buffer Указатель на данные, которые нужно скопировать в стек.
 * @return 1 при успехе, 0 при ошибке (NULL указатель или провал realloc).
 */
int arr_push (void *stack_ptr, void *buffer);

/**
 * @brief Копирует верхний элемент стека в буфер без удаления.
 * @param[in] stack_ptr Указатель на стек.
 * @param[out] buffer Указатель на область памяти, куда будет скопирован элемент.
 * @return 1 при успехе, 0 если стек пуст или указатель невалиден.
 */
int arr_top (void *stack_ptr, void *buffer);

/**
 * @brief Удаляет верхний элемент стека.
 * @details При достижении 1/4 заполненности от общего объема capacity, 
 * размер стека автоматически уменьшается вдвое.
 * @param[in] stack_ptr Указатель на стек.
 * @return 1 при успехе, 0 если стек пуст или указатель невалиден.
 * @note Уменьшение размера происходит только если итоговая capacity остается больше 4.
 */
int arr_pop (void *stack_ptr);

/**
 * @brief Возвращает текущее количество элементов в стеке.
 * @param[in] stack_ptr Указатель на стек.
 * @return Количество элементов или -1, если указатель на стек NULL.
 */
int arr_get_employment (void *stack_ptr);

#endif