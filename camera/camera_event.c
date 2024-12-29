#include "camera.h"

void         camera_event(t_cam *camera, SDLKey sym)
{
    if (!camera)
        return ;
    /** Camera Movement **/
    if (sym == SDLK_END)
        reset_camera(camera, CAMERA_KEEP_MODELSTACK);
    if (sym == SDLK_DOWN)
        sub_v3(camera->o, camera->uy, camera->o);
    if (sym == SDLK_UP)
        add_v3(camera->o, camera->uy, camera->o);
    if (sym == SDLK_LEFT)
        sub_v3(camera->o, camera->ux, camera->o);
    if (sym == SDLK_RIGHT)
        add_v3(camera->o, camera->ux, camera->o);
    if (sym == SDLK_PAGEDOWN)
        sub_v3(camera->o, camera->uz, camera->o);
    if (sym == SDLK_PAGEUP)
        add_v3(camera->o, camera->uz, camera->o);
    if (sym == SDLK_KP_PLUS)
        camera->focal_distance += 0.01;
    if (sym == SDLK_KP_MINUS)
        camera->focal_distance -= 0.01;
    if (sym == SDLK_KP2)
    {
        rot_vec3(camera->ux, deg_to_rad(5), camera->uy);
        rot_vec3(camera->ux, deg_to_rad(5), camera->uz);
    }
    if (sym == SDLK_KP8)
    {
        rot_vec3(camera->ux, -deg_to_rad(5), camera->uy);
        rot_vec3(camera->ux, -deg_to_rad(5), camera->uz);
    }
    if (sym == SDLK_KP6)
    {
        rot_vec3(camera->uy, deg_to_rad(5), camera->ux);
        rot_vec3(camera->uy, deg_to_rad(5), camera->uz);
    }
    if (sym == SDLK_KP4)
    {
        rot_vec3(camera->uy, -deg_to_rad(5), camera->ux);
        rot_vec3(camera->uy, -deg_to_rad(5), camera->uz);
    }
    if (sym == SDLK_KP7)
    {
        rot_vec3(camera->uz, deg_to_rad(5), camera->ux);
        rot_vec3(camera->uz, deg_to_rad(5), camera->uy);
    }
    if (sym == SDLK_KP9)
    {
        rot_vec3(camera->uz, -deg_to_rad(5), camera->ux);
        rot_vec3(camera->uz, -deg_to_rad(5), camera->uy);
    }
    refresh_orientation(camera);
}
