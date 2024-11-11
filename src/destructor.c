#include "8ball.h"

/**
 ** Author : ttrossea
 ** destructor.c :
 ** Several destructive functions.
 **
 ** Use root_destructor function to free the whole program before
 ** exit. Keeping the program leaks-free.
 **
 ** - root_destructor
 **
**/

/**
 ** root_destructor :
 ** Deallocate mega structure, failsafe.
 **
**/
int         root_destructor(t_mega *mega, int isErr)
{
    uint            i;

    DEBUG ///
    if (!mega)
        return (1);
    DEBUG ///
    if (mega->picture)
    {
        SDL_FreeSurface(mega->picture);
        mega->picture = NULL;
    }
    DEBUG ///
    if (mega->viewport)
    {
        SDL_FreeSurface(mega->viewport);
        mega->viewport = NULL;
    }
    DEBUG ///
    if (mega->work_viewport)
    {
        SDL_FreeSurface(mega->work_viewport);
        mega->work_viewport = NULL;
    }
    DEBUG ///
    if (mega->log_viewport)
    {
        SDL_FreeSurface(mega->log_viewport);
        mega->log_viewport = NULL;
    }
    if (mega->hud_viewport)
    {
        SDL_FreeSurface(mega->hud_viewport);
        mega->hud_viewport = NULL;
    }
    if (mega->ui_viewport)
    {
        SDL_FreeSurface(mega->ui_viewport);
        mega->ui_viewport = NULL;
    }
    if (mega->direct_viewport)
    {
        SDL_FreeSurface(mega->direct_viewport);
        mega->direct_viewport = NULL;
    }
    if (mega->viewport_swp)
    {
        SDL_FreeSurface(mega->viewport_swp);
        mega->viewport_swp = NULL;
    }
    DEBUG ///
    if (mega->screen) /** CRASH ??? **/
    {
        DEBUG ///
        SDL_FreeSurface(mega->screen);
        DEBUG ///
        mega->screen = NULL; ///
        /** SDL_Quit(); **/ // Moved down?
        DEBUG ///
    }
    camera_release(mega);
    DEBUG ///
    if (mega->stcl) /// Crash La dedans.
        release_opencl(*mega->stcl);
    DEBUG ///
    if (mega->timeMachine)
        release_history(&mega->timeMachine); //// Todo
    DEBUG ///
    if (mega->ui)
        release_ui(mega->ui);
    DEBUG ///
    FREE(mega);
    DEBUG ///
    SDL_Quit(); /// Test
    return (isErr);
}
