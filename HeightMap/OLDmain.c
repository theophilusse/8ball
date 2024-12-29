#include "HeightMap.h"

Uint32          rmask, gmask, bmask, amask;

static struct s_toolset upper_toolbar_btnset[UPPER_BAR_N_PICTO] = {
    {
        "rc/tool_add.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        btn_square_add, // Edit mode 1
    },
    {
        "rc/square_add_grad.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        btn_square_add_grad, // Edit Mode 2
    },
    {
        //"rc/render_wireframe.bmp",
        "rc/tool_erase.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        btn_square_del, // Edit mode 0
    },
    {
        "rc/render_dot.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        btn_render_cloud,
    },
    {
        "rc/render_wireframe.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        btn_render_wireframe,
    },
    {
        "rc/render_polygon.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        btn_render_polygon,
    },
    {
        "rc/separator.bmp",
        BUTTON_INACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        NULL,
    },
    {
        "rc/grid.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        NULL,
    },
    {
        "rc/help.bmp",
        BUTTON_ACTIVE,
        NULL, // Toto
        BUTTON_IDLE,
        PTYPE_FT,
        NULL, // Todo
        NULL
    }
};

static void         endian(void)
{
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    }
    else
    {
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    }
}

static void _colorset
    (   uchar *color4,
        uchar *black,
        uchar *red,
        uchar *transp,
        uchar *green,
        uchar *button_color
    )
{
    int             i;

    color4[0] = DEFAULT_R;
    color4[1] = DEFAULT_G;
    color4[2] = DEFAULT_B;
    color4[3] = DEFAULT_A;
    green[0] = DEFAULT_R;
    green[1] = DEFAULT_G;
    green[2] = DEFAULT_B;
    green[3] = DEFAULT_A;
    transp[0] = 0;
    transp[1] = 0;
    transp[2] = 0;
    transp[3] = 0;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;
    black[3] = 255;
    red[0] = 255;
    red[1] = 0;
    red[2] = 0;
    red[3] = 255;
    button_color[0] = DEFAULT_BTNBG_GRAY;
    button_color[1] = DEFAULT_BTNBG_GRAY;
    button_color[2] = DEFAULT_BTNBG_GRAY;
    button_color[3] = 255;
    i = -1;
    while (++i < UPPER_BAR_N_PICTO)
    {
        upper_toolbar_btnset[i].color = button_color;
        if (upper_toolbar_btnset[i].active == BUTTON_INACTIVE)
            upper_toolbar_btnset[i].color = transp;
    }
}

void        load_interface(t_toolset *upper_toolbar_btnset, t_conf **conf)
{
    int             i;

    i = -1;
    while (++i < UPPER_BAR_N_PICTO)
    {
        if (i == 0 || i == 1 || i == 2)
            upper_toolbar_btnset[i].arg = conf[1];
        if (i == 3 || i == 4 || i == 5)
            upper_toolbar_btnset[i].arg = conf[0];
    }
}

int main ( int argc, char** argv )
{
    /* int             i, j; */
    /* t_conf              *config[2]; */
    t_conf              *config[3];
    SDL_Cursor          *cursor[N_CURSOR];
    SDL_Surface         *screen;
    SDL_Surface         *background;
    SDL_Surface         *viewport;
    SDL_Surface         *editor;
    t_toolbar           *upper_toolbar;

    //SDL_Surface     *textSurface;
    uchar           color4[4];
    uchar           black[4];
    uchar           red[4];
    uchar           transp[4];
    uchar           green[4];
    uchar           button_color[4];

    endian();
    _colorset
    (
        (uchar *)color4,
        (uchar *)black,
        (uchar *)red,
        (uchar *)transp,
        (uchar *)green,
        (uchar *)button_color
    );

    // initialize SDL video
    if (SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    /*if (TTF_Init() == -1)
    {
        printf( "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }*/
    if (init_cursor((SDL_Cursor **)&cursor))
        return (1);

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 32,
                                    SDL_HWSURFACE|SDL_DOUBLEBUF);
                                    //SDL_HWSURFACE|SDL_DOUBLEBUF); // Original
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    //bmp = SDL_LoadBMP("grid.bmp");
    background = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, screen->w, screen->h, 32, rmask, gmask, bmask, amask);
    if (!background)
    {
        printf("Unable to malloc surface: %s\n", SDL_GetError());
        return 1;
    }

    //viewport = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32, rmask, gmask, bmask, amask);
    viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, (screen->w / 3) * 2, screen->h - 47, 32, rmask, gmask, bmask, amask);
    if ( !viewport )
    {
        printf("SDL_CreateRGBSurface Failed: %s\n", SDL_GetError());
        return 1;
    }
    editor = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, (screen->w / 3), screen->h - 47, 32, rmask, gmask, bmask, amask);
    if ( !viewport )
    {
        printf("SDL_CreateRGBSurface Failed: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    editor->clip_rect.x = (screen->w / 3) * 2;
    editor->clip_rect.y = 47;

    viewport->clip_rect.x = 0;
    viewport->clip_rect.y = 47;
    viewport->clip_rect.w = (screen->w / 3) * 2;
    viewport->clip_rect.h = screen->h - 47;

    background->clip_rect.x = (screen->w - background->w) / 2;
    background->clip_rect.y = (screen->h - background->h) / 2;

    /*TTF_Font* font = TTF_OpenFont("ARIAL.TTF", size);
    SDL_Color foregroundColor = { 255, 255, 255 };
    SDL_Color backgroundColor = { 0, 0, 0 };
    SDL_Rect textLocation = { (Sint16)(screen->w / 2), (Sint16)(screen->h / 2), 0, 0 };
    //textSurface = TTF_RenderText_Shaded(font, "Test", foregroundColor, backgroundColor);
    textSurface = TTF_RenderText_Shaded(NULL, "Test", foregroundColor, backgroundColor);*/


    t_grid          *data;
    t_grid          *mask;
    SDL_Surface     *img;
    SDL_Surface     *msk;
    //if (!(data = get_grid("input.bmp", &img)) ||
    if (!(data = get_grid("input.bmp", &img)) || !(mask = get_grid("rc/_MASK_.bmp", &msk)) || //
        !(config[0] = make_conf()) ||
        !(config[1] = make_conf()) ||
        !(config[2] = make_conf()))
    {
        printf("get_grid Failed\n");
        return (1);
    }
    if (img)
        SDL_FreeSurface(img);
    if (msk)
        SDL_FreeSurface(msk);
    data->conf = config[0];
    config[1]->dim[0] = 1; // Editor : Picture
    config[1]->dim[1] = 1;

    config[2]->dim[0] = 1; // Editor : Static Mask
    config[2]->dim[1] = 1;
    //config[1]->offset[]

    load_interface((t_toolset *)upper_toolbar_btnset, config);
    init_toolbar(screen, 0, 16, screen->w, 47, NULL, &upper_toolbar, (t_toolset *)upper_toolbar_btnset);
    // program main loop
    int done = 0;
    while (!done)
    {
        // message processing loop

        // DRAWING STARTS HERE
                // clear screen
        //if (data->persp)


        //SDL_BlitSurface(viewport, 0, screen, &viewport->clip_rect);

        fill_surface(viewport, (uchar *)black);
        //fill_surface(viewport, (uchar *)transp);
        fill_surface(editor, (uchar *)transp);
        //SDL_FillRect(viewport, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        /* SDL_Surface* screen */
        draw_background(background);
        draw_viewport(data, mask, config[0], viewport, (uchar *)&green);
        /*if (data->persp == 1)*/
            //draw_mask(data, config[1], editor, (uchar *)&color4);
            draw_mask(mask, config[2], editor, (uchar *)&color4);
        draw_heightmap(data, mask, config[1], editor, (uchar *)&color4);
        draw_toolbar(upper_toolbar);

        done = event_processing(data, mask, config, editor, viewport, upper_toolbar, (SDL_Cursor **)cursor);

        // draw bitmap
        SDL_BlitSurface(background, 0, screen, &background->clip_rect);
        //SDL_BlitSurface(screen, 0, screen, &screen->clip_rect);
        draw_line(viewport, (uchar *)red, viewport->clip_rect.w - 1, 0, viewport->clip_rect.w - 1, viewport->clip_rect.h - 1);
        draw_line(viewport, (uchar *)red, viewport->clip_rect.w - 2, 0, viewport->clip_rect.w - 2, viewport->clip_rect.h - 1);
        SDL_BlitSurface(editor, 0, screen, &editor->clip_rect);
        SDL_BlitSurface(viewport, 0, screen, &viewport->clip_rect);
        SDL_BlitSurface(upper_toolbar->viewport, 0, screen, &upper_toolbar->viewport->clip_rect);
        //SDL_BlitSurface(textSurface, NULL, screen, &textLocation);// Testing text

        //printf("EDITOR TOOL : %d\n", config[1]->edit_mod);
        // DRAWING ENDS HERE

        // finally, update the screen :)

        //draw_cloud(data, config[0], viewport, (uchar *)&green);////
        ///SDL_FillRect(viewport, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        //SDL_FillRect(viewport, &viewport->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
        //SDL_FillRect(viewport, &viewport->clip_rect, SDL_MapRGB(viewport->format, 0, 0, 0));

        SDL_Flip(screen);
    } // end main loop
    SDL_FreeSurface(background);
    //TTF_Quit();

    free(data->ptr);
    free(data);
    SDL_FreeCursor(cursor[0]);
    SDL_FreeCursor(cursor[1]);
    //printf("Exited cleanly\n");
    return 0;
}
