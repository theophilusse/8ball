#include "HeightMap.h"

int        event_processing(t_grid *data, t_grid *mask, t_conf **config, SDL_Surface *editor, SDL_Surface *viewport, t_toolbar *up_bar, SDL_Cursor **cursor)
{
    SDL_Event event;

    if (!data || !config || !config[0] || !config[1] || !editor || !viewport || !up_bar)
        return (1);
    //if (SDL_PollEvent(&event))
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
            // exit if the window is closed
            case SDL_QUIT: return (1);

            // check for keypresses
            case SDL_KEYDOWN:
            {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return (1);

                if (event.key.keysym.sym == SDLK_KP1)
                    data->conf->dim[0] -= MOVE_HEIGHT;
                if (event.key.keysym.sym == SDLK_KP2)
                    data->conf->dim[0] += MOVE_HEIGHT;
                if (event.key.keysym.sym == SDLK_KP4)
                    data->conf->dim[1] -= MOVE_HEIGHT;
                if (event.key.keysym.sym == SDLK_KP5)
                    data->conf->dim[1] += MOVE_HEIGHT;
                if (data->persp == 1)
                {
                    data->conf->dim[0] = data->conf->dim[0] < 1.0 ? 1.0 : data->conf->dim[0]; // Super important
                    data->conf->dim[1] = data->conf->dim[1] < 1.0 ? 1.0 : data->conf->dim[1];
                }

                if (event.key.keysym.sym == SDLK_KP9) // Wheel Down doesn' work ; press 9
                {
                    data->conf->mouse_rad += 1;
                }
                if (event.key.keysym.sym == SDLK_KP6) // Wheel Up doesn' work ; press 6
                {
                    data->conf->mouse_rad -= 1;
                    if (data->conf->mouse_rad == 0)
                        data->conf->mouse_rad = 1;
                }

                if (event.key.keysym.sym == SDLK_KP7)
                    data->conf->height -= MOVE_HEIGHT;
                //data->height = data->height < 0 ? 1 : data->height;
                if (event.key.keysym.sym == SDLK_KP8)
                    data->conf->height += MOVE_HEIGHT;


                if (event.key.keysym.sym == SDLK_KP_PLUS)
                {
                    if (!data->persp)
                        data->conf->pxsz += 1;
                    else
                        data->conf->mouse_int++;
                }
                if (event.key.keysym.sym == SDLK_KP_MINUS)
                {
                    if (!data->persp)
                        data->conf->pxsz -= 1;
                    else
                        data->conf->mouse_int--;

                }
                data->conf->pxsz = data->conf->pxsz < 1 ? 1 : data->conf->pxsz;
                data->conf->mouse_int = data->conf->mouse_int < 1 ? 1 : data->conf->mouse_int;
                if (event.key.keysym.sym == SDLK_PAGEUP)
                    data->conf->f += MOVE_HEIGHT;
                if (event.key.keysym.sym == SDLK_PAGEDOWN)
                    data->conf->f = config[1]->f - MOVE_HEIGHT > 1.0 ? 1.0 : data->conf->f - MOVE_HEIGHT;

                if (event.key.keysym.sym == SDLK_UP)
                    data->conf->offset[1] += MOVE_DIR;
                if (event.key.keysym.sym == SDLK_DOWN)
                    data->conf->offset[1] -= MOVE_DIR;
                if (event.key.keysym.sym == SDLK_LEFT)
                    data->conf->offset[0] += MOVE_DIR;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    data->conf->offset[0] -= MOVE_DIR;

                /*
                if (event.key.keysym.sym == SDLK_UP)
                    config[data->persp]->offset[1] += MOVE_DIR;
                if (event.key.keysym.sym == SDLK_DOWN)
                    config[data->persp]->offset[1] -= MOVE_DIR;
                if (event.key.keysym.sym == SDLK_LEFT)
                    config[data->persp]->offset[0] += MOVE_DIR;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    config[data->persp]->offset[0] -= MOVE_DIR;
                */

                /*if (event.key.keysym.sym == SDLK_KP_ENTER)
                    data->conf->edit_mod = data->conf->edit_mod == 0 ? 1 : 0;*/

                if (event.key.keysym.sym == SDLK_TAB)
                {
                    //data->persp = data->persp >= 2 ? 0 : data->persp + 1; // Later
                    data->persp = data->persp == 0 ? 1 : 0;
                    data->conf = config[data->persp];
                }
                if (event.key.keysym.sym == SDLK_SPACE)
                    export_dxf(data, config[0]); // Export ISO config

                break;
            }
        } // end switch
        //if (data->persp)

        mouse_input_processing(data, editor, viewport, up_bar, config, cursor);
    } // end of message processing
    return (0);
}
