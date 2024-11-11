#include "sdl_util.h"

/**
 ** Halt program.
*/
void        halt_program(uchar *refresh, void *mega)
{
    SDL_Event       waitForInput;

    while (SDL_WaitEvent(&waitForInput))
    {
        ///printf("TYPE [%u]\n", waitForInput.motion.type); ///
        if (waitForInput.motion.type == SDL_MOUSEMOTION)
        {
            DEBUG ///
            *refresh = 1;
            return ;
        }
        /**
            if (waitForInput.motion.type == SDL_VIDEORESIZE)
            {
                user_resizeWindow((t_mega *)mega, 0);
            }
        */
    }
}
