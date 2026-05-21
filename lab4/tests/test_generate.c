#include "test_generate.h"
#include <stdlib.h>

unsigned *unsigned_test_gen (size_t size)
{
    if (size == 0) return NULL;

    srand (42);
    unsigned *arr = (unsigned *) malloc (size * sizeof (unsigned));
    if (!arr) return NULL;

    for (size_t i = 0; i < size; i++)
    {
        arr [i] = (unsigned) rand ();
    }
    return arr;
}

char **string_test_gen (size_t size)
{
    if (size == 0) return NULL;

    srand (42);
    char **arr = (char **) malloc (size * sizeof (char *));
    if (!arr) return NULL;

    for (size_t i = 0; i < size; i++)
    {
        int len = 5 + rand () % 16; 
        arr [i] = (char *) malloc ((unsigned) (len + 1) * sizeof (char));
        
        if (!arr [i])
        {
            for (size_t j = 0; j < i; j++)
            {
                free (arr [j]);
            }
            free (arr);
            return NULL;
        }
        
        for (int j = 0; j < len; j++)
        {
            arr [i][j] = (char) ('a' + rand () % 26);
        }
        arr [i][len] = '\0';
    }
    return arr;
}

float *float_test_gen (size_t size)
{
    if (size == 0) return NULL;

    srand (42);
    float *arr = (float *) malloc (size * sizeof (float));
    if (!arr) return NULL;

    for (size_t i = 0; i < size; i++)
    {
        float scale = (float) rand () / (float) RAND_MAX;
        arr [i] = -10.0f + scale * 20.0f;
    }
    return arr;
}