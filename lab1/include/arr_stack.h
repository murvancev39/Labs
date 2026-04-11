#ifndef ARR_STACK_H
#define ARR_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


struct arr_stack
{
    void *array;
    size_t employment;
    size_t capacity;
    size_t element_size;
};

void *arr_stack_ctr (size_t size, size_t element_size);
void *arr_stack_ctr_for_tests (size_t element_size);
void *arr_stack_dtr (void *stack_ptr);
int arr_push (void *stack_ptr, void *buffer);
int arr_top (void *stack_ptr, void *buffer);
int arr_pop (void *stack_ptr);
int arr_get_employment (void *stack_ptr);
#endif