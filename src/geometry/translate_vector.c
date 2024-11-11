#include "geometry.h"

void         translate_vector(double *vector, double *rotate, double *scale, double *translate)
{
    uint             k;
    double           scale_bis[3];
    double           x_axis[3];
    double           y_axis[3];
    double           z_axis[3];

    if (!vector)
        return ;
    if (translate)
    {
        if (translate[0] != 0)
            vector[0] -= translate[0];
        if (translate[1] != 0)
            vector[1] -= translate[1];
        if (translate[2] != 0)
            vector[2] -= translate[2];
    }
    if (rotate)
    {
        x_axis[0] = 1;
        x_axis[1] = 0;
        x_axis[2] = 0;
        y_axis[0] = 0;
        y_axis[1] = 1;
        y_axis[2] = 0;
        z_axis[0] = 0;
        z_axis[1] = 0;
        z_axis[2] = 1;
        if (rotate[0] != 0)
            rot_vec3(x_axis, deg_to_rad(rotate[0] * -1), vector);
        if (rotate[1] != 0)
            rot_vec3(y_axis, deg_to_rad(rotate[1] * -1), vector);
        if (rotate[2] != 0)
            rot_vec3(z_axis, deg_to_rad(rotate[2] * -1), vector);
    }
    if (scale)
    {
        k = -1;
        while (++k < 3)
        {
            scale_bis[k] = 1.0;
            if (scale[k] != 0.0)
                scale_bis[k] /= scale[k];
            if (vector[k] != 0.0)
                vector[k] *= scale_bis[k];
        }
    }
}
