#include "matrix.h"

struct s_mtx_22          new_matrix_22(struct s_mtx_12 a, struct s_mtx_12 b)
{
    struct s_mtx_22      m;

    m.type = 4;
    m.a = a.a;
    m.b = a.b;
    m.c = b.a;
    m.d = b.b;
    return (m);
}
