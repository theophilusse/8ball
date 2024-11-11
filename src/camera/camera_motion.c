#include "camera.h"

void            rotate_camera_dir_drag(t_cam *camera, int *dragVec)
{
    double          uy[4];
    double          drag[2];

    ///return ;
    if (!camera || !dragVec)
        return ;
    copy_v3(camera->y, uy); // GLOBAL Y
    drag[0] = deg_to_rad(dragVec[0] / (camera->focal_distance + 5));
    drag[1] = deg_to_rad(dragVec[1] / (camera->focal_distance + 5));

    rot_vec3(camera->ux, drag[1], camera->uy);
    rot_vec3(camera->ux, drag[1], camera->uz);
    /*rot_vec3(uy, drag[0], camera->ux);
    rot_vec3(uy, drag[0], camera->uz);*/
    rot_vec3(camera->uy, drag[0], camera->ux);
    rot_vec3(camera->uy, drag[0], camera->uz);
}

void            rotate_camera_pos_drag(t_cam *camera, int *dragVec)
{
    double          ux[4];
    double          uy[4];
    double          o[4];
    double          v[4];
    double          drag[2];
    double          dragFactor;

    if (!camera || !dragVec)
        return ;
    copy_v3(camera->ux, ux);
    /**copy_v3(camera->uy, uy);**/
    copy_v3(camera->y, uy); // GLOBAL Y
    copy_v3(camera->o, o);
    copy_v3(o, v);

    drag[0] = (double)dragVec[0] * 0.1;
    drag[1] = (double)dragVec[1] * 0.1;
    dragFactor = sqrt(length2(drag));
    drag[0] = deg_to_rad(drag[0] * dragFactor);
    drag[1] = deg_to_rad(drag[1] * dragFactor);
    rot_vec3(ux, drag[1], o);
    rot_vec3(uy, drag[0], o);
    copy_v3(o, camera->o);

    rot_vec3(ux, drag[1], camera->ux);
    rot_vec3(uy, drag[0], camera->ux);
    rot_vec3(ux, drag[1], camera->uy);
    rot_vec3(uy, drag[0], camera->uy);
    rot_vec3(ux, drag[1], camera->uz);
    rot_vec3(uy, drag[0], camera->uz);
    rot_vec3(ux, drag[1], camera->ud);
    rot_vec3(uy, drag[0], camera->ud);

    /**
    add_v3(v, camera->ux, vx);
    //rot_vec3(ux, drag[1], vx);
    rot_vec3(uy, drag[0], vx);
    sub_v3(vx, o, camera->ux);
    unit3(camera->ux, camera->ux, NULL);

    add_v3(v, camera->uy, vx);
    //rot_vec3(ux, drag[1], vx);
    rot_vec3(uy, drag[0], vx);
    sub_v3(vx, o, camera->uy);
    unit3(camera->uy, camera->uy, NULL);

    add_v3(v, camera->uz, vx);
    //rot_vec3(ux, drag[1], vx);
    rot_vec3(uy, drag[0], vx);
    sub_v3(vx, o, camera->uz);
    unit3(camera->uz, camera->uz, NULL);

    add_v3(v, camera->ud, vx);
    //rot_vec3(ux, drag[1], vx);
    rot_vec3(uy, drag[0], vx);
    sub_v3(vx, o, camera->ud);
    unit3(camera->ud, camera->ud, NULL);
    **/
}


/**

    typedef struct          s_cam
    {
        double      o[4];
        double      pyr[4]; // Absolute Orientation Pitch-Yaw-Roll
        double      ud[4]; // Focal To Lens (focal_distance * direction)
        double      x[4];  // Absolute X (aka struct s_point)
        double      y[4];  // Absolute Y
        double      z[4];  // Absolute Z
        double      ux[4]; // Relative X (aka struct s_point)
        double      uy[4]; // Relative Y
        double      uz[4]; // Relative Z (direction)
        double      h; // Frustum Dimensions
        double      w;
        double      hh; // Precalc Frustum / 2
        double      hw;
        double      unit_w;
        double      unit_h;
        double      focal_distance;
        uint        vw;
        uint        vh;
        t_camdata      *data;
    }                       t_cam;

**/
