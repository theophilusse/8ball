#include "geometry.h"

double       get_angle_r2(double *a, double *b)
{
    double       dot;
    /*double       length[2];

    length[0] = length2(a);
    length[1] = length2(b);*/
    dot = dot_prod2(a, b);
    ///return (dot / (length[0] * length[1]));
    return (acos(dot));
}

double       get_angle_d2(double *a, double *b)
{
    return (rad_to_deg(get_angle_r2(a, b)));
}

double       get_angle_r3(double *a, double *b)
{
    double       dot;
    /*double       length[2];

    length[0] = length2(a);
    length[1] = length2(b);*/
    dot = dot_prod3(a, b);
    ///return (dot / (length[0] * length[1]));
    return (acos(dot));
}

double       get_angle_d3(double *a, double *b)
{
    return (rad_to_deg(get_angle_r3(a, b)));
}

double       fast_angle_r3(double *a, double *b)
{
    double       dot;
    /*double       length[2];

    length[0] = length2(a);
    length[1] = length2(b);*/
    dot = fabs(dot_prod3(a, b));
    ///return (dot / (length[0] * length[1]));
    return (acos(dot));
}

double       fast_angle_d3(double *a, double *b)
{
    return (rad_to_deg(fast_angle_r3(a, b)));
}
