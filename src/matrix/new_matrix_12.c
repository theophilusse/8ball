#include "matrix.h"

struct s_mtx_12          new_matrix_12(double a, double b)
{
    struct s_mtx_12      m;

    m.type = 2;
    m.a = a;
    m.b = b;
    return (m);
}
