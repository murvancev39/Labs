/**
 * @file main.h
 * @brief Заголовочный файл для главного модуля тестирования.
 * 
 * Содержит настройки параметров тестирования и объявления 
 * функций-фабрик для инициализации интерфейсов структур данных.
 */

#ifndef MAIN_H
#define MAIN_H

#include "skip_list.h"
#include "avl_tree.h"
#include "bst_tree.h"
#include "crt_tree.h"
#include "spl_tree.h"
#include "test_gen.h"
#include "rb_tree.h"
#include "b_tree.h"
#include "tester.h"

#define BST_RAND_ALL   100000
#define BST_SORTED_ALL 10000

#define BIG_FROM 100000
#define BIG_TO   1000000
#define BIG_STEP 100000

/**
 * @brief Обрабатывает и выводит подробное описание ошибки в консоль.
 * @param error_code Код ошибки, полученный в процессе выполнения программы.
 */
void error_code_handling (error_code_t error_code);

/** @name Функции инициализации интерфейсов для структур данных */
/**@{*/

/**
 * @brief Инициализирует интерфейс для AVL-дерева.
 * @return Указатель на структуру interface_t с настроенными функциями AVL.
 */
interface_t *avl_interface  (unsigned from, unsigned to, unsigned step, char path []);

/**
 * @brief Инициализирует интерфейс для B-дерева.
 * @return Указатель на структуру interface_t с настроенными функциями B-дерева.
 */
interface_t *b_interface    (unsigned from, unsigned to, unsigned step, char path []);

/**
 * @brief Инициализирует интерфейс для BST (бинарного дерева поиска).
 * @return Указатель на структуру interface_t с настроенными функциями BST.
 */
interface_t *bst_interface  (unsigned from, unsigned to, unsigned step, char path []);

/**
 * @brief Инициализирует интерфейс для CRT-дерева.
 * @return Указатель на структуру interface_t с настроенными функциями CRT.
 */
interface_t *crt_interface  (unsigned from, unsigned to, unsigned step, char path []);

/**
 * @brief Инициализирует интерфейс для RB-дерева (красно-черного).
 * @return Указатель на структуру interface_t с настроенными функциями RB.
 */
interface_t *rb_interface   (unsigned from, unsigned to, unsigned step, char path []);

/**
 * @brief Инициализирует интерфейс для списка с пропусками (Skip List).
 * @return Указатель на структуру interface_t с настроенными функциями Skip List.
 */
interface_t *skip_interface (unsigned from, unsigned to, unsigned step, char path []);

/**
 * @brief Инициализирует интерфейс для Splay-дерева.
 * @return Указатель на структуру interface_t с настроенными функциями Splay.
 */
interface_t *spl_interface  (unsigned from, unsigned to, unsigned step, char path []);

/**@}*/

#endif