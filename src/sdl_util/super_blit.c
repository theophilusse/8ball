#include "sdl_util.h"

void                super_blit(t_mega *mega)
{
    int                sz;
    SDL_Surface        *surface[8];

    if (!mega)
        return ;
    /** Consecutive blits. **/
    blit_mergeAlpha(mega->camera->data->backbuffer, mega->viewport);
    if (mega->stcl->option.edit_mode)
        blit_mergeAlpha(mega->hud_viewport, mega->viewport);
    if (mega->stcl->option.display_log == 1)
        blit_mergeAlpha(mega->log_viewport, mega->viewport);
    if (mega->ui->active == 1)
        blit_mergeAlpha(mega->ui_viewport, mega->viewport);
    SDL_FillRect(mega->viewport_swp, 0, SDL_MapRGB(mega->viewport_swp->format, 0, 64, 0));
    DEBUG ///
    /** blit_at_dim(mega->viewport, mega->viewport_swp, 0, 0, NULL, NULL, 0); **/ // Crash.
    blit_at(mega->viewport, mega->viewport_swp, 0, 0);
    DEBUG ///
    refresh(mega->viewport, mega->screen); // Render !
}
