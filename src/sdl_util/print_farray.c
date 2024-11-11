#include "8ball.h"


//** printf_array **//
// Arg1: Pointer to float array
// Arg2: The actual length of array
// Arg3: (optionnal) write a newline every mod float printed
//
void            print_farray(float *f, uint length, uint *mod)
{
    uint            i;
    uint            mod_;

    if (mod)
        mod_ = *mod;
    if (length == 0 || !f)
        return ;
    i = -1;
    while (++i < length)
        if ((mod && i % mod_ == 0) || (!mod && i != 0 && (i + 1) % 3 == 0))
            printf("[%f]\n", *(f++));
        else
            printf("[%f]", *(f++));
}
