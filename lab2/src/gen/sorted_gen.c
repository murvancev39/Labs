#include <stdio.h>
#include <stdlib.h>

int compare (const void *a, const void *b);

int main (int argc, char *argv [])
{
    if (argc != 2) return 1;

    unsigned size = atoi (argv [1]);
    if (size == 0)
    {
        return 0;
    }
    unsigned *arr = (unsigned *) calloc (size, sizeof (unsigned));

    for (unsigned i = 0; i < size; i++)
    {
        scanf ("%u", arr + i);
    }

    qsort (arr, size, sizeof (unsigned), compare);

    for (unsigned i = 0; i < size; i++)
    {
        printf ("%u\n", arr [i]);
    }

    free (arr);
    return 0;
}

int compare (const void *a, const void *b) 
{
    if (*(int *) a < *(int *) b) return -1;
    if (*(int *) a == *(int *) b) return 0;
    return 1;
}