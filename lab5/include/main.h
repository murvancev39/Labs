#ifndef MAIN_H
#define MAIN_H

#include "SKIP_list.h"
#include "AVL_tree.h"
#include "BST_tree.h"
#include "CRT_tree.h"
#include "SPL_tree.h"
#include "test_gen.h"
#include "RB_tree.h"
#include "B_tree.h"
#include "tester.h"

#define BST_RAND_ALL   100000
#define BST_SORTED_ALL 10000

#define BIG_FROM 100000
#define BIG_TO  1000000
#define BIG_STEP 100000

void error_code_handling (error_code_t error_code);
interface_t *AVL_interface  (unsigned from, unsigned to, unsigned step, char path []);
interface_t *B_interface    (unsigned from, unsigned to, unsigned step, char path []);
interface_t *BST_interface  (unsigned from, unsigned to, unsigned step, char path []);
interface_t *CRT_interface  (unsigned from, unsigned to, unsigned step, char path []);
interface_t *RB_interface   (unsigned from, unsigned to, unsigned step, char path []);
interface_t *SKIP_interface (unsigned from, unsigned to, unsigned step, char path []);
interface_t *SPL_interface  (unsigned from, unsigned to, unsigned step, char path []);

#endif