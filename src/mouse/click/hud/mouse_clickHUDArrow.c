#include "mouse.h"

int             mouse_clickHUDArrow(t_hud *hud, int *clickCoord)
{
    //t_hud_arrow           *arrow;
    double      pta[3];
    double      ptb[3];
    double      ptc[3];

    double distScreen;
    double distScreenMax = 30;
    double dist;

    double    coord[2];
    double    tmp[2];

    double          vertice[3];

    if (!clickCoord || !hud)// || !arrow->vertice)
        return (1);
    //arrow = (t_hud_arrow *)hud->data.buf;
    hud->select_index = -1;
    coord[0] = (double)clickCoord[0];
    coord[1] = (double)clickCoord[1];
    /**
    printf("Select at [%d][%d]\n", clickCoord[0], clickCoord[1]); ///
    printf("Persp X at [%f][%f]\n", hud->persp.x[0], hud->persp.x[1]); ///
    printf("Persp Y at [%f][%f]\n", hud->persp.y[0], hud->persp.y[1]); ///
    printf("Persp Z at [%f][%f]\n", hud->persp.z[0], hud->persp.z[1]); ///
    **/
    sub_v2(hud->persp.x, coord, tmp);
    ///printf("X vec [%f][%f]\n", tmp[0], tmp[1]); ///
    distScreen = length2(tmp);
    ///printf("X : [%f]\n", distScreen); ///
    if (distScreen < distScreenMax)
    {
        distScreenMax = distScreen;
        hud->select_index = 0;
    }

    sub_v2(hud->persp.y, coord, tmp);
    distScreen = length2(tmp);
    ///printf("Y : [%f]\n", distScreen); ///
    if (distScreen < distScreenMax)
    {
        distScreenMax = distScreen;
        hud->select_index = 1;
    }

    sub_v2(hud->persp.z, coord, tmp);
    distScreen = length2(tmp);
    ///printf("Z : [%f]\n", distScreen); ///
    if (distScreen < distScreenMax)
    {
        hud->select_index = 2;
    }
    if (hud->select_index == -1)
        return (1);
    return (0);
}

/*struct s_vertice_dist OLDhud_arrow_click(t_cam *c, t_hud_arrow *arrow, int *coord, int *error, SDL_Surface *s)
{
    t_camdata       *data;
    struct s_vertice_dist vselect;

    if (error)
        *error = 0;
    vselect.dist2d = 0;
    vselect.dist3d = DBL_MAX;
    vselect.vertice = NULL;
    data = c->data;
    if (arrow && arrow->active == 1)
    {
        vselect = select_hud_arrow(arrow, c, data->backbuffer->w, data->backbuffer->h, coord, s);
        arrow->active = 2;
        if (vselect.vertice == NULL)
            arrow->active = 0;
    }
    return (vselect);
}*/
