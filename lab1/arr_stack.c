#include "arr_stack.h"

struct Stack *stack_ctr(size_t size, size_t element_size)
{
    struct Stack *stack_ptr = (struct Stack *) calloc (1, sizeof (struct Stack));
    assert (stack_ptr);

    stack_ptr->array = (void *) calloc (size, element_size);
    if (stack_ptr->array == NULL)
    {
        free (stack_ptr);
        assert (0 && "stack_ptr->array == NULL | memory allocation error\n");
    }
    stack_ptr->element_size = element_size;
    stack_ptr->capacity = size;
    stack_ptr->employment = 0;
    return stack_ptr;
}

struct Stack* stack_dtr(struct Stack* stack_ptr)
{
    assert (stack_ptr);
    free (stack_ptr->array);
    free (stack_ptr);
    return NULL;
}

int push (struct Stack* stack_ptr, void* buffer)
{
    assert (stack_ptr);
    assert (buffer);
    if (stack_ptr->employment != stack_ptr->capacity - 1)
    {
        memcpy (stack_ptr->array + stack_ptr->element_size * stack_ptr->employment, buffer, stack_ptr->element_size);
        stack_ptr->employment++;
        return 1;
    }
    else
    {
        size_t new_size = stack_ptr->capacity * 2;
        int *array_pointer = realloc (stack_ptr->array, new_size * stack_ptr->element_size);
        if (array_pointer == NULL)
        {
            return 0;
        }
        stack_ptr->array = array_pointer;
        stack_ptr->capacity = new_size;
        memcpy (stack_ptr->array + stack_ptr->element_size * stack_ptr->employment, buffer, stack_ptr->element_size);
        stack_ptr->employment++;
        return 1;
    }
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
    else
    {
        memcpy (buffer, stack_ptr->array + (stack_ptr->employment - 1)* stack_ptr->element_size, stack_ptr->element_size);
        return 1;
    }
}

int pop (struct Stack* stack_ptr)
{
    assert (stack_ptr);
    if (stack_ptr->employment == 0)
    {
        return 0;
    }
    stack_ptr->employment--;
    return 1;
}