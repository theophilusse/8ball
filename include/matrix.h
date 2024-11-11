#ifndef MATRIX_H
#define MATRIX_H

    #include "8ball.h"

    struct s_mtx_12          new_matrix_12(double a, double b);
    struct s_mtx_13          new_matrix_13(double a, double b, double c);
    struct s_mtx_22          new_matrix_22(struct s_mtx_12 a, struct s_mtx_12 b);
    struct s_mtx_33          new_matrix_33(struct s_mtx_13 a, struct s_mtx_13 b, struct s_mtx_13 c);

#endif
