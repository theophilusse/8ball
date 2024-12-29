#include "geometry.h"

int         reverse_normal(t_triangle *T, struct s_point P)
{
    struct s_point  n_;
    struct s_point  n;

    copy_v3(T->n, (double *)&n);
    reverse_vec(n, &n_);
    add_v3((double *)&n, T->v0 , (double *)&n);
    add_v3((double *)&n_, T->v0, (double *)&n_);
    if (length3((double *)&n_) < length3((double *)&n))
    {
        reverse_vec(*((t_point *)T->n), (t_point *)T->n);
        return (1);
    }
    return (0);
}
