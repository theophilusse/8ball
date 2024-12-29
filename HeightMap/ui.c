#include "HeightMap.h"

static t_button            *make_button(int x, int y, int w, int h, uchar *color, int active, const char *picto, void (*ft)(void *), void *arg, char ptrtype)
{
    t_button        *b;

    if (!(b = (t_button *)malloc(sizeof(struct s_button))))
        return ((t_button *)NULL);

    if (!(b->s = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, w, h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000)))
    {
        printf("Unable to malloc surface: %s\n", SDL_GetError());
        return ((t_button *)NULL);
    }
    b->s->clip_rect.x = x;
    b->s->clip_rect.y = y;
    /*b->s->clip_rect.w = w;
    b->s->clip_rect.h = h;*/
    set_color4(b->color, color);
    b->active = active;
    b->state = BUTTON_IDLE;

    b->ptrtype = ptrtype; // Link function;
    b->arg = arg;
    b->ft_ptr = ft; // Link function;

    printf("Loading %s ...", picto);
    if (!(b->picto = SDL_LoadBMP(picto)))
        printf(" Error\n");
    else
        printf(" OK\n");
    return (b);
}

int                add_button(t_toolbar *bar, int x, int y, int w, int h, struct s_toolset tool)
{
    if (!bar)
        return (1);
    bar->n++;
    if (bar->n >= N_BUTTON)
        return (1);
    if (!(bar->btn[bar->n - 1] = make_button(x, y, w, h, (uchar *)tool.color, tool.active, tool.file, tool.ft, tool.arg, tool.ptrtype)))
        return (1);
    return (0);
}

t_toolbar           *make_toolbar(SDL_Surface *screen, int x, int y, int w, int h, uchar *color)
{
    t_toolbar       *bar;

    /*if (!screen || x < 0 || y < 0 || x >= screen->clip_rect.w || y >= screen->clip_rect.h || w >= screen->clip_rect.w || h >= screen->clip_rect.h)
        return (NULL);*/
    if (!(bar = (t_toolbar *)malloc(sizeof(struct s_toolbar))))
        return ((t_toolbar *)NULL);
    //if (!(bar->viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, w, h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff)))
    if (!(bar->viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, w, h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000)))
    {
        printf("Unable to malloc surface: %s\n", SDL_GetError());
        return ((t_toolbar *)NULL);
    }
    bar->viewport->clip_rect.x = x;
    bar->viewport->clip_rect.y = y;
    bar->viewport->clip_rect.w = w;
    bar->viewport->clip_rect.h = h;
    bar->n = 0;
    if (color)
    {
        bar->color[0] = color[0];
        bar->color[1] = color[1];
        bar->color[2] = color[2];
        bar->color[3] = 255;
        fill_surface(bar->viewport, bar->color);

        color[0] /= 2;
        color[1] /= 2; /// ???
        color[2] /= 2;
    }
    else
    {
        bar->color[0] = DEFAULT_BARBG_GRAY;
        bar->color[1] = DEFAULT_BARBG_GRAY;
        bar->color[2] = DEFAULT_BARBG_GRAY;
        bar->color[3] = 255;
        fill_surface(bar->viewport, bar->color);
    }
    return (bar);
}

int             init_toolbar(SDL_Surface *screen, int x, int y, int w, int h, uchar *color, t_toolbar **bar, t_toolset *ts)
{
    int         i, j;
    if (!bar)
        return (1);
    if (!(*bar = make_toolbar(screen, x, y, w, h, color)))
    {
        printf("make_toolbar Failed\n");
        return (1);
    }

    /** Misc **/
    i = -1;
    j = 10;
    while (++i < UPPER_BAR_N_PICTO)
    {
        if (add_button(*bar, j, 10, 30, 30, ts[i]))
        {
            printf("add_button Error\n");
            return (1);
        }
        if (i != 5)
            j += 40;
        else
            //j += (i == 3 ? upper_toolbar->w - (3 * 40) : 40);
            j += (i == 5 ? 460 : 40);
    }
    return (0);
}
