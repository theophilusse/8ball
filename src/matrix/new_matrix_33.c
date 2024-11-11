#include "matrix.h"

struct s_mtx_33          new_matrix_33(struct s_mtx_13 a, struct s_mtx_13 b, struct s_mtx_13 c)
{
    struct s_mtx_33      m;

    m.type = 9;
    m.a = a.a;
    m.b = a.b;
    m.c = a.c;
    m.d = b.a;
    m.e = b.b;
    m.f = b.c;
    m.g = c.a;
    m.h = c.b;
    m.i = c.c;
    return (m);
}
