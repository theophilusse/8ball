#include "camera.h"

/**
 ** new_camera :
 ** Init a fresh allocated camera.
 ** Takes a screen surface and a color mask.
 ** Return NULL if failed.
 **
**/
t_cam           *new_camera(SDL_Surface *screen, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
{
    int             i;
    int             j;
    t_cam           *c;
    t_camdata       *d;

    DEBUG ///
    if (!(c = (t_cam *)ALLOC(sizeof(struct s_cam))))
        return (NULL);
    c->data = NULL;
    /** Presets **/
    c->vw = screen->w;
    c->vh = screen->h;
    camera_aspect_ratio(c);
    c->hw = c->w / 2;
    c->hh = c->h / 2;
    c->unit_w = c->w / screen->w;
    c->unit_h = c->h / screen->h;
    c->o[0] = CAMERA_PRESET_ORIGIN_X;
    c->o[1] = CAMERA_PRESET_ORIGIN_Y;
    c->o[2] = CAMERA_PRESET_ORIGIN_Z;
    c->focal_distance = CAMERA_FOCAL_DISTANCE;

    /** Build Frustum **/
    ///reset_frustum(c);

    /** Constant Axis **/
    c->x[0] = 1.0;
    c->x[1] = 0.0;
    c->x[2] = 0.0;
    c->y[0] = 0.0;
    c->y[1] = 1.0;
    c->y[2] = 0.0;
    c->z[0] = 0.0;
    c->z[1] = 0.0;
    c->z[2] = 1.0;

    /** Relative Axis **/
    copy_v3(c->x, c->ux);
    copy_v3(c->y, c->uy);
    copy_v3(c->z, c->uz);

    /** YXZ Rotation **/
    c->pyr[0] = 0;
    c->pyr[1] = 0;
    c->pyr[2] = 0;

    mtp_v3_by(c->uz, c->focal_distance, c->ud);

    if (!(d = (t_camdata *)ALLOC(sizeof(struct s_camdata))))
    {
        if (c)
            FREE(c);
        return (NULL);
    }
    d->backbuffer = NULL;
    i = -1;
    while (++i < MAX_MODEL)
        d->model[i].active = 0;
    j = (screen->h * screen->w) * 4;
    ///cl->zbuffer_bufsz = (c->vw * c->vh) * (sizeof(double) * 4);
    if (!(d->zbuffer = (double *)ALLOC(sizeof(double) * j)))
    {
        if (c)
            FREE(c);
        if (d)
            FREE(d);
        return (NULL);
    }
    i = -1;
    while (++i < j)
        d->zbuffer[i] = DBL_MAX;
    refresh_orientation(c);
    /** d->backbuffer = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, screen->w, screen->h, 32, rmask, gmask, bmask, amask); **/
    d->backbuffer = new_surface32(screen->w, screen->h); ///
    /**
        d->selectDist[0] = 0;
        d->selectDist[1] = DBL_MAX;
    **/
    d->verticesDist[0] = 0;
    d->verticesDist[1] = DBL_MAX;
    c->data = d;
    return (c);
}
