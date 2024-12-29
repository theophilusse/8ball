#include "camera.h"

/**
 ** n_vrt :
 ** Takes a (double *) vertice stack and return the number of vertices in it.
 **
**/
static int          n_vrt(double *v)
{
    return ((int)((v[0] * v[1]) + v[1]));
}

/**
 ** n_face :
 ** Takes a (int *) face stack and return the number of faces in it.
 **
**/
static int          n_face(int *fce)
{
    int         i;
    int         k;
    int         ac;

    ac = 0;
    i = 0;
    k = 0;
    while (fce[i] != 0)
    {
        ac += fce[i];
        i += fce[i] + 1;
        k++;
    }
    ///return (ac);
    return (k);
}

/**
 ** push_model :
 ** Push a 3d geometry model (vrt)(nv)(fce) inside the camera (data) memory.
 ** Object have a color set by uchar *amb_color
 ** And a position set by (model_translate) (model_rotate) (model_scale)
 **
**/
int      push_model(t_camdata *d, uchar *amb_color,
                           double *vrt, double *nv, int *fce,
                           double *model_translate, double *model_rotate, double *model_scale/*, const char *name*/)
{
    int         i;
    int         n_vertices;
    double      *vptr;

    int         mdl;
    t_model     *m;
    double       _translate[3];
    double       _rotate[3];
    double       _scale[3];

    if (!d || !vrt || !nv || !fce)
        return (1);
    mdl = 0;
    while (d->model[mdl].active == 1)
        if (++mdl >= MAX_MODEL)
            return (1);
    m = &d->model[mdl];
    m->active = 1;
    m->id = mdl;

    if (model_translate)
        copy_v3(model_translate, m->_translate);
    else
    {
        _translate[0] = 0;
        _translate[1] = 0;
        _translate[2] = 0;
        copy_v3(_translate, m->_translate);
    }
    if (model_rotate)
        copy_v3(model_rotate, m->_rotate);
    else
    {
        _rotate[0] = 0;
        _rotate[1] = 0;
        _rotate[2] = 0;
        copy_v3(_rotate, m->_rotate);
    }
    if (model_scale)
        copy_v3(model_scale, m->_scale);
    else
    {
        _scale[0] = 1.0;
        _scale[1] = 1.0;
        _scale[2] = 1.0;
        copy_v3(_scale, m->_scale);
    }

    m->nv = n_vrt(vrt);
    if (!(m->proj = (t_proj *)ALLOC(sizeof(struct s_proj) * m->nv)))
        return (1);
    m->v = vrt;
    m->nn = n_vrt(nv);
    m->n = nv;
    m->nf = n_face(fce);
    printf("+ Pushing [%u] faces\n", m->nf);
    m->f = fce;
    if (amb_color)
    {
        m->_ambiant_color[0] = amb_color[0];
        m->_ambiant_color[1] = amb_color[1];
        m->_ambiant_color[2] = amb_color[2];
        m->_ambiant_color[3] = amb_color[3];
    }
    else
    {
        *m->_ambiant_color = *_original_gray;
        /*m->_ambiant_color[1] = 255;
        m->_ambiant_color[2] = 200;
        m->_ambiant_color[3] = 255;*/
    }

    /*** TEST WORKING ! ***/
    uint             vecsize;
    double           x_axis[3];
    double           y_axis[3];
    double           z_axis[3];

    x_axis[0] = 1;
    x_axis[1] = 0;
    x_axis[2] = 0;
    y_axis[0] = 0;
    y_axis[1] = 1;
    y_axis[2] = 0;
    z_axis[0] = 0;
    z_axis[1] = 0;
    z_axis[2] = 1;
    n_vertices = m->v[0] + 1;
    vecsize = (uint)m->v[1];
    printf("Model vector size : [%u]\n", vecsize);///
    vptr = m->v;
    i = 0;
    if (model_scale)
        while (++i < n_vertices)
        {
            vptr += vecsize;
            vptr[0] *= model_scale[0];
            vptr[1] *= model_scale[1];
            vptr[2] *= model_scale[2];
        }
    vptr = m->v;
    i = 0;
    if (model_rotate)
        while (++i < n_vertices)
        {
            vptr += vecsize;
            if (m->_rotate[0] != 0)
                rot_vec3(x_axis, deg_to_rad(m->_rotate[0]), vptr);
            if (m->_rotate[1] != 0)
                rot_vec3(y_axis, deg_to_rad(m->_rotate[1]), vptr);
            if (m->_rotate[2] != 0)
                rot_vec3(z_axis, deg_to_rad(m->_rotate[2]), vptr);
        }
    vptr = m->v;
    i = 0;
    if (model_translate)
        while (++i < n_vertices)
        {
            vptr += vecsize;
            vptr[0] += model_translate[0];
            vptr[1] += model_translate[1];
            vptr[2] += model_translate[2];
        }
    read_helloworld(m, d);
    return (0);
}
