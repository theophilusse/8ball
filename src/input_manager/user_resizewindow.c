#include "input_manager.h"

static void     release_frameBuffers(t_mega *mega)
{
    /// VIEWPORTS
    if (!mega)
        return ;
    if (mega->screen)
        SDL_FreeSurface(mega->screen);
    if (mega->viewport)
        SDL_FreeSurface(mega->viewport);
    if (mega->work_viewport)
        SDL_FreeSurface(mega->work_viewport);
    if (mega->hud_viewport)
        SDL_FreeSurface(mega->hud_viewport);
    if (mega->log_viewport)
        SDL_FreeSurface(mega->log_viewport);
    if (mega->ui_viewport)
        SDL_FreeSurface(mega->ui_viewport);
    if (mega->direct_viewport)
        SDL_FreeSurface(mega->direct_viewport);
    if (mega->viewport_swp)
        SDL_FreeSurface(mega->viewport_swp);
    mega->screen = NULL;
    mega->viewport = NULL;
    mega->hud_viewport = NULL;
    mega->log_viewport = NULL;
    mega->ui_viewport = NULL;
    mega->direct_viewport = NULL;
    mega->viewport_swp = NULL;
    mega->work_viewport = NULL;
}

static int            renew_frameBuffers(t_mega *mega, SDL_Event event)
{
    if (!mega)
        return (1);
    release_frameBuffers(mega);
    mega->screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    ///mega->viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask);
    mega->viewport = new_surface32(mega->screen->w, mega->screen->h);
    ///mega->hud_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask);
    mega->hud_viewport = new_surface32(mega->screen->w, mega->screen->h);
    ///mega->log_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask);
    mega->log_viewport = new_surface32(mega->screen->w, mega->screen->h);
    ///mega->ui_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask);
    mega->ui_viewport = new_surface32(mega->screen->w, mega->screen->h);
    ///mega->direct_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask);
    mega->direct_viewport = new_surface32(mega->screen->w, mega->screen->h);
    ///mega->viewport_swp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask);
    mega->viewport_swp = new_surface32(mega->screen->w, mega->screen->h);
    ///mega->work_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask);
    mega->work_viewport = new_surface32(mega->screen->w, mega->screen->h);
    /** Clear UI **/
    set_alpha(mega->hud_viewport, SDL_ALPHA_TRANSPARENT);
    set_alpha(mega->log_viewport, SDL_ALPHA_TRANSPARENT);
    set_alpha(mega->ui_viewport, SDL_ALPHA_TRANSPARENT);
    set_alpha(mega->direct_viewport, SDL_ALPHA_TRANSPARENT);
    set_alpha(mega->viewport_swp, SDL_ALPHA_TRANSPARENT);
    return (0);
}

int            user_resizeWindow(t_mega *mega, int flg)
{
    SDL_Event       event;

    if (!mega)
        return (1);
    event = mega->event;
    /**
            - BUG -
            DEBUG ///
            Strange loop behavior when mouse is outside the re-sized window.
            May be instable.
    **/
    DEBUG ///
    if (renew_frameBuffers(mega, event))
        return (1);
    if (resize_camera_viewport(mega->camera, mega->stcl, event.resize.w, event.resize.h))
        return (1);

    if (mega->screen->w < mega->ui->morpho.surface->w ||
        mega->screen->h < mega->ui->morpho.surface->h)
    {
        mega->ui->morpho.active = -1;
    }
    else
    {
        mega->ui->morpho.pos[0] = mega->screen->w - mega->ui->morpho.surface->w;
        mega->ui->morpho.pos[1] = mega->screen->h - mega->ui->morpho.surface->h;
    }
    halt_program(&mega->ui->sigRefresh, (void *)mega);
    //ui_main(mega, mega->ui);
    ///frame(*mega, 0, 0);
    ///mega->ui->sigFrame = 1;
    ///mega->ui->sigRefresh = 1;
    return (0);
}
