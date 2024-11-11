#ifndef STRIP_MODEL
    #define STRIP_MODEL
    #include "model.h"

    static double        strip_v[STRIP_MAX_VERTICES] =
    {
        15,3,0, // Keep this: 8 * 3 = length
        -0.000466, -1.000000, -0.010163,
        -0.000466, -1.000000, -2.010163,
        -0.000466, 1.000000, -0.010163,
        -0.000466, 1.000000, -2.010163,
        -0.000466, -0.466242, -2.010163,
        -0.000466, -0.466242, -4.010163,
        -0.000466, 0.466242, -2.010163,
        -0.000466, 0.466242, -4.010162,
        -0.000466, -1.000000, 3.989837,
        -0.000466, -1.000000, 1.989837,
        -0.000466, 1.000000, 3.989837,
        -0.000466, 1.000000, 1.989837,
        -0.000466, -0.466242, 1.989837,
        -0.000466, -0.466242, -0.010163,
        -0.000466, 0.466242, 1.989837,
        -0.000466, 0.466242, -0.010163
    };

    static double          strip_n[STRIP_MAX_VERTICES] =
    {
        1,3,0,
        -1.0000 -0.0000 -0.0000
    };

    static int        strip_f[STRIP_MAX_VERTICES] =
    {
        // N_vertices, a, b, c, d, ..
        4, 1, 3, 4, 2,
        4, 5, 7, 8, 6,
        4, 9, 11, 12, 10,
        4, 13, 15, 16, 14,
        0 // EOF
    };
#endif // STRIP_MODEL