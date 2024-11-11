#include "camera.h"

/**
 ** refresh_orientation :
 ** Refresh the camera's X Y Z local axis from the new X Y Z orientation.
 ** Takes a camera pointer.
 **
**/
void            refresh_orientation(t_cam *c) /// GOOD?
{
    double       tmp_a[2];
    double       tmp_b[2];
    double       va[3];
    double       vb[3];

    tmp_a[0] = c->uz[0];
    tmp_a[1] = c->uz[2];
    tmp_b[0] = 0;
    tmp_b[1] = 1;
    unit2(tmp_a, tmp_a, NULL);
    c->pyr[1] = get_angle_r2(tmp_a, tmp_b);

    if (dot_prod3(c->uz, c->x) <= 0)
        c->pyr[1] = -c->pyr[1];

    copy_v3(c->uz, va);
    rot_vec3(c->y, -c->pyr[1], va);
    tmp_a[0] = va[2];
    tmp_a[1] = va[1];
    unit2(tmp_a, tmp_a, NULL);
    tmp_b[0] = 1;
    tmp_b[1] = 0;
    c->pyr[0] = get_angle_r2(tmp_a, tmp_b);

    if (dot_prod3(va, c->y) > 0)
        c->pyr[0] = -c->pyr[0];

    copy_v3(c->uy, vb);
    rot_vec3(c->y, -c->pyr[1], vb);
    rot_vec3(c->x, -c->pyr[0], vb);
    tmp_a[0] = vb[0];
    tmp_a[1] = vb[1];
    unit2(tmp_a, tmp_a, NULL);
    tmp_b[0] = 0;
    tmp_b[1] = 1;
    c->pyr[2] = get_angle_r2(tmp_a, tmp_b);/// - deg_to_rad(90);

    if (dot_prod3(vb, c->x) > 0)
        c->pyr[2] = -c->pyr[2];
    mtp_v3_by(c->uz, c->focal_distance, c->ud);
}