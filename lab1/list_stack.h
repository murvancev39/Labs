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

struct Stack
{
    struct node *head;
    size_t employment;
    size_t element_size;
};

struct Stack* stack_ctr (size_t element_size);
int push(struct Stack* stack_ptr, void* buffer);
int top (struct Stack* stack_ptr, void* buffer);
int pop (struct Stack* stack_ptr);
struct Stack* stack_dtr (struct Stack* stack_ptr);
// void rec_delete (struct node *node);

#endif