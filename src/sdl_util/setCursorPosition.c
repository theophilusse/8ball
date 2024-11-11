#include "sdl_util.h"

void setCursorPosition(t_mega *mega, int x, int y)
{
    RECT                    rect;
    struct s_ftData_zone    zone;
    int         pos[2];
    uint        dim[2];

    if (!mega || !mega->global)
        return ;
    if (GetWindowRect(mega->global->window, (LPRECT)&rect))
    {
        dim[0] = rect.right - rect.left;
        dim[1] = rect.bottom - rect.top;
        zone.pos[0] = rect.left;
        zone.pos[1] = rect.top;
        pos[0] = x + (int)rect.left;
        pos[1] = y + (int)rect.top;
        SetCursorPos(pos[0], pos[1]);
        if (isInZone(pos, dim, zone.pos))
        {
            DEBUG ///
            ///SDL_GetMouseState(&mouse.mousePos[0], &mouse.mousePos[1]);
            /*struct s_mouse      mouse;
            m*ouse = mega->mouse;*/
            /*mega->mouse.mouseDrag[0] = mega->mouse.mouseRle[0] - mega->mouse.mousePos[0];
            mega->mouse.mouseDrag[1] = mega->mouse.mouseRle[1] - mega->mouse.mousePos[1];
            */
            mega->mouse.mouseDrag[0] = 0;
            mega->mouse.mouseDrag[1] = 0;
            /*mega->mouse.mouseRle[0] = mega->mouse.mouseRle[0] - mega->mouse.mousePos[0];
            mega->mouse.mouseRle[1] = mega->mouse.mouseRle[1] - mega->mouse.mousePos[1];*/
            mega->mouse.mouseRle[0] = mega->mouse.mouseRle[0] - mega->mouse.mousePos[0];
            mega->mouse.mouseRle[1] = mega->mouse.mouseRle[1] - mega->mouse.mousePos[1];
            mega->mouse.mousePos[0] = x;
            mega->mouse.mousePos[1] = y;
            /*mega->mouse.onClick[0] = 0;
            mega->mouse.onClick[1] = 0;*/
        }
    }
}
