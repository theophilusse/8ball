#include "sdl_util.h"

void                toggleFullscreen(t_mega *mega)
{
    int         err;

	if (!mega)
		return ;
	if (!SDL_WM_ToggleFullScreen(mega->screen))
        printf("Can't toggle fullscreen mode.\n");
	printf("Toggle fullscreen mode.\n");
}
