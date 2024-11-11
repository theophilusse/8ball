#include "input_manager.h"

int                 user_mouseButtonDown(t_mega *mega, int flg)
{
    SDLMod                  mod;
    t_tool                  *tool;
    struct s_mouse              mouse;
    struct s_hud_arrow      tmparrows;
    double                  vec[2];
    int             select_err;

    if (!mega)
        return (1);
    mouse = mega->mouse;
    tool = &mega->tool[mega->currentTool];
    if (mouse.mouseButtonUp == 0)
        return (0);
    SDL_GetMouseState(&mouse.onClick[0], &mouse.onClick[1]);
    if (mega->stcl->option.edit_mode == 1 && tool->hud.active == 1)
    {
        hud_project(mega->camera, &tool->hud, 2); /// Refresh center
        mouse.cacheClick[0] = mouse.onClick[0] - (int)tool->hud.org.coord[0];
        mouse.cacheClick[1] = mouse.onClick[1] - (int)tool->hud.org.coord[1];
        vec[0] = (double)mouse.cacheClick[0];
        vec[1] = (double)mouse.cacheClick[1];
        mouse.cacheLengthClick = length2(vec);
        unit2(vec, mouse.cacheUnitClick, &mouse.cacheLengthClick);
    }
    mouse.leftButton = 0;
    mouse.mouseButtonUp = 0;
    /*mega->dragSum[0] = 0;
    mega->dragSum[1] = 0;
    mega->dragSum[2] = 0;
    mouse.drag_ac[0] = 0;
    mouse.drag_ac[1] = 0;
    mega->axis_hud_reldot = 0;
    mega->axis_hud_absdot = 0;
    mega->dragFactor = 0;
    mega->dragFactorScale = 0;
    mega->dragLength = 0;
    mega->dragSumLength = 0;*/
    ////select.vertice = NULL;
    mouse.motion_ft = USER_MOUSE_MOTION_IDLE;
    if (mega->event.button.button == SDL_BUTTON_RIGHT)
    {
        mouse.motion_ft = USER_MOUSE_MOTION_CAMERA_DRAGPOS;
    }
    if (mega->event.button.button == SDL_BUTTON_MIDDLE)
    {
        mouse.motion_ft = USER_MOUSE_MOTION_CAMERA_DRAGDIR;
    }
    ///if (mega->event.button.button == SDL_BUTTON(SDL_BUTTON_WHEELUP)) // scroll up
    if (mega->event.button.button == 4) // scroll up
        mega->input_manager[USER_CAMERA_ZOOM](mega, 1);
    ///if (mega->event.button.button == SDL_BUTTON(SDL_BUTTON_WHEELDOWN)) // scroll up
    if (mega->event.button.button == 5) // scroll up
        mega->input_manager[USER_CAMERA_ZOOM](mega, 0);
    mega->mouse = mouse;
    if (mega->event.button.button == SDL_BUTTON_LEFT)
    {
        mega->mouse.leftButton = 1;
        mega->input_manager[USER_ON_LEFT_CLICK](mega, 0); /// TMP (call tool)
    }
    return (0);
}
