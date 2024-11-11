#include "mouse.h"

int                 mouse_clickHUDAngle(t_hud *hud, int *clickCoord)
{
    t_hud_angle           *angle;
    double      pta[3];
    double      ptb[3];
    double      ptc[3];

    double distScreen;
    double distScreenMin = 30;
    double dist;
    double distMin = DBL_MAX;
    double *alignedVertice = NULL;

    int    coord[2];
    double coord_b[2];
    double coord_a[2];
    double tmp[2];

    double          vertice[3];

    if (!clickCoord || !hud)
        return (1);
    angle = (t_hud_angle *)hud->data.buf;
    hud->select_index = -1;

    tmp[0] = (double)clickCoord[0] - hud->org.coord[0];
    tmp[1] = (double)clickCoord[1] - hud->org.coord[0];
    dist = fabs(length2(tmp) - angle->ringRayLength);
    if (dist < 10) /// Select Ring case
    {
        hud->select_index = 3;
        copy_v3(vertice, hud->axis.w);
    }

    coord_a[0] = hud->persp.x[0];
    coord_a[1] = hud->persp.x[1];
    coord_b[0] = (double)clickCoord[0];
    coord_b[1] = (double)clickCoord[1];
    sub_v2(coord_a, coord_b, tmp);
    distScreen = length2(tmp);
    ///printf("DistScreen : [%f]\n", distScreen); ///
    if (distScreen < distScreenMin)
    {
        distScreenMin = distScreen;
        distMin = dist; /// Obsolete ?
        alignedVertice = hud->axis.x;
        hud->select_index = 0;
    }

    coord_a[0] = hud->persp.y[0];
    coord_a[1] = hud->persp.y[1];
    coord_b[0] = (double)clickCoord[0];
    coord_b[1] = (double)clickCoord[1];
    sub_v2(coord_a, coord_b, tmp);
    distScreen = length2(tmp);
    ///printf("DistScreen : [%f]\n", distScreen); ///
    if (distScreen < distScreenMin)
    {
        distScreenMin = distScreen;
        distMin = dist; /// Obsolete ?
        alignedVertice = hud->axis.y;
        hud->select_index = 1;
    }

    coord_a[0] = hud->persp.z[0];
    coord_a[1] = hud->persp.z[1];
    coord_b[0] = (double)clickCoord[0];
    coord_b[1] = (double)clickCoord[1];
    sub_v2(coord_a, coord_b, tmp);
    distScreen = length2(tmp);
    ///printf("DistScreen : [%f]\n", distScreen); ///
    if (distScreen < distScreenMin)
    {
        distScreenMin = distScreen;
        distMin = dist; /// Obsolete ?
        alignedVertice = hud->axis.z;
        hud->select_index = 2;
    }

    /*switch (angle->select_index)
    {
        case 0: {
            copy_v3(tool->hud.axis.z, angle->axis);
            angle->oppositeAxis[0] = tool->hud.persp.y[0];
            angle->oppositeAxis[1] = tool->hud.persp.y[1];
                    break; };
        case 1: {
            copy_v3(tool->hud.axis.x, angle->axis);
            angle->oppositeAxis[0] = tool->hud.persp.z[0];
            angle->oppositeAxis[1] = tool->hud.persp.z[1];
                    break; };
        case 2: {
            copy_v3(tool->hud.axis.x, angle->axis);
            angle->oppositeAxis[0] = tool->hud.persp.x[0];
            angle->oppositeAxis[1] = tool->hud.persp.x[1];
                    break; };
    }*/
    if (hud->select_index == -1)
        return (1);
    return (0);
}
