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
#include "status.h"

#define NARROWING_KOEFF 4
#define EXPANSION_KOEFF 2

/**
 * @struct arr_stack_t
 * @brief Структура стека.
 * * Использует void* для для универсальности.
 */
typedef struct arr_stack_t
{
    void *array;          /**< Указатель на массив данных */
    size_t count;    /**< Текущее количество элементов в стеке */
    size_t capacity;      /**< Максимальная вместимость без переаллокации */
    size_t element_size;  /**< Размер одного элемента в байтах */
} arr_stack_t;

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
status_t arr_push (void *stack_ptr, void *buffer);

/**
 * @brief Расширяет емкость стека в 2 раза при достижении лимита.
 * * @details Функция выделяет новый блок памяти под массив данных с помощью realloc,
 * увеличивая текущее значение поля capacity в EXPANSION_KOEFF раз, и обновляет указатель на массив.
 * * @param[in,out] stack_ptr Указатель на структуру стека.
 * @return STATUS_OK (1) при успешном перевыделении памяти.
 * @return STATUS_ERR (0) если stack_ptr равен NULL или произошла ошибка выделения памяти (realloc вернул NULL).
 * * @note Данная функция является вспомогательной и вызывается внутри arr_push,
 * когда (count) становится равным максимальной вместимости (capacity).
 */
status_t arr_expansion (void *stack_ptr);

/**
 * @brief Копирует верхний элемент стека в буфер без удаления.
 * @param[in] stack_ptr Указатель на стек.
 * @param[out] buffer Указатель на область памяти, куда будет скопирован элемент.
 * @return 1 при успехе, 0 если стек пуст или указатель невалиден.
 */
status_t arr_top (void *stack_ptr, void *buffer);

/**
 * @brief Удаляет верхний элемент стека.
 * @details При достижении 1/4 заполненности от общего объема capacity, 
 * размер стека автоматически уменьшается вдвое.
 * @param[in] stack_ptr Указатель на стек.
 * @return 1 при успехе, 0 если стек пуст или указатель невалиден.
 * @note Уменьшение размера происходит только если итоговая capacity остается больше 4.
 */
status_t arr_pop (void *stack_ptr);

/**
 * @brief Уменьшает емкость стека в 2 раза для экономии памяти.
 * * @details Функция освобождает неиспользуемую память с помощью realloc,
 * уменьшая текущее значение поля capacity вдвое, если стек стал полупустым.
 * * @param[in,out] stack_ptr Указатель на структуру стека.
 * @return STATUS_OK (1) при успешном перевыделении памяти и уменьшении емкости.
 * @return STATUS_ERR (0) если stack_ptr равен NULL или если realloc не смог выделить измененный блок памяти.
 * * @note Данная функция является вспомогательной и вызывается внутри arr_pop,
 * когда текущее количество элементов (count) становится меньше емкости (capacity) в NARROWING_KOEF раз.
 * Ошибка realloc здесь не критична для работы стека, так как старые данные и прежний размер массива сохраняются.
 */
status_t arr_narrowing (void *stack_ptr);

/**
 * @brief Возвращает текущее количество элементов в стеке.
 * @param[in] stack_ptr Указатель на стек.
 * @return Количество элементов или -1, если указатель на стек NULL.
 */
int arr_get_count (void *stack_ptr);

#endif