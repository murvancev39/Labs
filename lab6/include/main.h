#ifndef MAIN_H
#define MAIN_H

#include "tester.h"

#include "fenw.h"
#include "sparse_table.h"
#include "segment_tree.h"

#define FROM 1000000
#define TO   1000000
#define STEP 1000000

interface_t *RMQ_N_LOGN_interface        (unsigned from, unsigned to, unsigned step, char path []);
interface_t *RMQ_LOGN_N_interface        (unsigned from, unsigned to, unsigned step, char path []);
interface_t *RSQ_FENW_interface          (unsigned from, unsigned to, unsigned step, char path []);
interface_t *RSQ_SEG_interface_interface (unsigned from, unsigned to, unsigned step, char path []);

void error_code_handling (error_code_t error_code);

void         destruct_v_n_wrapp       (void *table);
error_code_t rmq_search_v_n_wrapp     (void *table, unsigned int left, unsigned int right);

void         destruct_v_logn_wrapp    (void *table);
error_code_t rmq_search_v_logn_wrapp  (void *table, unsigned int left, unsigned int right);

void         fenw_destructor_wrapp    (void *table);
error_code_t fenw_search_wrapp        (void *table, unsigned int left, unsigned int right);
error_code_t fenw_update_wrapp        (void *table, unsigned int left, unsigned int right);

void         seg_tree_destructor_wrapp(void *table);
error_code_t seg_tree_search_wrapp    (void *table, unsigned int left, unsigned int right);
error_code_t seg_tree_update_wrapp    (void *table, unsigned int left, unsigned int right);


#endif