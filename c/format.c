#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

int check_block_is_open(char *template)
{
    int block_open = 0;

    for ( int i=0; i < strlen(template); i++ )
    {
        if ( template[i] == '{' )
        {
            block_open += 1;
        }

        if ( template[i] == '}' )
        {
            block_open -= 1;
        }
    }

    return block_open;
}

char *replace(char *template, dict *d)
{
    int si = 0;
    int ei = 0;
    int size = strlen(template);

    // TODO
    // need to alloc mem dynamic

    char *ret = (char *)malloc(size * 2);
    int j = 0;
    int inblock = 0;

    for ( int i=0; i < size; i++)
    {
        if ( template[i] == '{' && inblock != 1)
        {
            // found the block
            si = i;
            inblock = 1;
            continue;
        }

        if ( template[i] == '}' )
        {
            // end of the block
            ei = i;
            int range = ei - si;
            char *tmp = (char *)malloc(range * sizeof(char*));
            int it = 0;

            // get the key of the dict
            for (int ti=si + 1; ti < ei; ti++)
            {
                tmp[it] = template[ti];
                it++;
            }
            tmp[it] = '\0';

            // get the value of the dict
            char *value = get_value_by_key(d, tmp);

            if ( value )
            {
                for( int ti=0; ti < strlen(value); ti++ )
                {
                    ret[j] = value[ti];
                    j++;
                }
            }

            free(tmp);

            si = 0;
            ei = 0;
            inblock = 0;
            continue;
        }

        if (inblock)
        {
            continue;
        }

        ret[j] = template[i];
        j++;
    }

    ret[j] = '\0';

    return ret;
}