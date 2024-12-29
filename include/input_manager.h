#ifndef INPUT_MANAGER_H
    #define INPUT_MANAGER_H

    #include "8ball.h"
    /*#define INPUT_MANAGER_FTSZ      24*/

    #define USER_QUIT                         0
    #define USER_RESIZE_WINDOW                1
    #define USER_SWITCH_MODEL_VIEW            2
    #define USER_SWITCH_CLOUD_VIEW            3
    #define USER_KEY_UP                       4
    #define USER_KEY_DOWN                     5
    #define USER_MOUSE_BUTTON_UP              6
    #define USER_MOUSE_BUTTON_DOWN            7
    #define USER_MOUSE_MOTION                 8
    #define USER_COMPUTE_CLOUD                9
    #define USER_MOUSE_MOTION_CAMERA_DRAGPOS  10
    #define USER_MOUSE_MOTION_CAMERA_DRAGDIR  11
    #define USER_MOUSE_MOTION_IDLE            12
    #define USER_CAMERA_ZOOM                  13
    #define USER_ON_LEFT_CLICK                14
    #define USER_CANVA_CLICK                  15
    #define USER_INTERFACE_CLICK              16
    #define USER_MORPHO_CLICK                 17
    /*#define USER_MOUSE_MOTION_HUD             16
    #define USER_MOUSE_MOTION_RADIUS_HUD      17
    #define USER_MOUSE_MOTION_ANGLE_HUD       18*/

    /**
     ** Input Manager.
     ** Input -> Pointer Table -> Input Function
    **/

    ///extern int (*input_manager_[INPUT_MANAGER_FTSZ])(t_mega *, int); /// Verify syntax array[]


    int             user_quit(t_mega *mega, int flg);
    int             user_resizeWindow(t_mega *mega, int flg);
    int             user_switchModelView(t_mega *mega, int flg);
    int             user_switchCloudView(t_mega *mega, int flg);
    int             user_keydown(t_mega *mega, int flg);
    int             user_keyup(t_mega *mega, int flg);
    int             user_morphoClick(t_mega *mega, int flg);
    int             user_mouseButtonUp(t_mega *mega, int flg);
    int             user_mouseButtonDown(t_mega *mega, int flg);
    int             user_mouseMotion(t_mega *mega, int flg);
    int             user_computeCloud(t_mega *mega, int flg); /// GPU fall()
    void            *td_computeCloudFall(void *p_mega); /// *** ///
    int             user_computeCloud_CPU(t_mega *mega, int flg); /// CPU fall()
    int             user_cameraDrag(t_mega *mega, int flg);
    int             user_cameraDragDir(t_mega *mega, int flg);
    int             user_idle(t_mega *mega, int flg);
    int             user_cameraZoom(t_mega *mega, int flg);
    int             user_onLeftClick(t_mega *mega, int flg);
    int             user_canvaClick(t_mega *mega, int flg);

    int             user_interfaceClick(t_mega *mega, int flg); // New

    /*int             user_mouseMotionHUD(t_mega *mega, int flg);
    int             user_mouseMotionRadiusHUD(t_mega *mega, int flg);
    int             user_mouseMotionAngleHUD(t_mega *mega, int flg);*/

    void            rotate_camera_pos_drag(t_cam *camera, int *dragVec);
    void            rotate_camera_dir_drag(t_cam *camera, int *dragVec);

    ///int         inputManager_loop(struct s_mega mega, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);
    int         inputManager_loop(t_mega *mega, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);

#endif // INPUT_MANAGER_H
