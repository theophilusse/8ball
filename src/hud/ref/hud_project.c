#include "hud.h"

int                        hud_project(t_cam *c, t_hud *hud, int refProject)
{
    double      vertice[3];
    double      vec[3];
    int         coord[2];
    double focal_distance;
    double distance;

    if (!c || !hud || hud->active == 0)
        return (0);
    sub_v3(hud->org.vec, c->o, vertice);
    distance = length3(vertice);
    unit3(vertice, vertice, NULL);
    if (refProject > 0)
    {
        if (!vector_to_pixel(c, vertice, c->vw, c->vh, coord))
            return (0);
        hud->org.coord[0] = (double)coord[0];
        hud->org.coord[1] = (double)coord[1];
        if (refProject == 2)
            return (1);
    }
    mtp_v3_by(vertice, 5 * c->focal_distance, vertice);
    add_v3(vertice, c->o, vertice);

    add_v3(hud->axis.x, vertice, vec);
    sub_v3(vec, c->o, vec);
    unit3(vec, vec, NULL);
    if (!vector_to_pixel(c, vec, c->vw, c->vh, coord))
        return (0);
    hud->persp.x[0] = (double)coord[0];
    hud->persp.x[1] = (double)coord[1];

    add_v3(hud->axis.y, vertice, vec);
    sub_v3(vec, c->o, vec);
    unit3(vec, vec, NULL);
    if (!vector_to_pixel(c, vec, c->vw, c->vh, coord))
        return (0);
    hud->persp.y[0] = (double)coord[0];
    hud->persp.y[1] = (double)coord[1];

    add_v3(hud->axis.z, vertice, vec);
    sub_v3(vec, c->o, vec);
    unit3(vec, vec, NULL);
    if (!vector_to_pixel(c, vec, c->vw, c->vh, coord))
        return (0);
    hud->persp.z[0] = (double)coord[0];
    hud->persp.z[1] = (double)coord[1];
    return (1);
}
