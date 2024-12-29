#include "camera.h"

/**
 ** reset_camera :
 ** Restore camera back to default configuration (position/orientation).
 ** Takes a camera pointer, BEWARE THE FLAG BUGGY.
 **
**/
void        reset_camera(t_cam *c, int flag)
{
    int             i;

    if (!c)
        return ;
    camera_aspect_ratio(c);
    c->o[0] = CAMERA_PRESET_ORIGIN_X;
    c->o[1] = CAMERA_PRESET_ORIGIN_Y;
    c->o[2] = CAMERA_PRESET_ORIGIN_Z;
    c->focal_distance = CAMERA_FOCAL_DISTANCE;

    ///reset_frustum(c);

    copy_v3(c->x, c->ux);
    copy_v3(c->y, c->uy);
    copy_v3(c->z, c->uz);

    c->pyr[0] = 0;
    c->pyr[1] = 0;
    c->pyr[2] = 0;
    mtp_v3_by(c->uz, c->focal_distance, c->ud);

    if (flag == CAMERA_KEEP_MODELSTACK)
        return ;
    if (flag == CAMERA_FREE_MODELSTACK)
    {
        i = -1;
        while (++i < MAX_MODEL)
            c->data->model[i].active = 0;
    }
    refresh_orientation(c);
}