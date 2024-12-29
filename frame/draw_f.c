#include "frame.h"

/**
 ** Obsolete.
 **
 ** Render made on GPU.
 **
**/


static void                 map_vertice(t_cam *c, int w, int h, double *v3, int *out2, double *out3)
{
    double       to[3];
    double       unit[3];

    sub_v3(v3, c->o, to);
    unit3(to, unit, NULL);
    ///if (!vector_to_pixel(c, unit, w, h, &out2[0], &out2[1], out3)) // OLD
    /**
    if (!vector_to_pixel(c, unit, w, h, out2[0], &out2[1])) // NEW
    {
        out2[0] = -1;
        out2[1] = -1;
    }**/
}

static struct s_triangle       make_triangle(double *v1, double *v2, double *v3)
{
    struct s_triangle       T;

    copy_v3(v1, T.v0);
    copy_v3(v2, T.v1);
    copy_v3(v3, T.v2);
    sub_v3(T.v1, T.v0, T.u);
    sub_v3(T.v2, T.v0, T.v);
    cross_prod3(T.u, T.v, T.n);
    unit3(T.n, T.n, NULL);
    return (T);
}

static void        draw_triangle_to_zbuffer(double *zbuffer, t_cam *camera, int w, int h, uchar *rgb, int *a, int *b, int *c, struct s_triangle triangle)
{
    int maxX = _max(a[0], _max(b[0], c[0]));
    int minX = _min(a[0], _min(b[0], c[0]));
    int maxY = _max(a[1], _max(b[1], c[1]));
    int minY = _min(a[1], _min(b[1], c[1]));
    double   vfa[2];
    double   vfb[2];
    double   vf_out[2];
    double     vs1[2];
    double     vs2[2];
    double     q[2];
    double   t;
    double   s;
    int     y;
    int     x;
    double       vector_length;
    struct s_ray    ray;
    double       point[3];
    uchar       ambia[4];
    uchar       diffu[4];
    uchar       specw[4];
    double       dot_light;
    double       dot_light_spec;
    double       pc[3];
    double       light[3];

    reverse_normal(&triangle, *((struct s_point *)(camera->o)));
    copy_v3(camera->o, ray.origine);
    /*** Triangle Center **/
    add_v3(triangle.v0, triangle.v1, point);
    add_v3(point, triangle.v2, point);
    mtp_v3_by(point, 1.f/3.f, point);
    sub_v3(camera->o, point, pc);
    unit3(pc, pc, NULL);
    if (fabs(dot_prod3(pc, triangle.n)) <= 0.00006) /// Avoid "square artefacts" bug
        return ;
    vector_length = length3(point);

    diffu[0] = rgb[0];
    diffu[1] = rgb[1];
    diffu[2] = rgb[2];
    ambia[0] = (uchar)((double)rgb[0] * 0.2);
    ambia[1] = (uchar)((double)rgb[1] * 0.2);
    ambia[2] = (uchar)((double)rgb[2] * 0.2);
    specw[0] = 255;
    specw[1] = 255;
    specw[2] = 255;

    add_v3(point, camera->o, light); // DIFFUSE LIGHT
    sub_v3(light, sun_position, light);
    unit3(light, light, NULL);
    dot_light = dot_prod3((double *)light, triangle.n); /// GOOD
    if (dot_light <= EPSILON)
        dot_light = 0; // Original
    rot_vec3(triangle.n, deg_to_rad(180), pc); // SPECULAR LIGHT
    dot_light_spec = dot_prod3(light, pc);
    if (dot_light_spec <= EPSILON)
        dot_light_spec = 0;
    else
        //dot_light_spec = pow(dot_light_spec, 3); /// TEST
        dot_light_spec = pow(dot_light_spec, 20); /// TEST
        //dot_light_spec = pow(dot_light_spec, 2); /// TEST
    mtp_color(diffu, dot_light);
    mtp_color(specw, dot_light_spec);
    add_color(ambia, diffu, ambia);
    add_color(ambia, specw, ambia);

    vs1[0] = b[0] - a[0];
    vs1[1] = b[1] - a[1];
    vs2[0] = c[0] - a[0];
    vs2[1] = c[1] - a[1];
    x = minX;
    while (x <= maxX && x < w && x > 0)
    {
      y = minY;
      while (y <= maxY && y < h && y > 0)
      {
        q[0] = (double)x - a[0];
        q[1] = (double)y - a[1];
        cross_prod2(q, vs2, vfa);
        cross_prod2(vs1, vs2, vfb);
        div_v2(vfa, vfb, vf_out);
        s = vf_out[0];
        cross_prod2(vs1, q, vfa);
        div_v2(vfa, vfb, vf_out);
        t = vf_out[1];
        if ( (s >= -0.000001) && (t >= -0.000001) && (s + t <= 1.000001) ) /// No gap between triangles ; Need to verify precise value
        {
            if (zbuffer[(((y * w) + x) * 4) + 3] > vector_length || zbuffer[(((y * w) + x) * 4) + 3] == DBL_MAX)
            {
                zbuffer[(((y * w) + x) * 4)] = (double)ambia[0];
                zbuffer[(((y * w) + x) * 4) + 1] = (double)ambia[1];
                zbuffer[(((y * w) + x) * 4) + 2] = (double)ambia[2];
                zbuffer[(((y * w) + x) * 4) + 3] = vector_length;
                ///zbuffer[(((y * w) + x) * 4) + 3] = 1;
            }
        }
        /*else /// TEST ///
        {
            zbuffer[(((y * w) + x) * 4)] = 255;
            zbuffer[(((y * w) + x) * 4) + 1] = 0;
            zbuffer[(((y * w) + x) * 4) + 2] = 0;
            zbuffer[(((y * w) + x) * 4) + 3] = FLT_MAX;
        } */ ///TEST ///
        y++;
      }
      x++; // Iteration in while condition
    }
    ///printf("debug : dege[%u], ret2[%u] disj[%u], away[%u]\n", tri_degenerate, tri_ret2, tri_disjoint, tri_goaway);
}

void     draw_f(t_cam *camera, double *zbuffer, int w, int h, uchar *rgb, t_model *model)
{
    int *fce;
    double *vrt;
    double *nrm;

    int             nf;
    int             i;
    int             j;
    int             flen;
    double           n[3];
    double           a[3];
    double           b[3];
    double           c[3];
    int             _a[2];//[3];
    int             _b[2];//[3];
    int             _c[2];//[3];
    double          a_[3];
    double          b_[3];
    double          c_[3];
    uchar           color[4];

    if (!model || !(vrt = model->v) || !(nrm = model->n) || !(fce = model->f) || (nf = model->nf) <= 0)
        return ;
    i = -1;
    color[3] = 255;
    while (++i < nf)
    {
        flen = fce[0];
        /*if (k_debug % nf != i)
        {
            fce += flen + 1;
            continue;
        }*/
        j = 2;
        get_v3(vrt, fce[1], a, model->_translate, model->_rotate, model->_scale);
        get_v3(nrm, i, n, NULL, NULL, NULL); //model->_translate, model->_rotate, model->_scale);
        unit3(n, n, NULL);
        ///int        vector_to_pixel(t_cam *c, double *input_vector, int w, int h, int *x, int *y, double *out3)
        ///vector_to_pixel(camera, a, w, h, &_a[0], &_a[1], a_); /// Test
        map_vertice(camera, w, h, a, _a, a_); /// BUG?
        sub_v3(a, camera->o, a); // Test
        while (j < flen)
        {
            get_v3(vrt, fce[j], b, model->_translate, model->_rotate, model->_scale);
            get_v3(vrt, fce[j + 1], c, model->_translate, model->_rotate, model->_scale);
            color[0] = rgb[0];
            color[1] = rgb[1];
            color[2] = rgb[2];
            ///vector_to_pixel(camera, b, w, h, &_b[0], &_b[1], b_); /// Test
            ///vector_to_pixel(camera, c, w, h, &_c[0], &_c[1], c_); /// Test
            map_vertice(camera, w, h, b, _b, b_); /// BUG?
            map_vertice(camera, w, h, c, _c, c_); /// BUG?
            sub_v3(b, camera->o, b); // Test
            sub_v3(c, camera->o, c); // Test

            draw_triangle_to_zbuffer(zbuffer, camera, w, h, color, _a, _b, _c, make_triangle(a, b, c)); /// GOOD
            /** get_v3(nrm, j, n, model->_translate, model->_rotate, model->_scale); /// TEST
            draw_triangle_to_zbuffer(zbuffer, camera, w, h, color, _a, _b, _c, make_triangle(a, b, c, n)); /// TEST /// MARCHE PAS */
            ///draw_triangle_to_zbuffer(zbuffer, camera, w, h, color, _a, _b, _c, make_triangle(a_, b_, c_)); /// TEST (Pas si mal, à tester mieux)
            j++;
        }
        fce += flen + 1;
    }
}
