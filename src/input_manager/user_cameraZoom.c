#include "input_manager.h"

int         user_cameraZoom(t_mega *mega, int flg)
{
    if (!mega || !mega->camera)
        return (1);
    if (flg)
    {
        mega->camera->focal_distance *= 1.1;
        if (mega->camera->focal_distance > CAMERA_MAX_FOCAL_DISTANCE)
            mega->camera->focal_distance = 3;

    }
    else
    {
        mega->camera->focal_distance *= 0.9;
        if (mega->camera->focal_distance <= EPSILON)
            mega->camera->focal_distance = 0.1;
    }
    return (0);
}
