#ifndef CUBE_MODEL
    #define CUBE_MODEL
    #include "model.h"

    ///static const double        cube_v[CUBE_MAX_VERTICES] =
    static double        cube_v[CUBE_MAX_VERTICES] =
    {
        8, 3, 0, // Keep this: 8 * 3 = length
        1.000000, -1.000000, -1.000000,
        1.000000, -1.000000, 1.000000,
        -1.000000, -1.000000, 1.000000,
        -1.000000, -1.000000, -1.000000,
        1.000000, 1.000000, -1.000000,
        1.000000, 1.000000, 1.000000,
        -1.000000, 1.000000, 1.000000,
        -1.000000, 1.000000, -1.000000
    };

    ///static const double          cube_n[CUBE_MAX_VERTICES] =
    static double          cube_n[CUBE_MAX_VERTICES] =
    {
        6, 3, 0,
        0.0000, -1.0000, 0.0000,
        0.0000, 1.0000, 0.0000,
        1.0000, 0.0000, 0.0000,
        -0.0000, -0.0000, 1.0000,
        -1.0000, -0.0000, -0.0000,
        0.0000, 0.0000, -1.0000
    };

    ///static const int        cube_f[CUBE_MAX_VERTICES] =
    static int        cube_f[CUBE_MAX_VERTICES] =
    {
        // N_vertices, a, b, c, d, ..
        4, 1, 2, 3, 4,
        4, 5, 8, 7, 6,
        4, 1, 5, 6, 2,
        4, 2, 6, 7, 3,
        4, 3, 7, 8, 4,
        4, 5, 1, 4, 8,
        0
    };
#endif // CUBE_MODEL
