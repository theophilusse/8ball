#include "mouse.h"

/***
static struct s_vertice_dist select_near_vertice(t_model *model, t_cam *c, int w, int h, int *screenPos, SDL_Surface *s)
{
    struct s_vertice_dist ret;
    double distScreen;
    double distScreenMin = 30;
    double dist;
    double distMin = DBL_MAX;
    double *alignedVertice = NULL;

    int    coord[2];
    double coord_b[2];
    double coord_a[2];
    double tmp[2];

    int             nv;
    double          *vrt;
    double          vertice[3];
    int             i;

    uint            adr;
    double          *zbuffer;

    ret.dist2d = 0;
    ret.dist3d = 0;
    ret.cache[0] = 0;
    ret.cache[1] = 0;
    ret.cache[2] = 0;
    ret.vertice = NULL;
    if (!model || !(vrt = model->v) || (nv = (model->nv / (int)(vrt[1]))) <= 0)
        return (ret);
    if (!(zbuffer = c->data->zbuffer))
        return (ret);
    i = 0;
    while (++i < nv)
    {
        copy_v3(&vrt[i * 3], vertice);
        copy_v3(vertice, ret.base);
        ///copy_v3(ret.base, ret.cache);
        sub_v3(vertice, c->o, vertice);
        dist = length3(vertice);
        unit3(vertice, vertice, &dist);
        if (vector_to_pixel(c, vertice, w, h, coord) && coord[0] != -1 && coord[1] != -1) // Test
        {
            adr = (((coord[1] * w) + coord[0]) * 4) + 3;
            if ( zbuffer[adr] < dist - DBL_EPSILON ) /// TEST
                continue;
            coord_a[0] = (double)coord[0];
            coord_a[1] = (double)coord[1];
            coord_b[0] = (double)screenPos[0];
            coord_b[1] = (double)screenPos[1];
            sub_v2(coord_a, coord_b, tmp);
            distScreen = length2(tmp);
            if (distScreen < distScreenMin)
            {
                distScreenMin = distScreen;
                distMin = dist;
                ret.coord[0] = coord[0];
                ret.coord[1] = coord[1];
                alignedVertice = &vrt[i * 3];
            }
        }
    }
    ret.dist2d = distScreenMin;
    ret.dist3d = distMin;
    ret.vertice = alignedVertice;
    return (ret);
} ***/

static struct s_select_vertice select_near_vertice(t_model *model, t_cam *c, int *screenPos, double *distMin)
{
    struct s_select_vertice ret;
    double dist2d;
    double coord_b[2];
    double coord_a[2];
    double tmp[2];

    int             nv;
    double          *vrt;
    //double          vertice[3];
    int             i;

    //uint            adr;
    //double          *zbuffer;
    t_proj          *proj;

    ret.ptr = NULL;
    if (!model || !c || !screenPos || !distMin ||
        ///!(vrt = model->v) || (nv = (model->nv / (int)(vrt[1]))) <= 0) /// Original
        !(vrt = model->v) || (nv = (int)vrt[0] + 1) <= 0) // Test
    {
        return (ret);
    }
    coord_b[0] = (double)screenPos[0];
    coord_b[1] = (double)screenPos[1];
    i = -1;
    while (++i < nv)
    {
        if (!model->proj[i].ptr)
            continue;
        proj = &model->proj[i];
        coord_a[0] = (double)proj->coord[0];
        coord_a[1] = (double)proj->coord[1];
        /**
            adr = ((((int)coord_a[1] * viewport->w) + (int)coord_a[0]) * 4) + 3;
            if (zbuffer[adr] < dist3d - DBL_EPSILON ) /// TEST
                continue;
        **/
        sub_v2(coord_a, coord_b, tmp);
        dist2d = length2(tmp);
        if (dist2d < distMin[0])
        {
            distMin[0] = dist2d;
            distMin[1] = proj->dist;
            /** y = i; **/
            ret.coord[0] = coord_a[0];
            ret.coord[1] = coord_a[1];
            ret.ptr = proj->ptr;
        }
    }
    /** printf("Select vertices %d\n", y); **/
    return (ret);
}

///struct s_vertice_dist select_vertice_click(t_cam *c, t_tool *tool, int *coord, int *error, SDL_Surface *s)
//struct s_select_vertice mouse_clickSelect(t_cam *c, t_tool *tool, int *coord, int *error, SDL_Surface *viewport)
int             mouse_clickSelect(t_cam *c, t_tool *tool, int *coord, SDL_Surface *viewport, t_select_vertice *vsel)
{
    t_camdata           *data;
    int                   i;
    double                dist[2];
    double                distMin[2];
    struct s_select_vertice vertice;

    if (!c || !tool || !coord || !viewport || !vsel || !(data = c->data))
        return (0);
    vsel->ptr = NULL;
    dist[0] = DBL_MAX;
    distMin[0] = 25;
    distMin[1] = DBL_MAX;
    i = -1;
    while (++i < MAX_MODEL)
    {
        if (data->model[i].active)
        {
            vertice = select_near_vertice(&data->model[i], c, coord, dist);
            if (vertice.ptr && dist[0] < distMin[0] && dist[1] < distMin[1])
            {
                distMin[0] = dist[0];
                distMin[1] = dist[1];
                vertice.model = i;
                *vsel = vertice;
                tool->hud.active = 1;
                /*** arrow->vertice = vertice.vertice; ***/
            }
        }
        else
            break;
    }
    if (vsel->ptr)
        return (1); /// Click Ok.
    return (0);     /// Click Fail.
}
