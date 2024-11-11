#ifndef MODEL_H
    #define MODEL_H

    #include "8ball.h"

    #define MASK_MAX_VERTICES       800
    #define STRIP_MAX_VERTICES      128
    #define WAVE_MAX_VERTICES       128
    #define CARPET_MAX_VERTICES     32000
    #define CUBE_MAX_VERTICES       128
    #define TEAPOT_MAX_VERTICES     18800
    #define DEBUG_MAX_VERTICES      32
    #define MIKO_MAX_VERTICES       13933
    #define PUTIN_MAX_VERTICES      2123
    #define DISC_MAX_VERTICES       1013
    #define LOL_MAX_VERTICES        61463
    #define UVSPHERE_MAX_VERTICES   307223
    #define KNIGHT_MAX_VERTICES     2903
    #define PUNK_MAX_VERTICES       3083
    #define BUST_MAX_VERTICES       7823

    #define BUSTHD_MAX_VERTICES 122393
    #define BUSTHD_MAX_FACES 12160

    /**
    #include "putin_model.h"
    #include "disc_model.h"
    #include "miko_model.h"

    #include "debug_model.h"
    #include "punk_model.h"
    #include "lol_model.h"
    **/
    /*#include "debug_model.h"
    #include "wave_model.h"
    #include "strip_model.h"
    #include "knight_model.h"
    */
    //#include "carpet_model.h"
    /*#include "teapot_model.h"
    #include "mask_model.h"*/
    #include "bust_model.h"
    #include "cube_model.h"
    //#include "uvsphere_model.h"
    #include "lights.h"
    ///#include "bustHD_model.h"

    int         copy_model(double *vrt, double *nv, int *fce, double *ovrt, double *onv, int *ofce);

#endif // MODEL_H
