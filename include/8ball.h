#ifndef HEIGHTBALL_H
    #define HEIGHTBALL_H

   #ifdef __cplusplus
        #include <cstdlib>
    #else
        #include <stdlib.h>
    #endif

    #ifdef LINUX_PLATEFORM
        #define BEEP                    printf("\a");              /* play Printf beep */
    #else
        #include <windows.h>
        #define BEEP                    MessageBeep(MB_OK);              /* play Windows default beep */
        #define BEEP_INFORMATION        MessageBeep(MB_ICONINFORMATION); /* play asterisk sound */
        #define BEEP_QUESTION           MessageBeep(MB_ICONQUESTION);    /* play question sound */
        #define BEEP_WARNING           MessageBeep(MB_ICONWARNING);     /* play warning sound */
    #endif

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #include <time.h>
    #ifndef PTHREAD_HEADER
        #include <pthread.h>
    #endif

    #define CL_USE_DEPRECATED_OPENCL_1_2_APIS
    #define CL_TARGET_OPENCL_VERSION 220
    #ifdef MAC
        #include <OpenCL/cl.h>
    #else
        #include "cl.h"
    #endif

    /** Debug Macros **/
    #include "todo_string.h"
    #define DEBUG_TODO      printf("Todo : [%s] %s - %s : %u\n", _todo_string_, __FILE__, __func__, __LINE__);

    /** Cloud Computing Method **/
    //#define COMPUTE_CLOUD_GPU /// GPU fall()
    #define COMPUTE_CLOUD_CPU
    #define THREAD_COUNT        8


    /** Const **/
    //#define EPSILON         (0.000001)
    #define EPSILON         (0.000000000001)

    #define PI_2                  1.57079632679489
    #define PI                    3.14159265358979
    #define PI2                   6.28318530717958
    #define DEBUG                       printf("%s - %s : %u\n", __FILE__, __func__, __LINE__);
    ///#define DEBUG                       user_idle(NULL, 0); /// (build)
    #define TINY_STRING_SIZE            128
    #define STRING_SIZE                 255

    #define INPUT_MANAGER_FTSZ         32
    #define TOOLSET_SIZE               16

    #define UI_CURSOR_COUNT             16
    #define UI_BOX_COUNT                255
    #define UI_BOX_TITLE_STRLEN         32
    ///#define UI_BOX_CONTENT_MAX_ITEM     16
    #define UI_BOX_CONTENT_MAX_ITEM     128

    /**
        #define MOUSE_OOB
    **/

    /*#define WINX            640
    #define WINY            480*/
    /***#define WINX            1300
    #define WINY            975***/

    ////#define FULLSCREEN_MOD
    ///#define WINX        1500
    ///#define WINY        750
    #define WINX        1024
    #define WINY        512
    /** #define FULLSCREEN_MOD **/
    static int         global_winx;
    static int         global_winy;

    #include <SDL/SDL.h>

    typedef unsigned int    uint;
    typedef unsigned char   uchar;

    #include "my_color_table.h"
    #include "model.h"

    ///#define MODEL_SCALE         (0.2)
    #define MODEL_SCALE         (1.0) /* Monkey */
    ///#define MODEL_SCALE         (0.5)

    ///void            drawTriangle(SDL_Surface *s, uchar *rgb, int *v1, int *v2, int *v3);

    #define MAX_MODEL               100

    /*** #define DEBUG_TRIANGLE ***/
    static Uint32          rmask, gmask, bmask, amask;
    static const void            *global_mega;

    #include "float.h"

    #include "macro/logical_shrinker.h"
    #include "macro/NATOphonetic.h"

    #include "dbg_util.h"

    #include "structures.h"

    #ifdef CUSTOM_ALLOC
        #include "memmgr.h"
    #else
        #define ALLOC(sz) \
            ((void *)malloc(sz))
        #define FREE(ptr) \
            (free(ptr))
    #endif

    #include "camera.h"

    #include "alphabet_tileset.h"
    #include "geometry.h"
    ///#include "HeightMap.h" /** Obsolete **/
    #include "rasterization.h" /** Obsolete ? **/
    #include "str_util.h"
    #include "sdl_util.h"
    #include "opencl_util.h"
    #include "ft_gpu.h"
    #include "toolset.h"
    #include "mouse.h"
    #include "filesystem.h"
    #include "export.h"
    #include "import.h"
    #include "hud.h"
    #include "morpho.h"
    #include "frame.h"
    #include "history.h"
    #include "user_interface.h"
    #include "helloworld.h"

    #ifndef HEIGHT_BALL
     #define HEIGHT_BALL
        SDL_Surface          *init_(void);
        /*int                  push_model(t_camdata *d, uchar *amb_color,
                                    double *vrt, double *nv, int *fce,
                                    double *model_translate, double *model_rotate, double *model_scale);*/
        t_mega               *mega_construct(Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask, const char *picture_filename);
        int             root_destructor(t_mega *mega, int isErr);
        //void            loading_bar(SDL_Surface *surface, float from_percent, float percent);
    #endif

    #include "input_manager.h"
    /*void            charset_print(SDL_Surface *s, SDL_Surface **charset, int x, int y, const char *str);
    SDL_Surface     **load_charset(const uchar *color_bg, const uchar *color_fg);*/

    #include "ascii_art_box.h"
#endif // HEIGHTBALL_H
