#include "frame.h"

static int             coordInside(int w, int h, int *coord)
{
    if (coord[0] >= 0 && coord[1] >= 0)
        if (coord[0] < w && coord[1] < h)
            return (1);
    return (0);
}

void                vertices_project(SDL_Surface *viewport, t_cam *camera, uint occlusion) /// Need to be modified
{
    t_camdata       *data;
    struct s_model  model;
    int             i;
    int             j;
    uint            vecsize;
    uint            adr;
    double          vertice[3];
    double          *vrt;
    int             nv;
    int             coord[2];
    double          length;
    double          minDist;
    double          maxDist;
    int             w;
    int             h;
    t_proj          *proj;

    minDist = 0;
    minDist = DBL_MAX;
    if (!camera || !viewport || !(data = camera->data))
        return ;
    w = viewport->w;
    h = viewport->h;
    i = -1;
    while (++i < MAX_MODEL)
    {
        if (data->model[i].active)
        {
            model = data->model[i];
            if ((vrt = model.v) &&
                (nv = (model.nv / (int)(vrt[1]))) >= 0 &&
                (proj = model.proj))
            {
                vecsize = vrt[1];
                j = 0;
                while (++j < nv)
                {
                    adr = j * vecsize;
                    copy_v3(&vrt[adr], vertice);
                    sub_v3(vertice, camera->o, vertice);
                    //length = length2(vertice); /// TEST
                    length = length3(vertice); /// TEST
                    unit3(vertice, vertice, NULL);

                    proj->ptr = NULL;
                    if (vector_to_pixel(camera, vertice, w, h, coord) && coordInside(w, h, coord))
                        if (!occlusion || (data->zbuffer[(((coord[1] * w) + coord[0]) * 4) + 3] >= length - 0.000001)) /// TEST
                        {
                            if (minDist == 0 || length < minDist)
                                minDist = length;
                            if (maxDist == DBL_MAX || length > maxDist)
                                maxDist = length;
                            proj->dist = length;
                            proj->coord[0] = (int)coord[0];
                            proj->coord[1] = (int)coord[1];
                            proj->ptr = &vrt[adr];
                        }
                    proj++;
                }
            }
        }
        else
            break;
    }
    camera->data->verticesDist[0] = minDist;
    camera->data->verticesDist[1] = maxDist;
}
