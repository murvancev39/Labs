#include "list_stack.h"

void *list_stack_ctr (size_t element_size)
{
    struct list_stack *stack_ptr = (struct list_stack *) calloc (1, sizeof (struct list_stack));
    assert (stack_ptr);

    stack_ptr->employment = 0;
    stack_ptr->head = NULL;
    stack_ptr->element_size = element_size;

    return stack_ptr;
}

int list_push (void *stack_ptr, void *buffer)
{
    assert (stack_ptr);
    assert (buffer);
    struct list_stack *stack = stack_ptr;

    struct node *new_node = (struct node *) calloc (1, sizeof (struct node));
    if (new_node == NULL)
    {
        return 0;
    }

    new_node->elem = (void *) calloc (1, stack->element_size);
    if (new_node->elem == NULL)
    {
        free (new_node);
        return 0;
    }

    memcpy (new_node->elem, buffer, stack->element_size);

    void *next = stack->head;
    new_node->next = next;
    stack->head = new_node;

    stack->employment++;

    return 1;
}

int list_top (void *stack_ptr, void *buffer)
{
    assert (stack_ptr);
    assert (buffer);
    struct list_stack *stack = stack_ptr;

    if (stack->employment == 0)
    {
        return 0;
    }

    memcpy (buffer, stack->head->elem, stack->element_size);

    return 1;
}

int list_pop (void *stack_ptr)
{
    assert (stack_ptr);
    struct list_stack *stack = stack_ptr;

    if (stack->employment == 0)
    {
        return 0;
    }

    struct node *next = stack->head->next;

    free (stack->head->elem);
    free (stack->head);

    stack->head = next;
    stack->employment--;

    return 1;
}

void *list_stack_dtr (void *stack_ptr)
{
    assert (stack_ptr);
    struct list_stack *stack = stack_ptr;

    struct node *cur_node = stack->head;
    while (cur_node != NULL)
    {
        stack->head = stack->head->next;
        free (cur_node->elem);
        free (cur_node);
        cur_node = stack->head;
    }
    free (stack);
    return NULL;
}

int list_get_employment (void *stack_ptr)
{
    return ((int) (((struct list_stack *)stack_ptr)->employment));
}