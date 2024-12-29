#include "camera.h"

/**
 ** camera_aspect_ratio :
 ** Adjust the camera's aspect ratio from the screen resolution.
 **
**/
void            camera_aspect_ratio(t_cam *c)
{
    c->w = (c->vw > c->vh ? (double)c->vw / (double)c->vh : 1) * CAMERA_DIMENSION_FACTOR;
    c->h = (c->vw > c->vh ? 1 : (double)c->vh / (double)c->vw) * CAMERA_DIMENSION_FACTOR;
}