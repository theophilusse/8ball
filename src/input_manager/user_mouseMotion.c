#include "input_manager.h"

static char             *strUppercase(char *s)
{
    static char             buf[STRING_SIZE];

    buf[0] = '\0';
    strncpy(buf, (const char *)s, strlen(s));
    return (strupr(buf));
}

void             ui_updateCursor(t_userInterface *ui, int *mousePos)
{
    t_ui_box            *box;
    uchar               boxSide;
    uchar               handle;

    if (!ui)
        return ;
    if (!mousePos || ui->active == 0 || ui->event.type != UI_EVENT_NONE)/// && mega->ui->event.type != UI_EVENT_BARGRAB)
    {
        SDL_SetCursor(ui->cursor[UI_CURSOR_ARROW]);
        return ;
    }
    box = NULL;
    ///handle = ui_getFrontBoxHandle(ui, 255); // Old z-Index System
    handle = ui_getFrontBoxHandle(ui); /// Front Box.
    if (handle != UI_BOX_COUNT)
        box = &ui->box[handle];
    /****/
    boxSide = 8;
    int     relClick[2] = {0, 0};
    if (box)
    {
        relClick[0] = mousePos[0] - box->pos[0];
        relClick[1] = mousePos[1] - box->pos[1];
    }
    ///if (ui_isResize(box, mousePos, &boxSide) && boxSide < 8)
    if (ui_isResize(box, relClick, &boxSide) && boxSide < 8)
    {
        if (boxSide >= 4)
        {
            if (boxSide >= 6)
            {
                if (boxSide == 6)
                    SDL_SetCursor(ui->cursor[UI_CURSOR_CORNER_DL]);
                else
                    SDL_SetCursor(ui->cursor[UI_CURSOR_CORNER_DR]);
            }
            else
            {
                if (boxSide == 4)
                    SDL_SetCursor(ui->cursor[UI_CURSOR_CORNER_UL]);
                else
                    SDL_SetCursor(ui->cursor[UI_CURSOR_CORNER_UR]);
            }
        }
        else
        {
            if (boxSide >= 2)
            {
                SDL_SetCursor(ui->cursor[UI_CURSOR_ARROW_HRZ]);
            }
            else
            {
                SDL_SetCursor(ui->cursor[UI_CURSOR_ARROW_VRT]);
            }
        }
    }
    else
        SDL_SetCursor(ui->cursor[UI_CURSOR_ARROW]);
}

int             user_mouseMotion(t_mega *mega, int flg)
{
    t_tool              *tool;
    double              tmp_vec[2];
    struct s_mouse      mouse;

    if (!mega)
        return (1);
    mouse = mega->mouse;
    tool = &mega->tool[mega->currentTool];
    /// Keep Motion Coherent when mouse reach the window boundary.
    if (mouse.skipDrag < 1)
    {
        SDL_GetRelativeMouseState(&mouse.mouseDrag[0], &mouse.mouseDrag[1]);
        mouse.mouseRle[0] += mouse.mouseDrag[0];
        mouse.mouseRle[1] += mouse.mouseDrag[1];
        /*mouse.mouseRle[0] = mouse.mouseDrag[0];
        mouse.mouseRle[1] = mouse.mouseDrag[1];*/
    }
    else
    {
        mouse.mouseRle[0] = 0;
        mouse.mouseRle[1] = 0;
        mouse.skipDrag = 0;
    }
    SDL_GetMouseState(&mouse.mousePos[0], &mouse.mousePos[1]);

    /** uint mouseMap[2]; /// Unused for nox;
    mouse.mouseOff[0] = (mouse.mousePos[1] * mega->viewport->w) + mouse.mousePos[0];
    mouse.mouseOff[1] = mouse.mouseOff[0];
    */

    mouse.draw_marker = tool->hud.active != 2 ? 0 : 1;
    mega->mouse = mouse;

    /***
    if (mega->ui)
    {
        ui_updateCursor(mega->ui, mouse.mousePos);///
        ui_displayCursorCaption(mega, mega->ui_viewport);
    }***/
    if (mega->ui)
        ui_updateCursor(mega->ui, mouse.mousePos);///
    if (mouse.mouseButtonUp == 1)
        return (0);
    if (mouse.motion_ft != USER_MOUSE_MOTION_IDLE)
    {
        ///printf("Mouse Motion FT : [%d]\n", mega.mouse.motion_ft);
        mega->input_manager[mouse.motion_ft](mega, 0);
    }
    //else if (mouse.leftButton == 1)
    if (mouse.leftButton == 1)
    {
        /*** UI mouseMotion / UI_EVENTS ***/
        if (mega->ui->active != 0)
        {
            ui_interfaceMotion(mega, mega->ui, mouse);
            /**if (!ui_interfaceMotion(mega, mega->ui, mouse)) /// ScrollBar Quit ???
                return (1);*/
        }
        /*** HUD mouseMotion ***/
        if (tool->hud.active == 2)
        {
            if (tool->hud.data.mouse_motion((void *)mega, 1))
                return (1);
            tool->proceed((void *)mega, 1);
        }
    }
    return (0);
}
