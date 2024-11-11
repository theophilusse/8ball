#include "frame.h"

void            highlight_selection(SDL_Surface *viewport, t_cam *camera, int w, int h, t_select_node *selectStack, uint occlusion)
{
    char            skip;
    int             k;
    int             coord[2];
    double          *zbuffer;
    double          vertice[4];
    double          *ptr;

    double          dist;
    double          f;
    double          c_val;
    double          maxDist;
    double          acDist;
    double          tmpDist;
    int             circleSize;
    uchar           color[4];

    if (!viewport || !camera || w < 0 || h < 0)
        return ;
    if (occlusion)
        if (!(zbuffer = camera->data->zbuffer))
            return ;
    /**
        maxDist = camera->data->selectDist[1];
        tmpDist = 1 / (maxDist - camera->data->selectDist[0]);
    **/
    maxDist = camera->data->verticesDist[1];
    tmpDist = 1 / (maxDist - camera->data->verticesDist[0]);
    color[3] = (uchar)255;
    while (selectStack)
    {
        if ((ptr = selectStack->vrt.ptr))
        {
            copy_v3(ptr, vertice);
            sub_v3(vertice, camera->o, vertice);
            dist = length3(vertice);
            unit3(vertice, vertice, NULL);
            if (vector_to_pixel(camera, vertice, w, h, coord))
            {
                if (occlusion && zbuffer[(((coord[1] * w) + coord[0]) * 4) + 3] < dist - 0.000001)
                    skip = 1;
                else
                    skip = 0;
                if (!skip)
                {
                    if (dist == 0)
                        f = 1;
                    else
                    {
                        acDist = maxDist - dist;
                        f = acDist * tmpDist;
                        if (f <= 0.2)
                            f = 0.2;
                    }
                    circleSize = (int)(f * 8);
                    k = -1;
                    while (++k < 3)
                        if ((c_val = (double)_deep_violet[k] * f) < 255 - DBL_EPSILON)
                            color[k] = (uchar)c_val;
                        else
                            color[k] = 255;
                    plain_circle(viewport, (uchar *)color, coord, circleSize);
                }
            }
        }
        selectStack = selectStack->next;
    }
}
