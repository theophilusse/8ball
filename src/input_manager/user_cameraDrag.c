#include "input_manager.h"

int         user_cameraDrag(t_mega *mega, int flg)
{
    double              Up[3];
    int                 antiDrag[2];
    struct s_mouse      mouse;

    if (!mega || !mega->camera)
        return (1);
    mouse = mega->mouse;
    Up[0] = 0;
    Up[1] = 1;
    Up[2] = 0;
    if (dot_prod3(mega->camera->uy, Up) <= -DBL_EPSILON)
    {
        antiDrag[0] = -mouse.mouseDrag[0];
        antiDrag[1] = mouse.mouseDrag[1];
        rotate_camera_pos_drag(mega->camera, antiDrag);
    }
    else
        rotate_camera_pos_drag(mega->camera, mouse.mouseDrag);
    refresh_orientation(mega->camera);
    mega->mouse = mouse;
    return (0);
}

int         user_cameraDragDir(t_mega *mega, int flg)
{
    struct s_mouse      mouse;

    if (!mega || !mega->camera)
        return (1);
    mouse = mega->mouse;
    rotate_camera_dir_drag(mega->camera, mouse.mouseDrag);
    refresh_orientation(mega->camera);
    mega->mouse = mouse;
    return (0);
}
