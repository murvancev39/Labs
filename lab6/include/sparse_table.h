#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H


#include <stdio.h>
#include <stdlib.h>

typedef struct Sparse_t
{
    unsigned n;
    unsigned logn;
    char *lg_arr;
    unsigned **table;
} sparse_t;

void       destruct_v_n    (sparse_t *table);
void       destruct_v_logn (sparse_t *table);
void      *create_v_n      (unsigned *arr, unsigned len);
void      *create_v_logn   (unsigned *arr, unsigned len);
unsigned   min             (unsigned first, unsigned second);
sparse_t  *free_in_create  (sparse_t *table, unsigned error_string_idx);
long long  rmq_v_n         (sparse_t *table, unsigned left, unsigned right);
long long  rmq_v_logn      (sparse_t *table, unsigned left, unsigned right);

#endif