#include "input_manager.h"

int             user_keyup(t_mega *mega, int flg)
{
    ///if (event.key.keysym.sym == SDLK_LCTRL)
    ///if (event.key.keysym.mod & KMOD_LCTRL)
    ///if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL)
        ///lctrl_down = 0;
    /*if ( (SDL_GetModState() & KMOD_ALT) )
        return (0);*/
    mega->ui->sigRefresh = 1;
    /**
        ui_main(mega, mega->ui, 0);
        blit_mergeAlpha(mega->camera->data->backbuffer, mega->viewport);//Test
        blit_mergeAlpha(mega->ui_viewport, mega->viewport);
        refresh(mega->viewport, mega->screen); // Render !
    */
    ///mega->ui->sigRefresh = 1;
    return (0);
}
