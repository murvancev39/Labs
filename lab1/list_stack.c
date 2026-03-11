#include "list_stack.h"

struct Stack* stack_ctr (size_t element_size)
{
    struct Stack *stack_ptr = (struct Stack *) calloc (1, sizeof (struct Stack));
    assert (stack_ptr);
    stack_ptr->employment = 0;
    stack_ptr->head = NULL;
    stack_ptr->element_size = element_size;
    return stack_ptr;
}

int push (struct Stack* stack_ptr, void* buffer)
{
    assert (stack_ptr);
    assert (buffer);

    struct node *new_node = (struct node *) calloc (1, sizeof (struct node));
    if (new_node == NULL)
    {
        return 0;
    }
    new_node->elem = (void *) calloc (1, stack_ptr->element_size);
    if (new_node->elem == NULL)
    {
        free (new_node);
        return 0;
    }

    memcpy (new_node->elem, buffer, stack_ptr->element_size);

    void *next = stack_ptr->head;
    new_node->next = next;
    stack_ptr->head = new_node;

    stack_ptr->employment++;
    return 1;
}

int top (struct Stack* stack_ptr, void* buffer)
{
    assert (stack_ptr);
    assert (buffer);
    if (stack_ptr->employment == 0)
    {
        return 0;
    }

    memcpy (buffer, stack_ptr->head->elem, stack_ptr->element_size);
    return 1;
}

int pop (struct Stack* stack_ptr)
{
    assert (stack_ptr);
    if (stack_ptr->employment == 0)
    {
        return 0;
    }

    struct node* next = stack_ptr->head->next;
    free (stack_ptr->head->elem);
    free (stack_ptr->head);
    stack_ptr->head = next;
    stack_ptr->employment--;
    return 1;
}

struct Stack* stack_dtr (struct Stack* stack_ptr)
{
    assert (stack_ptr);
    struct node *cur_node = stack_ptr->head;
    while (cur_node != NULL)
    {
        stack_ptr->head = stack_ptr->head->next;
        free (cur_node->elem);
        free (cur_node);
        cur_node = stack_ptr->head;
    }
    free (stack_ptr);
    return NULL;
}