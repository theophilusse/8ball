#ifndef CAMERA_H
    #define CAMERA_H

    #include "8ball.h"

    #include "opencl_util.h"

    /**
     ** Author : ttrossea
     ** camera.h :
     ** Contain new_camera and several camera related functions (zbufs...).
     **
     ** Use new_camera to build a new_camera.
     **
     **
    **/

    #define CAMERA_PRESET_ORIGIN_X      0.0
    #define CAMERA_PRESET_ORIGIN_Y      0.0
    #define CAMERA_PRESET_ORIGIN_Z      -10.0

    #define CAMERA_PRESET_DIR_X         0.0
    #define CAMERA_PRESET_DIR_Y         0.0
    #define CAMERA_PRESET_DIR_Z         0.0

    /*#define CAMERA_WIDTH                5
    #define CAMERA_HEIGHT               3.75*/
    #define CAMERA_DIMENSION_FACTOR        1

    #define CAMERA_FOCAL_DISTANCE       1.0

    #define CAMERA_FREE_MODELSTACK 0
    #define CAMERA_KEEP_MODELSTACK 1

    #define CAMERA_MAX_FOCAL_DISTANCE     850


    void         camera_event(t_cam *camera, SDLKey sym);

    void            clear_zbuffer(double *zbuffer, int w, int h);
    t_cam           *new_camera(SDL_Surface *screen, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);
    void            reset_camera(t_cam *cam, int flag);

    void            refresh_orientation(t_cam *c);
    int             resize_camera_viewport(t_cam *c, t_opencl *cl, uint x, uint y);

    void            rotate_camera_pos_drag(t_cam *camera, int *dragVec);
    void            rotate_camera_dir_drag(t_cam *camera, int *dragVec);

    /** Mesh Loader **/
    void 		camera_release(t_mega *mega);
    int      push_model(t_camdata *d, uchar *amb_color,
                           double *vrt, double *nv, int *fce,
                           double *model_translate, double *model_rotate, double *model_scale);
    void     release_modelPointers(t_model *model);
    void     release_model(t_camdata *dat, uint objHandle);
    uint         model_getLastHandle(t_camdata *dat);

#endif // CAMERA_H
