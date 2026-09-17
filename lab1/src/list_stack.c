#include "list_stack.h"

void *list_stack_ctr (size_t element_size)
{
    list_stack_t *stack_ptr = (list_stack_t *) calloc (1, sizeof (list_stack_t));

    if (!stack_ptr) return NULL;

    stack_ptr->count = 0;
    stack_ptr->head = NULL;
    stack_ptr->element_size = element_size;

    return stack_ptr;
}

status_t list_push (void *stack_ptr, void *buffer)
{
    if (!buffer) return STATUS_ERR;
    if (!stack_ptr) return STATUS_ERR;
    
    list_stack_t *stack = stack_ptr;

    node_t *new_node = (node_t *) calloc (1, sizeof (node_t));
    if (new_node == NULL)
    {
        return STATUS_ERR;
    }

    new_node->elem = (void *) calloc (1, stack->element_size);
    if (new_node->elem == NULL)
    {
        free (new_node);
        return STATUS_ERR;
    }

    memcpy (new_node->elem, buffer, stack->element_size);

    void *next = stack->head;
    new_node->next = next;
    stack->head = new_node;

    stack->count++;

    return STATUS_OK;
}

status_t list_top (void *stack_ptr, void *buffer)
{
    if (!buffer) return STATUS_ERR;
    if (!stack_ptr) return STATUS_ERR;

    list_stack_t *stack = stack_ptr;

    if (stack->count == 0)
    {
        return STATUS_ERR;
    }

    memcpy (buffer, stack->head->elem, stack->element_size);

    return STATUS_OK;
}

status_t list_pop (void *stack_ptr)
{
    if (!stack_ptr) return STATUS_ERR;

    list_stack_t *stack = stack_ptr;

    if (stack->count == 0)
    {
        return STATUS_ERR;
    }

    node_t *next = stack->head->next;

    free (stack->head->elem);
    free (stack->head);

    stack->head = next;
    stack->count--;

    return STATUS_OK;
}

void *list_stack_dtr (void *stack_ptr)
{
    assert (stack_ptr);

    list_stack_t *stack = stack_ptr;
    node_t *cur_node = stack->head;
    
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

int list_get_count (void *stack_ptr)
{
    if (!stack_ptr) return -1;
    return ((int) (((list_stack_t *)stack_ptr)->count));
}
