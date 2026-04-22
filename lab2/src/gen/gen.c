#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned get_rand_below (unsigned max_val);

int main (int argc, char *argv [])
{
    if (argc != 3) return 0;

    srand (time (NULL));
    
    unsigned size = 0, max_val = 0;
    
    size = atoi (argv [1]);
    max_val = atoi (argv [2]);

    if (max_val == RAND_MAX)
    {
        for (unsigned i = 0; i <= size; i++)
        {
            printf ("%u\n", rand ());
        }
        return 0;
    }
    for (unsigned i = 0; i <= size; i++)
    {
        printf ("%u\n", get_rand_below (max_val));
    }
    return 0;
}

unsigned get_rand_below (unsigned max_val)
{
    if (max_val == 0)
    {
        return 0;
    }
    unsigned val = rand ();
    unsigned range = (RAND_MAX / max_val) * max_val;
    while (val >= range)
    {
        val = rand ();
    }
    return val % max_val;
}