#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct node
{
    void *elem;
    struct node *next;
};

struct list_stack
{
    struct node *head;
    size_t employment;
    size_t element_size;
};

void *list_stack_ctr (size_t element_size);
void *list_stack_dtr (void *stack_ptr);
int list_push (void *stack_ptr, void *buffer);
int list_top (void *stack_ptr, void *buffer);
int list_pop (void *stack_ptr);
int list_get_employment (void *stack_ptr);

#endif