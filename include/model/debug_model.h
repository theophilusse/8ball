#ifndef DEBUG_MODEL
    #define DEBUG_MODEL
    #include "model.h"

    static const double        debug_v[DEBUG_MAX_VERTICES] =
    {
        3,3,0, // Keep this: 8 * 3 = length
        0.000000, 0.000000, 0.000000,
        1.000000, 0.000000, 0.000000,
        0.000000, 1.000000, 0.000000
    };

    static const double          debug_n[DEBUG_MAX_VERTICES] =
    {
        1,3,0,
        0.0000, 0.0000, 1.0000
    };

    static const int        debug_f[DEBUG_MAX_VERTICES] =
    {
        // N_vertices, a, b, c, d, ..
        3, 1, 2, 3,
        0 // EOF
    };
#endif // DEBUG_MODEL
