#include "frame.h"

void            vertices_highlight(SDL_Surface *viewport, t_cam *camera /*, int *currentObject*/) /// Need to be modified
{
    t_camdata       *data;
    struct s_model model;
    int             i;
    int             j;
    //uint            adr;
    //double          vertice[3];
    double          *vrt;
    int             nv;
    double maxDist;
    double tmpDist;
    double      acDist;
    int         squareSize[2];
    t_proj          *proj;
    double          f;
    double          c_val;
    uchar           color[4];
    int             k;

    if (!camera || !viewport || !(data = camera->data))
        return ;
    i = -1;
    maxDist = camera->data->verticesDist[1];
    tmpDist = 0.8 / (maxDist - camera->data->verticesDist[0]);
    while (++i < MAX_MODEL)
    {
        if (data->model[i].active /*&& (!currentObject || i == *currentObject)*/)
        {
            model = data->model[i];
            if ((vrt = model.v) &&
                (nv = (model.nv / (int)(vrt[1]))) >= 0 &&
                (proj = model.proj))
            {
                j = 0;
                while (++j < nv)
                {
                    if (proj->ptr)
                    {
                        acDist = maxDist - proj->dist;
                        f = acDist * tmpDist;
                        squareSize[0] = (int)(f * 6);
                        squareSize[1] = squareSize[0] / 2;
                        squareSize[0] += 1;
                        if (f <= 0.2)
                            f = 0.2;
                        k = -1;
                        while (++k < 3)
                            if ((c_val = (double)_blue_crystal[k] * f) < 255 - DBL_EPSILON)
                                color[k] = (uchar)c_val;
                            else
                                color[k] = 255;
                        color[3] = (uchar)255;
                        square(viewport, proj->coord[0] - squareSize[1], proj->coord[1] - squareSize[1],
                               squareSize[0], squareSize[0], (uchar *)color);
                        //**//
                        //printf("f===========================[%f]\n", f); /// Marker
                        //printf("color[%u|%u|%u]\n", color[0], color[1], color[2]); /// Marker
                        ///square(viewport, proj->coord[0] - 2, proj->coord[1] - 2, 5, 5, (uchar *)_blue_crystal); (low config)
                    }
                    proj++;
                }
            }
        }
    }
}
