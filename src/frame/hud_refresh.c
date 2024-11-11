#include "frame.h"

void                hud_refresh(SDL_Surface *dst, t_mega *mega, t_tool *tool)
{
    if (hud_project(mega->camera, &tool->hud, 1))
        hud_draw(dst, mega->camera, tool, mega->mouse.mousePos);
}