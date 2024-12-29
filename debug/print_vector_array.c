#include "dbg_util.h"

void            print_vector_array(double *parray, uint id)
{
    char        sign = '\n';

    id += 12;
    printf("double4 dump:");
    while (id-- > 12)
    {
        if ((id + 1) % 4 == 0)
        {
            printf("%c%f ", sign, *(parray++));
            sign = (id + 1) % 16 == 0 ? '\n' : '\t';
        }
        else
            printf("%f ", *(parray++));
    }
    printf("\n");
}
