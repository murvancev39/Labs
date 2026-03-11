#ifndef ARR_STACK_H
#define ARR_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


struct Stack
{
    void *array;
    size_t employment;
    size_t capacity;
    size_t element_size;
};

struct Stack *stack_ctr(size_t size, size_t element_size);
struct Stack* stack_dtr(struct Stack* stack_ptr);
int push (struct Stack* stack_ptr, void* buffer);
int top (struct Stack* stack_ptr, void* buffer);
int pop (struct Stack* stack_ptr);
#endif