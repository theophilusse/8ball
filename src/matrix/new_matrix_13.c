#include "matrix.h"

struct s_mtx_13          new_matrix_13(double a, double b, double c)
{
    struct s_mtx_13      m;

    m.type = 3;
    m.a = a;
    m.b = b;
    m.c = c;
    return (m);
}
