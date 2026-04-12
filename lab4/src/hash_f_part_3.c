#include "hash_f_part_3.h"

unsigned hash_f_s_len (char *key)
{
    return strlen (key);
}

unsigned hash_f_s_sum (char *key)
{
    unsigned sum = 0;
    char *one_char = key;
    while (*one_char != '\0')
    {
        sum += *one_char;
        one_char++;
    }
    return sum % 1000;
}

unsigned hash_f_s_polinom (char *key)
{
    unsigned sum = 0;
    unsigned i = 0;
    unsigned cur_coef = 1;
    while (key [i] != '\0')
    {
        sum += key [i] * cur_coef;
        cur_coef *= 31;
        i++;
    }
    return sum % 1000;
}

unsigned hash_f_s_crc32 (char *key)
{   
    const unsigned char *string = (const unsigned char *) key;
    unsigned len = strlen (key);
    unsigned init = 0xFFFFFFFF;
    unsigned crc = init;
    while (len--)
    {
        crc = (crc << 8) ^ crc32_table [((crc >> 24) ^ * string) & 255];
        string++;
    }
    return crc % 1000;
}   
