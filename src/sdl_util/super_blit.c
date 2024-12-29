#include "sdl_util.h"

void                super_blit(t_mega *mega)
{
    int                sz;
    SDL_Surface        *surface[8];

    DEBUG //
    if (!mega)
        return ;
    /** Consecutive blits. **/
    printf("VIEWPORT @ %p\n", mega->viewport);// DEBUG
    printf("backbuffer @ %p\n", mega->camera->data->backbuffer);// DEBUG
    printf("hud_viewport @ %p\n", mega->hud_viewport);// DEBUG
    printf("log_viewport @ %p\n", mega->log_viewport);// DEBUG
    printf("ui_viewport @ %p\n", mega->ui_viewport);// DEBUG
    printf("viewport_swp @ %p\n", mega->viewport_swp);// DEBUG
    printf("screen @ %p\n", mega->screen);// DEBUG
    DEBUG //
    blit_mergeAlpha(mega->camera->data->backbuffer, mega->viewport); // DEBUG TODO REMETTRE
    DEBUG //
    if (mega->stcl->option.edit_mode)
        blit_mergeAlpha(mega->hud_viewport, mega->viewport);
    DEBUG //
    if (mega->stcl->option.display_log == 1)
        blit_mergeAlpha(mega->log_viewport, mega->viewport);
    DEBUG //
    if (mega->ui->active == 1)
        blit_mergeAlpha(mega->ui_viewport, mega->viewport);
    DEBUG //
    SDL_FillRect(mega->viewport_swp, 0, SDL_MapRGB(mega->viewport_swp->format, 0, 64, 0));
    DEBUG ///
    /** blit_at_dim(mega->viewport, mega->viewport_swp, 0, 0, NULL, NULL, 0); **/ // Crash.
    blit_at(mega->viewport, mega->viewport_swp, 0, 0);
    DEBUG ///
    refresh(mega->viewport, mega->screen); // Render !
}
