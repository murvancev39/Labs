#include "test_generate.h"

unsigned *unsigned_test_gen (size_t size)
{
    srand (42);
    unsigned *arr = (unsigned *) malloc (size * sizeof (unsigned));
    for (size_t i = 0; i < size; i++)
    {
        arr [i] = rand ();
    }
    return arr;
}

char **string_test_gen (size_t size)
{
    srand (42);
    char **arr = (char **) malloc (size * sizeof (char *));
    for (size_t i = 0; i < size; i++)
    {
        int len = 5 + rand () % 16; 
        arr [i] = (char *) malloc ((len + 1) * sizeof (char));
        
        for (int j = 0; j < len; j++)
        {
            arr [i][j] = 'a' + rand () % 26;
        }
        arr [i][len] = '\0';
    }
    return arr;
}


float *float_test_gen (size_t size)
{
    srand (42);
    float *arr = (float *) malloc (size * sizeof (float));
    for (size_t i = 0; i < size; i++)
    {
        float scale = (float) rand () / (float) RAND_MAX;
        arr [i] = -10.0f + scale * 20.0f;
    }
    return arr;
}