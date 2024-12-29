#include "8ball.h"
#include "model.h"
#include "alphabet_tileset.h"
#include "frame.h"

//Uint32          rmask, gmask, bmask, amask;
//void            *global_mega;

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

void        procedural_grid(t_camdata *d, uchar *amb_color, double *model_v, double *model_n, int *model_f, double space, double *scale, int x, int y, int z, double posX, double posY, double posZ)
{
    int       dim[3] = { x, y, z };
    int       i;
    int       j;
    int       k;
    double       pos[3];

    if (!d)
        return ;
    ///space = 4; // ?
    i = -1;
    while (++i < dim[0])
    {
        j = -1;
        while (++j < dim[1])
        {
            k = -1;
            while (++k < dim[2])
            {
                pos[0] = posX + ((i * space) - ((space * dim[0]) / 2));
                pos[1] = posY + ((j * space) - ((space * dim[1]) / 2));
                pos[2] = posZ + ((k * space) - ((space * dim[2]) / 2));
                push_model(d, (uchar *)amb_color, (double *)model_v, (double *)model_n, (int *)model_f, pos, NULL, scale);
            }
        }
    }
}

/**
void            draw_HUD_axis(SDL_Surface *s, uchar *color, double *axis, int w, int h, int x, int y, int size) /// !!! NOT USED !!!
{
    int     size_2;
    int     rx;
    int     ry;

    size_2 = size / 2;
    rx = x;
    ry = y;
    //rx += (axis[2] * (20 * w)) + axis[0] * (20 * w);
    //ry += (axis[0] * (20 * w)) - ((double)axis[1] * 0.5 + axis[2] * (20 * w));
    rx += (axis[0] * size) + (axis[2] * size_2);
    ry -= (axis[1] * size) - (axis[2] * size_2);// + axis[2] * (20 * w));

    draw_line_width(s, color, x, y, rx, ry, 3);
}
**/

static char *getArgv(const char *argv)
{
    char *ptr;

    if (!(ptr = (char *)argv))
        return (NULL);
    while (*ptr != '\0')
        ptr++;
    ptr--;
    while (*ptr != '\\' && ptr != argv) /// Windows Path.
        ptr--;
    return (ptr + (*ptr == '\\' ? 1 : 0));
}

int main ( int argc, char** argv )
{
    int                     err;
    t_mega                  *mega;
    struct s_globalVars     global_variables;

    endian();

    /** memMgr Test **/
    /*
    if (memMgr_init())
        return (1);
    DEBUG ///
    void    *ptrs[1500];
    uint _i = -1;
    uint _j = -1;
    while (++_i < 1000)
    {
        if (!(ptrs[_i] = ALLOC(_i + 1)))
            return (printf("ERROR i:%u\n", _i));
        _j = -1;
        while (++_j < 500)
            if (!(ptrs[_j + 1000] = ALLOC(_j + 1)))
                return (printf("ERROR i:%u j:%u\n", _i, _j));
        while (--_j != UINT_MAX)
            FREE(ptrs[_j + 1000]);
    }
    void        *datC = ptrs[5];
    t_memCell *cell;
    t_memPage *page;
    if (!(cell = mem_getDataCell(datC)))
        return (printf("getCell error\n"));
    if (!(page = mem_getCellPage(cell)))
        return (printf("getPage error\n"));
    mem_display();
    printf("n_mem_pages : [%u]\n", mem_pageCount(NULL));
    while (_i--)
        FREE(ptrs[_i]);
    return (42);*/
    /** memMgr Test **/

    printf("memMgr_init Mega_construct\n");
    if (
    #ifdef CUSTOM_ALLOC
        memMgr_init() ||
    #endif
        !(mega = mega_construct(rmask, gmask, bmask, amask, "input.bmp")))
        return (1);

    ///printf("ponc space @ %p\n", charset_ponc_space);
    ///charset_print(mega->screen, mega->ui->font.charset, 0, 0, "          TEST");
    printf("PIXELS SPACE : %p\n", mega->ui->font.charset[32]->pixels);
    printf("Mouse caption\n");
    memset((void *)global_variables.mouseCaption, 0, sizeof(char) * STRING_SIZE);
    strcat(global_variables.mouseCaption, "Test Caption (main.c)"); ///
    global_variables.videoInfo = SDL_GetVideoInfo();
    global_variables.wTitle = getArgv(argv[0]);
    SDL_WM_SetCaption(global_variables.wTitle, NULL); /// Title.
    global_variables.window = FindWindowA(NULL, global_variables.wTitle);
    mega->global = &global_variables;
    printf("DEBUG CAPTION : [%s]\n", global_variables.mouseCaption); ///
    printf("DEBUG CAPTION : [%s]\n", mega->global->mouseCaption); ///
    printf("Load bitmap\n");
    global_mega = (void *)mega;
    SDL_Surface* tmp = SDL_LoadBMP("rc/nagscreen.bmp");
    SDL_Surface* bmp;
    if (!tmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return (1);
    }
    bmp = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);
    SDL_WM_SetIcon(bmp, NULL); /// Icon.
    /** toggleFullscreen(mega); **/

    /*** NagScreen ***/
    /*set_alpha(mega->viewport_swp, SDL_ALPHA_TRANSPARENT);*/
    SDL_FillRect(mega->viewport_swp, 0, SDL_MapRGB(mega->viewport_swp->format, 0, 64, 0));
    SDL_FillRect(mega->viewport, 0, SDL_MapRGB(mega->viewport_swp->format, 0, 64, 0));

    blit_at(bmp, mega->viewport, (mega->viewport->w / 2) - (bmp->w / 2), (mega->viewport->h / 2) - (bmp->h / 2));
    blit(mega->viewport, mega->screen);
    SDL_Flip(mega->screen);

    //
    SDL_FreeSurface(bmp);
    bmp = NULL;

    /*** NagScreen ***/
    if (0 && mega->input_manager[USER_COMPUTE_CLOUD](mega, 0))
    {
        printf("user_computeCloud failed\n");
        root_destructor(mega, 1);
        return (1);
    }

    /** LOL **/
    /*
        //SDL_CDStatus()
        SDL_CD      *cd;
        int cdtest = -1;
        while (++cdtest < 10)
        {
            cd = SDL_CDOpen(cdtest);
            SDL_CDEject(cd);
        }
    */
    /** LOL **/

    /*** START ***/
    ///charset_print(mega->viewport, mega->ui->font.charset,
    charset_print_noAlpha(mega->viewport, mega->ui->font.charset,
                  (mega->viewport->w / 2) - (8*16),
                  mega->viewport->h - (mega->viewport->h / 10),
                  "~ Press Any key ~");
    printf("Viewport : [%p] ;; viewport_swp : [%p]\n", mega->viewport, mega->viewport_swp); ///

    copy_surface(mega->viewport, mega->viewport_swp, "012", "012");
    blit(mega->viewport, mega->screen);
    SDL_Flip(mega->screen);
    // program main loop

    printf("Entering Main Loop\n");
    // free mega struct when mainLoop finish
    err = inputManager_loop(mega, rmask, gmask, bmask, amask);
    root_destructor(mega, err);
    printf("Exited cleanly\n");
    DEBUG_TODO ///
    return (0);
}
