#ifndef GEOMETRY_H
 #define GEOMETRY_H

 #include "8ball.h"

#define deg_to_rad(deg) (deg * 3.14159265358979 / 180)
#define rad_to_deg(rad) (rad * 180 / 3.14159265358979)

 void        add_v2(const double *a, const double *b, double *ret);
 void        sub_v2(const double *a, const double *b, double *ret);

 void        mtp_v2(const double *a, const double *b, double *ret);
 void        mtp_v2_by(const double *a, const double b, double *ret);
 void        div_v2(const double *a, const double *b, double *ret);

 double          dot_prod2(double *a, double *b);
 void           cross_prod2(double *a, double *b, double *ret);
 double          length2(const double *v);
 double          fast_length2(const double *v);
 void           unit2(const double *v, double *ret, double *length);
 void            copy_v2(double *in, double *out);
 double       get_angle_r2(double *a, double *b);
 double       get_angle_r3(double *a, double *b);
 double       fast_angle_r3(double *a, double *b);
 double       get_angle_d2(double *a, double *b);
 double       get_angle_d3(double *a, double *b);
 double       fast_angle_d3(double *a, double *b);

 void		rot_vec2(double *unit, double angle, double *out);

 ///void        add_v3(const double *a, const double *b, double *ret);
 void        add_v3(double *a, double *b, double *ret);
 void        sub_v3(const double *a, const double *b, double *ret);

 void        mtp_v3(const double *a, const double *b, double *ret);
 void        mtp_v3_by(const double *a, const double b, double *ret);
 void        div_v3(const double *a, const double *b, double *ret);
 void        div_v3_by(const double *a, const double b, double *ret);

 double          dot_prod3(double *a, double *b);
 void           cross_prod3(double *a, double *b, double *ret);
 double          length3(const double *v);
 double          fast_length3(const double *v);
 void           unit3(const double *v, double *ret, double *length);
 void            copy_v3(double *in, double *out);
void			rot_vec3(double *axis, double a, double *lev);

///void            translate_angle_zyx(double *vec, double *x, double *y, double *z, double *euler_rotation, double *ret);
void            translate_angle_absrel(double *vec, t_cam *c, double *ret);
void            translate_angle_relabs(double *vec, double *x, double *y, double *z, double *euler_rotation, double *ret);


void            inv_v2(double *in, double *out);
void            inv_v3(double *in, double *out);

int             _min(int a, int b);
int             _max(int a, int b);
void            clamp_v3(double *v, int max_value, int min_value);

void                translate_vector(double *vector, double *rotate, double *scale, double *translate);
int             reverse_normal(t_triangle *T, struct s_point P);


#endif // GEOMETRY_H
