/**
 * @file hash_f_part_3.c
 * @brief Реализация алгоритмов хеширования строк и компаратора.
 */

#include "hash_f_part_3.h"

unsigned hash_f_s_len (void *key)
{
    return (unsigned) strlen ((char *) key);
}

unsigned hash_f_s_sum (void *key)
{
    unsigned sum = 0;
    char *one_char = (char *) key;
    while (*one_char != '\0')
    {
        sum += (unsigned) *one_char;
        one_char++;
    }
    return sum;
}

unsigned hash_f_s_polinom (void *key)
{
    unsigned sum = 0;
    unsigned i = 0;
    unsigned cur_coef = 1;
    unsigned char x = 0;
    while ((x = (unsigned char) (((unsigned char *) key) [i])) != '\0')
    {
        sum += x * cur_coef;
        cur_coef *= 31;
        i++;
    }
    return sum;
}

unsigned hash_f_s_src32 (void *key)
{   
    const unsigned char *string = (const unsigned char *) key;
    unsigned len = (unsigned) strlen (key);
    unsigned init = 0xFFFFFFFF;
    unsigned src = init;
    while (len--)
    {
        src = (src << 8) ^ crc32_table [((src >> 24) ^ * string) & 255];
        string++;
    }
    return src;
}   

int string_cmp (void *key1, void *key2)
{
    return strcmp ((const char *) key1, (const char *) key2);
}
