#include "input_manager.h"

static int             mouse_mirror(t_mega *mega, int *mousePos, uchar side, uint w, uint h)
{
    int         x;
    int         y;

    if (!mega || !mousePos || side > 3)
        return (0);
    if (side == 0)
    {
        x = w + 8;
        y = mousePos[1];// + 30;
    }
    if (side == 1)
    {
        x = 8;
        y = mousePos[1];// + 30;
    }
    if (side == 2)
    {
        x = mousePos[0];
        y = h + 29;
    }
    if (side == 3)
    {
        x = mousePos[0];
        y = 31;
    }
    mega->mouse.skipDrag = 1;
    setCursorPosition(mega, x, y);
    return (1);
}

static int          mouse_outOfBound(t_mega *mega, uint w, uint h, int buttonUp)
{
    POINT       pos;
    int         mousePos[2];
    int         zero[2];
    uint        screenBound[2];
    uchar       side;

    if (!mega || buttonUp == 1)
        return (0);
    if (GetCursorPos((LPPOINT)&pos) == 0)
        return (0);
    mousePos[0] = (int)pos.x;
    mousePos[1] = (int)pos.y;
    zero[0] = 0;
    zero[1] = 0;
    screenBound[0] = w;
    screenBound[1] = h;
    if (isInZone(zero, screenBound, mousePos) == 1)
        return (0);
    side = 255;
    if (mousePos[0] <= 0) /// Left.
        side = 0;
    if (mousePos[0] >= (int)w) /// Right.
        side = 1;
    if (mousePos[1] < 30) /// Top.
        side = 2;
    if (mousePos[1] >= (int)h + 30) /// Down.
        side = 3;
    if (mouse_mirror(mega, mousePos, side, w, h))
        return (1);
    return (0);
}

int         inputManager_loop(t_mega *mega, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
{
    SDLMod          mod;
    int             flg;
    /* struct s_mega   mega; */
    /***
    ***/
    /*struct s_vertice_dist hud_select;*/

    /*int                 lctrl_down = 0;*/
    /***
    ***/
    mega->ui->sigRefresh = 1;
    flg = 0;
    int userIdle = 0;
    int done = 0;
    while (done == 0)
    {
        /// FRAME
        if (mega->ui->sigFrame == 1)
        {
            if (frame(mega, mega->mouse.draw_marker, 1))
                return (1);
            mega->ui->sigFrame = 0;
        }
        /// FRAME
        if (userIdle++ > 1 && mega->ui)
        {
            SDL_FillRect(mega->direct_viewport, 0, SDL_MapRGBA(mega->direct_viewport->format, 0, 64, 0, SDL_ALPHA_OPAQUE));
            blit(mega->viewport_swp, mega->direct_viewport);
            ui_displayCursorCaption(mega, mega->direct_viewport); /// Keep.
            blit(mega->direct_viewport, mega->screen);
            SDL_Flip(mega->screen);
            userIdle = 0;
        }
        #ifdef MOUSE_OOB
            if (mega->mouse.leftButton == 1)
                mouse_outOfBound(mega, (uint)mega->screen->w, (uint)mega->screen->h, mega->mouse.mouseButtonUp);
        #endif
        // message processing loop
        ///while (SDL_PollEvent(&mega->event) != 0)
        ///if (SDL_PollEvent(&mega->event) != 0)
        if (SDL_PollEvent(&mega->event) != 0)
        {
            userIdle = 0;
            mod = SDL_GetModState();
            // check for messages
            switch (mega->event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                {
                    /*mega->input_manager[0](mega, 0);*/
                    return (0);
                }
                case SDL_VIDEORESIZE:
                {
                    DEBUG ///
                    if (mega->input_manager[USER_RESIZE_WINDOW](mega, 0))
                        return (1);
                    mega->ui->sigFrame = 1;
                    ///break;
                    continue;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    DEBUG ///
                    if (mega->input_manager[USER_MOUSE_BUTTON_DOWN](mega, 0))
                        return (1);
                    mega->ui->sigFrame = 1;
                    ///mega->mouse.mouseButtonUp = 0; // Test
                    /*if (frame(*mega, mega->mouse.draw_marker, 1))
                    {
                        return (1);
                    }
                    */
                    ///break;
                    continue;
                }
                case SDL_MOUSEMOTION:
                {
                    DEBUG ///
                    if (mega->input_manager[USER_MOUSE_MOTION](mega, 0))
                        return (1);
                    ///userIdle = mega->mouse.drag_ac <= 5 ? -1 : userIdle;
                    if (mega->mouse.mouseButtonUp == 0) /** Mouse Button Down **/
                    {
                        if (mega->mouse.motion_ft != USER_MOUSE_MOTION_IDLE || /** Tool conditions **/
                            mega->tool[mega->currentTool].hud.active == 2)
                        {
                            DEBUG ///
                            mega->ui->sigFrame = 1;
                        }
                        else
                        {
                            ///mega->ui->sigRefresh = 1; /// Test.
                            ui_main(mega, mega->ui);
                            super_blit(mega);
                        }
                    }
                    ///break;
                    continue;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    if (mega->input_manager[USER_MOUSE_BUTTON_UP](mega, 0))
                        return (1);
                    ///mega->mouse.mouseButtonUp = 1; // Test
                    /*
                    if (frame(*mega, mega->mouse.draw_marker, 0))
                    {
                        return (1);
                    }
                    */
                    ///break;
                    continue;
                }
                case SDL_KEYDOWN:
                {
                    DEBUG ///
                    flg = 0;
                    if ((mod & KMOD_LCTRL) && mega->event.key.keysym.sym == SDLK_w)
                        flg = 1;
                    if (flg == 1 && (mod & KMOD_LSHIFT) && mega->event.key.keysym.sym == SDLK_w)
                        flg = 2;
                    if (mega->input_manager[USER_KEY_DOWN](mega, flg))
                        return (1);
                    mega->keyboardUp = 0;
                    mega->ui->sigFrame = 1;
                    /*if (frame(*mega, mega->mouse.draw_marker, 0))
                        return (1);
                    */
                    ///break;
                    continue;
                }
                case SDL_KEYUP:
                {
                    DEBUG ///
                    if (mega->keyboardUp != 0)
                        continue;
                        ///break;
                    if (mega->input_manager[USER_KEY_UP](mega, 0))
                        return (1);
                    mega->ui->sigFrame = 1;
                        /*
                    if (frame(mega, mega.mouse.draw_marker, 0)) /// Test
                        return (1);*/
                    mega->keyboardUp = 1;
                    ///break;
                    continue;
                }
                default:
                {
                    DEBUG ///
                    break;
                }
                ///default : continue;
            } // end switch
        }
    }
    DEBUG ///
    return (0);
}
