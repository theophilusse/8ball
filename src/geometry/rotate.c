#include "geometry.h"

/***Vec2f		myRotate(Vec2f unit, f32 angle)
{
	f32						rad;
	f32						a;
	f32						b;

	rad = angle * 3.141592f/180;
	a = (unit.x * Maths::Cos(rad)) + (unit.y * (Maths::Sin(rad) * -1));
	b = (unit.y * Maths::Sin(rad)) + (unit.y * Maths::Cos(rad));
	unit.x = a;
	unit.y = b;
	return unit;
}***/

void		rot_vec2(double *unit, double angle, double *out)
{
	double						rad;
	double						a;
	double						b;

	rad = deg_to_rad(angle);
	a = unit[0] * cos(rad) - unit[1] * sin(rad);
	b = unit[1] * cos(rad) + unit[0] * sin(rad);
	out[0] = a;
	out[1] = b;
}

void			rot_vec3(double *axis, double a, double *lev)
{
	double			q[3];
	double				cosa;
	double				sina;

	cosa = (double)cos(a);
	sina = (double)sin(a);
	q[0] = (cosa + (1 - cosa) * axis[0] * axis[0]) * lev[0];
	q[0] += ((1 - cosa) * axis[0] * axis[1] - axis[2] * sina) * lev[1];
	q[0] += ((1 - cosa) * axis[0] * axis[2] + axis[1] * sina) * lev[2];
	q[1] = ((1 - cosa) * axis[0] * axis[1] + axis[2] * sina) * lev[0];
	q[1] += (cosa + (1 - cosa) * axis[1] * axis[1]) * lev[1];
	q[1] += ((1 - cosa) * axis[1] * axis[2] - axis[0] * sina) * lev[2];
	q[2] = ((1 - cosa) * axis[0] * axis[2] - axis[1] * sina) * lev[0];
	q[2] += ((1 - cosa) * axis[1] * axis[2] + axis[0] * sina) * lev[1];
	q[2] += (cosa + (1 - cosa) * axis[2] * axis[2]) * lev[2];
	lev[0] = q[0];
	lev[1] = q[1];
	lev[2] = q[2];
}

/*** (Absolute to Relative orientation) ***/
void            translate_angle_absrel(double *vec, t_cam *c, double *ret)
{
    double       unit_vector[3];
    double       l;

    l = length3(vec);
    unit3(vec, unit_vector, &l);
    rot_vec3(c->y, -c->pyr[1], unit_vector); /// 'Marche'
    rot_vec3(c->x, -c->pyr[0], unit_vector);
    rot_vec3(c->z, -c->pyr[2], unit_vector);
    if (l != 1)
        mtp_v3_by(unit_vector, l, ret);
    else
        copy_v3(unit_vector, ret);
}

/*** (Relative to Absolute orientation) ***/
void            translate_angle_relabs(double *vec, double *x, double *y, double *z, double *euler_rotation, double *ret)
{
    double       unit_vector[3];
    double       l;

    l = length3(vec);
    unit3(vec, unit_vector, &l);
    rot_vec3(z, euler_rotation[2], unit_vector);
    rot_vec3(x, euler_rotation[0], unit_vector);
    rot_vec3(y, euler_rotation[1], unit_vector);
    if (l != 1)
        mtp_v3_by(unit_vector, l, ret);
    else
        copy_v3(unit_vector, ret);
}
