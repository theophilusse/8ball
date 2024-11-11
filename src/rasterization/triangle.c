#include "8ball.h"

void     swap_pointers(void **pa, void **pb)
{
    void        *swp;

    if (!pa || !pb)
        return ;
    if (!(swp = *pa))
        return ;
    *pa = *pb;
    *pb = swp;
}

void         swap_values(double *a, double *b)
{
    double       c;

    c = *b;
    *b = *a;
    *a = c;
}

/// Assume that classes are already given for the objects:
///    Point and Vector with
///        coordinates {double x, y, z;}
///        operators for:
///            == to test  equality
///            != to test  inequality
///            (Vector)0 =  (0,0,0)         (null vector)
///            Point   = Point ± Vector
///            Vector =  Point - Point
///            Vector =  Scalar * Vector    (scalar product)
///            Vector =  Vector * Vector    (cross product)
///    Line and Ray and Segment with defining  points {Point P0, P1;}
///        (a Line is infinite, Rays and  Segments start at P0)
///        (a Ray extends beyond P1, but a  Segment ends at P1)
///    Plane with a point and a normal {Point V0; Vector  n;}
///    Triangle with defining vertices {Point V0, V1, V2;}
///    Polyline and Polygon with n vertices {int n;  Point *V;}
///        (a Polygon has V[n]=V[0])
///===================================================================

// intersect3D_RayTriangle(): find the 3D intersection of a ray with a triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 =  disjoint (no intersect)
//             1 =  intersect in unique point I1
//             2 =  are in the same plane
///printf("debug : dege[%u], ret2[%u] disj[%u], away[%u]\n", tri_degenerate, tri_ret2, tri_disjoint, tri_goaway);
///int BETTERrayTriangleIntersect(double *orig, double *dir, double *v0, double *v1, double *v2, double *t, double *u, double *v)
int intersect3D_RayTriangle( struct s_ray R, struct s_triangle T, double* I , double *Dist ) //
{
    double     dir[3];             // ray vectors
    double     w0[3];              // ray vectors
    double     w1[3];              // ray vectors
    double     w[3];               // ray vectors
    double     r, a, b;              // params to calc ray-plane intersect

    if (T.n[0] == 0 && T.n[1] == 0 && T.n[2] == 0)             // triangle is degenerate
    {
        return (-1);                  // do not deal with this case
    }

    double           tmp[3];
    ///dir = R.P1 - R.P0;              // ray direction vector
    //sub_v3(R.direction, R.origine, dir);              // ray direction vector
    copy_v3(R.direction, dir);              // ray direction vector

    //add_v3(dir, R.direction, dir); /// TEST WITH SEGMENT

    ///reverse_vec( *((t_point *)T.n), (t_point *)T.n); // TEST
    sub_v3(R.origine, T.v0, w0); // Original
    sub_v3(T.v0, R.origine, w1); // Original TEST

    cross_prod3(T.u, T.v, T.n); // Original TEST

    double to[3];
    double rt[3];
    double denom = dot_prod3(T.n, R.direction);
    ///if (fabs(denom) > 0.0001f) // your favorite epsilon  // Original
    if (fabs(denom) > EPSILON) // your favorite epsilon
    ///if (denom > EPSILON) // TEST
    {
        sub_v3(T.v0/*center*/, R.origine, to); //
        ///*Dist = dot_prod3(tmp, T.n) / denom;
        //r = dot_prod3(w0, T.n) / denom; // Test
        r = dot_prod3(to, T.n) / denom; // Original
        ///if (r >= 0.0001f) // Original
        ///if (r >= EPSILON) // Original
        if (r >= EPSILON) // DEBUG TEST
        {
            mtp_v3_by(dir, r, rt);//
            add_v3(rt, R.origine, I);
            *Dist = r;
            /*if (fabs(r) >= 150)/// DEBUG
            {
                printf("a[%f] b[%f] r[%f]\n", a, b, r);
            }*/// DEBUG
            return (1); // you might want to allow an epsilon here too
        }
    }
    //return (0); // Test

    a = -dot_prod3(T.n, w0); // Original
    b = dot_prod3(T.n, dir); // Original
    if (fabs(b) < EPSILON + 0.01) {     // ray is  parallel to triangle plane // Test
        if (a == 0)                 // ray lies in triangle plane
        //if (a >= 0)                 // ray lies in triangle plane
        {
            return (2);
        }
        return (0);              // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b; // Original
    if (r <= 1)                    // ray goes away from triangle
    {
        return (0);                   // => no intersect
    }
    // for a segment, also test if (r > 1.0) => no intersect
    ///*I = R.P0 + r * dir;            // intersect point of ray and plane
    /** Test **/
    /// *Dist = length3(tmp); // Original
    *Dist = sqrt(length3(tmp)); // Log Zbuffer
    return (1);
    /** Test **/

    double       Tu[3];
    double       Tv[3];
    //double       Tn[3];
    // is I inside T?
    double    uu, uv, vv, wu, wv, D;
    /** Test **/
    unit3(T.u, Tu, NULL);
    unit3(T.v, Tv, NULL);
    /** Test **/
    uu = dot_prod3(T.u,T.u);
    uv = dot_prod3(T.u,T.v);
    vv = dot_prod3(T.v,T.v);
    sub_v3(T.v0, I, w);
    wu = dot_prod3(w,T.u);
    wv = dot_prod3(w,T.v);
    D = (uv * uv) - uu * vv;

    // get and test parametric coords
    double s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0 || s > 1)         // I is outside T
        return (0);
    t = (uv * wu - uu * wv) / D;
    if (t < 0 || (s + t) > 1)  // I is outside T
        return (0);
    mtp_v3_by(T.u, s, Tu);
    mtp_v3_by(T.v, t, Tv);
    add_v3(Tu, Tv, tmp);
    add_v3(T.v0, tmp, tmp);

    sub_v3(tmp, R.origine, tmp); // Original
    *Dist = length3(tmp);
    return (1);                       // I is in T
}

int        pixel_to_vector(t_cam *c, int w, int h, int x, int y, t_ray *ray) /// Good? (Buggy)
{
    double           relative[3];

    /** Relative to camera vector **/
    relative[0] = ((double)x * c->unit_w) - (c->w / 2); // Pixel coord. to real coord. (zero = 50/50 on screen)
    relative[1] = ((double)y * c->unit_h) - (c->h / 2); // Pixel coord. to real coord.
    relative[2] = c->focal_distance; // Pixel coord. to real coord.

    /** Absolute vector **/
    unit3(relative, relative, NULL); /// Test
    //translate_angle_xyz(relative, c->x, c->y, c->z, c->pyr, ray->origine); // Relative to absolute vector
    translate_angle_relabs(relative, c->x, c->y, c->z, c->pyr, ray->direction); // Relative to absolute vector
    unit3(ray->origine, ray->direction, NULL); /// TEST
    ///unit3(ray->direction, ray->direction, NULL); /// Original
    ///return (1); // Next : Should return struct s_point

    /** //TEST
    double           u[3];
    double           v[3];

    sub_v3(c->fb, c->fa, u);
    sub_v3(c->fc, c->fa, v);
    div_v3_by(u, c->w, u);
    div_v3_by(v, c->h, v);
    mtp_v3_by(u, (double)x, u);
    mtp_v3_by(v, (double)y, v);
    add_v3(u, v, relative);
    ///sub_v3(relative, c->o, relative);
    unit3(relative, relative, NULL);
    //copy_v3(c->o, ray->origine);
    copy_v3(relative, ray->direction);
    //TEST **/

    /** TEST **/
    double          a[2] = { ((60 / (double)w) * (double)x) , ((45 / (double)h) * (double)y) };
    double          v[3];

    copy_v3(c->uz, v);
    rot_vec3(c->uy, deg_to_rad(a[0]) - deg_to_rad((60 / w) * 0.5), v);
    rot_vec3(c->ux, deg_to_rad(a[1]) - deg_to_rad((45 / h) * 0.5), v);
    unit3(v, ray->direction, NULL);
    copy_v3(c->o, ray->origine);
    /** TEST **/
    return (1);
}

int        vector_to_pixel(t_cam *c, double *input_vector, uint dimW, uint dimH, int *screen_pixel) /// GOOD
{
    double   		 fdim[2];
    double           vec3[3];
    double           a[2];
    double           b[2];
    double           p[2];
    double           dot;
    double          dot_side[2];
    double          angle[3];
    double			 pixel[2];

    /* Pre-requis */
    if (dot_prod3(input_vector, c->ud) < DBL_EPSILON) /** Behind Camera **/
        return (0);
    translate_angle_absrel(input_vector, c, vec3);
    /* Axe X */
    a[0] = vec3[0];
    a[1] = vec3[2];
    unit2(a, a, NULL);
    b[0] = 0;
    b[1] = 1;
    p[0] = 1;
    p[1] = 0;
    dot = dot_prod2(b, a);
    dot_side[0] = dot_prod2(p, a);

    angle[0] = acos(dot);
    /*angle.y = M_PI_2;
    angle.z = M_PI - angle.x - angle.y;*/
    angle[1] = PI_2;
    angle[2] = PI - angle[0] - angle[1];

    fdim[0] = c->w;
    fdim[1] = c->h;

    pixel[0] = (c->focal_distance/sin(angle[2])) * sin(angle[0]);
    if (dot_side[0] >= DBL_EPSILON)
        pixel[0] += fdim[0] / 2;
    else
        pixel[0] = (fdim[0] / 2) - pixel[0];

    /* Axe Y */
    a[0] = vec3[2];
    a[1] = vec3[1];
    unit2(a, a, NULL);
    b[0] = 1;
    b[1] = 0;
    p[0] = 0;
    p[1] = 1;
    dot = dot_prod2(b, a);

    dot_side[1] = dot_prod2(p, a);

    angle[0] = acos(dot);
    angle[1] = M_PI_2;
    angle[2] = M_PI - angle[0] - angle[1];

    pixel[1] = (c->focal_distance/sin(angle[2])) * sin(angle[0]);
    if (dot_side[1] >= DBL_EPSILON)
        pixel[1] += fdim[1] / 2;
    else
        pixel[1] = (fdim[1] / 2) - pixel[1];

    if (pixel[0] >= fdim[0] * 2 || pixel[1] >= fdim[1] * 2 || pixel[0] < -fdim[0] || pixel[1] < -fdim[1]) /// Test
        return (0);

    double       width_unit = (fdim[0] / dimW);
    double       height_unit = (fdim[1] / dimH);
    screen_pixel[0] = (int)(pixel[0] / width_unit);
    screen_pixel[1] = dimH - (int)(pixel[1] / height_unit);
    if (screen_pixel[0] < 0 || screen_pixel[0] >= dimW || screen_pixel[1] < 0 || screen_pixel[1] >= dimH)
        return (0);
    return (1);
}

int        OLDvector_to_pixel(t_cam *c, double *input_vector, int w, int h, int *x, int *y, double *out3) /// " Working "
{
    double           vec3[3];
    double           a[2];
    double           b[2];
    double           p[2];
    double           dot;
    double           dot_side[2];
    double           angle_a;
    double           angle_b;
    double           angle_c;
    double           x_;
    double           y_;

    /* Pre-requis */
    unit3(input_vector, vec3, NULL);
    if (dot_prod3(input_vector, c->ud) < EPSILON) // Behind Camera
        return (0);
    translate_angle_absrel(input_vector, c, vec3);
    if (out3)
        copy_v3(vec3, out3); ///

    /* Axe X */
    a[0] = vec3[0];
    a[1] = vec3[2];
    unit2(a, a, NULL);
    b[0] = 0;
    b[1] = 1;
    p[0] = 1;
    p[1] = 0;
    dot = dot_prod2(b, a);
    dot_side[0] = dot_prod2(p, a);

    angle_a = acos(dot);
    angle_b = PI_2;
    angle_c = PI - angle_a - angle_b;

    x_ = (c->focal_distance/sin(angle_c)) * sin(angle_a);
    if (dot_side[0] >= EPSILON)
        x_ += c->w / 2;
    else
        x_ = (c->w / 2) - x_;

    /* Axe Y */
    a[0] = vec3[2];
    a[1] = vec3[1];
    unit2(a, a, NULL);
    b[0] = 1;
    b[1] = 0;
    p[0] = 0;
    p[1] = 1;
    dot = dot_prod2(b, a);

    dot_side[1] = dot_prod2(p, a);

    angle_a = acos(dot);
    angle_b = PI_2;
    angle_c = PI - angle_a - angle_b;

    y_ = (c->focal_distance/sin(angle_c)) * sin(angle_a);
    if (dot_side[1] >= EPSILON)
        y_ += c->h / 2;
    else
        y_ = (c->h / 2) - y_;
    if (x_ >= c->w || y_ >= c->h || x_ < 0 || y_ < 0)
        return (0);

    double       width_unit = (c->w / w);
    double       height_unit = (c->h / h);
        *x = (int)(x_ / width_unit);
        *y = (int)(y_ / height_unit);
    /** TEST**/
    /*
    *y = h - *y;
    *x = *x + 1;
    */
    return (1);
}

void        reverse_vec(struct s_point in, t_point *out)
{
    out->x = -in.x;
    out->y = -in.y;
    out->z = -in.z;
}

int         reverse_normal(t_triangle *T, struct s_point P)
{
    struct s_point  n_;
    struct s_point  n;

    copy_v3(T->n, (double *)&n);
    reverse_vec(n, &n_);
    add_v3((double *)&n, T->v0 , (double *)&n);
    add_v3((double *)&n_, T->v0, (double *)&n_);
    if (length3((double *)&n_) < length3((double *)&n))
    {
        reverse_vec(*((t_point *)T->n), (t_point *)T->n);
        return (1);
    }
    return (0);
}

void        draw_triangle(SDL_Surface *surface, uchar *rgb, int *a, int *b, int *c)
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

    vs1[0] = b[0] - a[0];
    vs1[1] = b[1] - a[1];
    vs2[0] = c[0] - a[0];
    vs2[1] = c[1] - a[1];
    x = minX;
    while (x <= maxX && x < surface->w && x > 0)
    {
      y = minY;
      while (y <= maxY && y < surface->h && y > 0)
      {
        q[0] = (double)x - a[0];
        q[1] = (double)y - a[1];
        cross_prod2(q, vs2, vfa);
        //a[0] * vs2[1] - q[1] * vs2[0]

        cross_prod2(vs1, vs2, vfb);
        //vs1[0] * vs2[1] - vs1[1] * vs2[0]

        div_v2(vfa, vfb, vf_out);
        s = vf_out[0];
        cross_prod2(vs1, q, vfa);
        div_v2(vfa, vfb, vf_out);
        t = vf_out[1];
        if ( (s >= 0) && (t >= 0) && (s + t <= 1))
          put_pixel(surface, rgb, x, y);
        y++;
      }
      x++;
    }
}

void         get_v3(double *vertices, int i, double *out, double *pos, double *rotate, double *scale)
{
    int            add;
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
    add = (vertices[1] * i);
    out[0] = *(vertices + add);
    out[1] = *(vertices + add + 1);
    out[2] = *(vertices + add + 2);
    if (scale)
    {
        out[0] *= scale[0];
        out[1] *= scale[1];
        out[2] *= scale[2];
    }
    if (rotate)
    {
        rot_vec3(x_axis, deg_to_rad(rotate[0]), out);
        rot_vec3(y_axis, deg_to_rad(rotate[1]), out);
        rot_vec3(z_axis, deg_to_rad(rotate[2]), out);
    }
    if (pos)
    {
        out[0] += pos[0];
        out[1] += pos[1];
        out[2] += pos[2];
    }
}
