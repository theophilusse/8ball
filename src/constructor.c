#include "8ball.h"
/**
 ** Author : ttrossea
 ** constructor.c :
 ** Several boot functions.
 **
 ** Use mega_construct function to build the whole program.
 **
 ** - init_
 ** - input_manager_init
 ** - mega_construct
 **
**/

/**
 ** init_ :
 **
 ** Init Both SDL1.2 and Window.
 ** Return : screen
 ** Note : define FULLSCREEN_MOD macro to switch fullscreen
 **
**/
SDL_Surface          *init_(void)
{
    char        *env;

    if ((env = ft_strdup("SDL_VIDEO_WINDOW_POS=10,32")))
        putenv(env);
    if (env)
        FREE(env);

    AllocConsole();
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    /** initialize SDL video **/
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return (NULL);
    }

    /** make sure SDL cleans up before exit **/
    atexit(SDL_Quit);

    /** create a new window **/
    #ifdef FULLSCREEN_MOD
        SDL_Rect **modes;
        uint    maxres;
        int i;
        /* Get available fullscreen/hardware modes */
        maxres = 0;
        global_winx = 0;
        global_winy = 0;
        if (!(modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE)))
            return (NULL);
        for(i=0;modes[i];++i)
        {
            if (modes[i]->w * modes[i]->h > maxres)
            {
                global_winx = modes[i]->w;
                global_winy = modes[i]->h;
                maxres = (uint)(global_winx * global_winy);
            }
            FREE(modes[i]);
        }
        FREE(modes);
        if (maxres == 0)
            return (NULL);
        printf("Resolution [%d x %d]\n", global_winx, global_winy);
        SDL_Surface* screen = SDL_SetVideoMode(global_winx, global_winy, 16, SDL_FULLSCREEN); // Original
    #else
        /*SDL_Surface* screen = SDL_SetVideoMode(WINX, WINY, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);*/
        SDL_Surface* screen = SDL_SetVideoMode(WINX, WINY, 24, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
        /**SDL_Surface* screenVideo = SDL_SetVideoMode(WINX, WINY, 24, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
        SDL_Surface* screen = NULL;
        if (screenVideo)
        {
            screen = SDL_DisplayFormatAlpha(screenVideo);
            SDL_FreeSurface(screenVideo);
        }*/
        global_winx = WINX;
        global_winy = WINY;
    #endif
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return (NULL);
    }
    return (screen);
}

/**
 ** input_manager_init :
 ** Initialize input manager table.
 ** Return : 1 if error, 0 if OK.
 ** Input :
 **  - Takes address of manager (function pointer table)
 **  - Pointers buffer-size value (nf), use macro INPUT_MANAGER_FTSZ
**/
int intput_manager_init(int (**manager)(t_mega *, int), int nf)
{
    if (!manager)
        return (1);
    manager[USER_QUIT] = user_quit;
    manager[USER_RESIZE_WINDOW] = user_resizeWindow;
    manager[USER_SWITCH_MODEL_VIEW] = user_switchModelView;
    manager[USER_SWITCH_CLOUD_VIEW] = user_switchCloudView;
    manager[USER_KEY_UP] = user_keyup;
    manager[USER_KEY_DOWN] = user_keydown;
    manager[USER_MOUSE_BUTTON_UP] = user_mouseButtonUp;
    manager[USER_MOUSE_BUTTON_DOWN] = user_mouseButtonDown;
    manager[USER_MOUSE_MOTION] = user_mouseMotion;
    #ifdef COMPUTE_CLOUD_GPU
        manager[USER_COMPUTE_CLOUD] = user_computeCloud;
    #endif
    #ifdef COMPUTE_CLOUD_CPU
        manager[USER_COMPUTE_CLOUD] = user_computeCloud_CPU;
    #endif
    manager[USER_MOUSE_MOTION_CAMERA_DRAGPOS] = user_cameraDrag;
    manager[USER_MOUSE_MOTION_CAMERA_DRAGDIR] = user_cameraDragDir;
    manager[USER_MOUSE_MOTION_IDLE] = user_idle;
    manager[USER_CAMERA_ZOOM] = user_cameraZoom;
    manager[USER_ON_LEFT_CLICK] = user_onLeftClick;
    manager[USER_CANVA_CLICK] = user_canvaClick;
    manager[USER_INTERFACE_CLICK] = user_interfaceClick;
    manager[USER_MORPHO_CLICK] = user_morphoClick;
    /*manager[USER_MOUSE_MOTION_HUD] = user_mouseMotionHUD; /// Drag along axis
    manager[USER_MOUSE_MOTION_RADIUS_HUD] = user_mouseMotionRadiusHUD; /// Drag Length
    manager[USER_MOUSE_MOTION_ANGLE_HUD] = user_mouseMotionAngleHUD; /// Drag around axis*/
    return (0);
}

// Marker
///struct s_tool       build_toolset(int type, struct s_hud_arrow hud, t_vselection *select, const char *name)
int             build_toolset(t_mega *mega)
{
    uint            i;
    int             err;

    if (!mega)
        return (1);
    i = -1;
    while (++i < TOOLSET_SIZE)
        build_tool[i] = tool_buildIdle;
    build_tool[TOOLSET_NONE] = tool_buildIdle;
    build_tool[TOOLSET_SELECT] = tool_buildSelect;
    build_tool[TOOLSET_TRANSFORM] = tool_buildTransform;
    build_tool[TOOLSET_SCALE] = tool_buildScale;
    build_tool[TOOLSET_RESIZE] = tool_buildResize;
    build_tool[TOOLSET_ROTATE] = tool_buildRotate;

    mega->toolset_builder = build_tool;
    i = -1;
    while (++i < TOOLSET_SIZE)
    {
        mega->tool[i] = mega->toolset_builder[i](mega, &err);
        if (err == 1)
            return (1);
    }
    return (1);
}

/**
 ** opencl_build_data :
 ** Call every Mem object constructors.
 ** Init opencl memory
 ** Return 1 if failed, 0 if success.
 **
**/
int             opencl_build_data(t_mega *mega)
{
    if (!mega || !mega->stcl || !mega->picture || !mega->camera)
        return (1);
    DEBUG //
    if (init_clmem_option(mega->stcl))
    {
        printf("Init OpenCL option Buffer : ERROR.\n");
        return (1);
    }
    DEBUG //
    ///if (init_clmem_cloud_buffer(mega->stcl, mega->picture, 0))
    if (init_clmem_cloud_buffer(mega->stcl, mega->picture, 1))
    {
        printf("Init OpenCL cloud Buffer : ERROR.\n");
        return (1);
    }
    ///
    DEBUG //
    if (init_clmem_triangle(mega->camera->data, mega->stcl)) /// Bug crash
    {
        printf("Init OpenCL triangle Buffer : ERROR.\n");
        return (1);
    }
    ///
    if (init_clmem_picture(mega->stcl, mega->picture))
    {
        printf("Init OpenCL picture Buffer : ERROR.\n");
        return (1);
    }
    if (init_clmem(mega->camera, mega->sun, mega->picture, mega->stcl))
    {
        printf("Init OpenCL Buffers : ERROR.\n");
        return (1);
    }
    if (init_kernel_cloud_fall(mega->stcl))
    {
        printf("Init OpenCL cloud_fall Kernel : ERROR.\n");
        return (1);
    }
    if (init_kernel(mega->stcl))
    {
        printf("Init OpenCL Kernel : ERROR.\n");
        return (1);
    }
    return (0);
}

/**
 ** asset_load :
 ** Load 3d assets.
 **
**/
int             asset_load(t_camdata *data)
{
    //double       ppos[3];
    //double       rrot[3];
    //double       sscale[3];

    if (!data)
        return (1);
    ///return (0);
    //ppos[0] = -5;
    //ppos[1] = 0;
    //ppos[2] = 0;

    //rrot[0] = -35;
    //rrot[0] = 0;
    //rrot[1] = 180;
    //rrot[1] = 180;
    //rrot[1] = 0;
    //rrot[2] = 0;

    /*
    rrot[0] = 0;
    rrot[1] = 45;
    rrot[2] = 0;
    */

    /*sscale[0] = 0.5;struct s_select_node   *selectStack;
    sscale[1] = 0.5;
    sscale[2] = 0.5;*/

    //sscale[0] = 0.05;
    //sscale[1] = 0.05;
    //sscale[2] = 0.05;

    ///push_model(data, (uchar *)_blue_crystal, (double *)debug_v, (double *)debug_n, (int *)debug_f, NULL, NULL, NULL); /// Debug

    //push_model(data, (uchar *)_blue_crystal, (double *)bust_v, (double *)bust_n, (int *)bust_f, NULL, NULL, NULL/*rrot, sscale*/); /// Bust
    //push_model(data, (uchar *)_blue_crystal, (double *)bust_v, (double *)bust_n, (int *)bust_f, NULL, NULL, sscale/*rrot, sscale*/); /// Bust

    //push_model(data, (uchar *)_blue_crystal, (double *)bust_v, (double *)bust_n, (int *)bust_f, NULL, rrot, sscale/*rrot, sscale*/); /// Bust
    //push_model(data, (uchar *)_blue_crystal, (double *)bustHD_v, (double *)bustHD_n, (int *)bustHD_f, NULL, NULL, NULL); /// BustHD

    ///push_model(data, (uchar *)_blue_crystal, (double *)cube_v, (double *)cube_n, (int *)cube_f, NULL, NULL, NULL); /// Cube
    /*
        ppos[0] = 0;
        ppos[1] = -( 0.1 * (double)1 );
        ppos[2] = -( 0.1 * (double)1 );
    push_model(data, (uchar *)_blue_crystal, (double *)cube_v, (double *)cube_n, (int *)cube_f, ppos, NULL, NULL); /// Cube
    // debug
    uint i = -1;
    while (0 && ++i < 10)
    {
        ppos[0] = 0;
        ppos[1] = -( 0.1 * (double)i );
        ppos[2] = -( 0.1 * (double)i );
        push_model(data, (uchar *)_blue_crystal, (double *)cube_v, (double *)cube_n, (int *)cube_f, ppos, rrot, NULL); /// Cube
    }*/

    ///  push_model(data, (uchar *)_blue_crystal, (double *)cube_v, (double *)cube_n, (int *)cube_f, NULL, NULL, sscale/*rrot, sscale*/); /// Cube
    //push_model(data, (uchar *)_blue_crystal, (double *)cube_v, (double *)cube_n, (int *)cube_f, ppos, NULL, NULL/*rrot, sscale*/); /// Cube
    //push_model(data, (uchar *)_blue_crystal, (double *)strip_v, (double *)strip_n, (int *)strip_f, NULL /*ppos*/, NULL, NULL); /// Strip
    //push_model(data, (uchar *)_deep_red, (double *)strip_v, (double *)strip_n, (int *)strip_f, ppos, NULL, NULL); /// Strip
    ///push_model(data, (uchar *)_blue_crystal, (double *)mask_v, (double *)mask_n, (int *)mask_f, NULL, rrot, sscale); /// Monkey
    ///push_model(data, (uchar *)_blue_crystal, (double *)mask_v, (double *)mask_n, (int *)mask_f, NULL, NULL, NULL); /// Monkey
    ///push_model(data, (uchar *)_deep_red, (double *)miko_v, (double *)miko_n, (int *)miko_f, NULL, NULL, sscale); /// Miko
    ///push_model(data, (uchar *)_deep_red, (double *)putin_v, (double *)putin_n, (int *)putin_f, NULL, NULL, sscale); /// Miko
    //push_model(data, (uchar asset_load*)_deep_red, (double *)teapot_v, (double *)teapot_n, (int *)teapot_f, NULL, NULL, NULL); /// Teapot
    ///push_model(data, (uchar *)_deep_red, (double *)disc_v, (double *)disc_n, (int *)disc_f, NULL, NULL, NULL); /// Disc
    ///push_model(data, (uchar *)_deep_red, (double *)lol_v, (double *)lol_n, (int *)lol_f, NULL, NULL, NULL); /// Lol
    ///push_model(data, (uchar *)_deep_red, (double *)uvsphere_v, (double *)uvsphere_n, (int *)uvsphere_f, NULL, NULL, NULL); /// UVSphere
    ///push_model(data, (uchar *)_deep_red, (double *)teapot_v, (double *)teapot_n, (int *)teapot_f, NULL, NULL, NULL); /// Teapot
    ///  push_model(data, (uchar *)_deep_red, (double *)knight_v, (double *)knight_n, (int *)knight_f, NULL, rrot, NULL); /// Knight
    ///push_model(data, (uchar *)_deep_red, (double *)punk_v, (double *)punk_n, (int *)punk_f, NULL, rrot, NULL); /// Punk
    //push_model(data, (uchar *)_deep_red, (double *)carpet_v, (double *)carpet_n, (int *)carpet_f, ppos, rrot, NULL); /// Carpet
    //push_model(data, (uchar *)_deep_red, (double *)wave_v, (double *)wave_n, (int *)wave_f, NULL, rrot, NULL); /// Wave
    //push_model(data, (uchar *)_deep_red, (double *)debug_v, (double *)debug_n, (int *)debug_f, NULL, NULL, sscale); /// Debug


    ///procedural_grid(camera->data, (uchar *)_original_gray, (double *)wave_v, (double *)wave_n, (int *)wave_f, 4, sscale, 1, 1, 5, 0,0,0);
    ///procedural_grid(camera->data, (uchar *)_original_gray, (double *)cube_v, (double *)cube_n, (int *)cube_f, 4, sscale, 2, 2, 2, 0,0,0);
    ///procedural_grid(camera->data, (uchar *)_deep_red, (double *)teapot_v, (double *)teapot_n, (double *)teapot_f, 50, (double *)sscale, 2, 2, 2, 0,0,0);
    return (0);
}

static void                         filter_surface_alpha(SDL_Surface *out, SDL_Surface *in, uchar r, uchar g, uchar b)
{
    uchar           transparent[4];
    uchar           truecolor[4];
    int             h;
    int             w;
    int             i;
    int             j;
    uchar           *pixl;

    if (!out || !in)
        return ;
    transparent[3] = 0;
    truecolor[3] = 255;
    w = out->w;
    h = out->h;
    if (w != in->w || h != in->h)
    {
        printf("Morpho Assets Size doesn't match !!! (749x901)\n");
        return ;
    }
    j = -1;
    while (++j < h)
    {
        i = -1;
        while (++i < w)
        {

            if (!(pixl = (uchar *)getpixel_addr(in, i, j)))
                return ;
            truecolor[0] = pixl[2];
            truecolor[1] = pixl[1];
            truecolor[2] = pixl[0];
            if (*(pixl) == r && *(pixl + 1) == g && *(pixl + 2) == b)
                put_pixel(out, transparent, i, j);
            else
                put_pixel(out, truecolor, i, j);
        }
    }
}

static int                          make_morpho_part(t_morpho_group *part, char *filename, uint r, uint g, uint b, char *name, uint *pos, uint *dim)
{
    SDL_Surface             *surface;
    char                    full_path[512];

    if (!part || !name)
        return (1);
    part->surf = NULL;
    part->active = 0;
    part->pos[0] = 0;
    part->pos[1] = 0;
    part->dim[0] = 0;
    part->dim[1] = 0;
    part->color[0] = r;
    part->color[1] = g;
    part->color[2] = b;
    part->color[3] = 255;
    strncpy(part->name, name, 32);
    if (filename)
    {
        full_path[0] = '\0';
        strncpy(full_path, PATH_MORPHO, strlen(PATH_MORPHO));
        strncpy(full_path + (uint)strlen(PATH_MORPHO), filename, strlen(filename));
        full_path[strlen(PATH_MORPHO) + strlen(filename)] = '\0';
        printf("Loading : [%s]\n", full_path);
        //if (!(part->surf = SDL_LoadBMP(full_path)))
        if (!(surface = SDL_LoadBMP(full_path)))
            return (1);
        /** if (!(part->surf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask))) **/
        /**if (!(part->surf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, surface->w, surface->h, 32, rmask, gmask, bmask, amask)))**/
        if (!(part->surf = new_surface32(surface->w, surface->h)))
        {
            SDL_FreeSurface(surface);
            return (1);
        }
        filter_surface_alpha(part->surf, surface, 255, 255, 255);
        SDL_FreeSurface(surface);
    }
    else
    {
        if (!pos || !dim)
            return (1);
        part->pos[0] = pos[0];
        part->pos[1] = pos[1];
        part->dim[0] = dim[0];
        part->dim[1] = dim[1];
    }
    return (0);
}

static struct s_morpho              build_morpho(SDL_Surface *screen, uint *err)
{
    uint                        i;
    uint                        pos[2];
    uint                        dim[2];
    SDL_Surface                 *tmp;
    struct s_morpho             morpho;

    if (err)
        *err = 0;
    morpho.active = 0;
    morpho.pos[0] = 0;
    morpho.pos[1] = 0;
    morpho.surface = NULL;
    if (!screen)
    {
        if (err)
            *err = 1;
        return (morpho);
    }
    i = -1;
    while (++i < 44)
    {
        morpho.part[i].surf = NULL;
        morpho.part[i].name[0] = '\0';
    }

    if (!(tmp = SDL_LoadBMP(PATH_MORPHO_00)))
    {
        if (err)
            *err = 1;
        return (morpho);
    }
    if (screen->w < tmp->w || screen->h < tmp->h)
        morpho.active = -1;
    else
    {
        morpho.pos[0] = screen->w - tmp->w;
        morpho.pos[1] = screen->h - tmp->h;
    }
    morpho.surface = tmp;
    i = -1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Al.bmp", 230, 126, 48, "Crane G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Ar.bmp", 230, 126, 48, "Crane D", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Bl.bmp", 136, 66, 29, "Arcade G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Br.bmp", 136, 66, 29, "Arcade D", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Cl.bmp", 121, 248, 248, "Peaupiere G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Cr.bmp", 121, 248, 248, "Peaupiere D", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Dl.bmp", 167, 103, 38, "Tempe G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Dr.bmp", 167, 103, 38, "Temps D", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_El.bmp", 130, 196, 108, "Oeil G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Er.bmp", 130, 196, 108, "Oeil D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Fl.bmp", 145, 40, 59, "Oreille G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Fr.bmp", 145, 40, 59, "Oreille D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Gl.bmp", 240, 195, 0, "Cerne G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Gr.bmp", 240, 195, 0, "Cerne D", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Hl.bmp", 136, 77, 167, "Paumette G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Hr.bmp", 136, 77, 167, "Paumette D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Il.bmp", 48, 48, 48, "Nez G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Ir.bmp", 48, 48, 48, "Nez D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Jl.bmp", 173, 79, 9, "Naseau G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Jr.bmp", 173, 79, 9, "Naseau D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Kl.bmp", 0, 0, 0, "Joue G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Kr.bmp", 0, 0, 0, "Joue D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Ll.bmp", 55, 0, 40, "Moustache G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Lr.bmp", 55, 0, 40, "Moustache D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Ml.bmp", 157, 62, 12, "Bajoue G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Mr.bmp", 157, 62, 12, "Bajoue D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Nl.bmp", 255, 203, 96, "Machoire G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Nr.bmp", 255, 203, 96, "Machoire D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Ol.bmp", 86, 130, 3, "Trapeze G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Or.bmp", 86, 130, 3, "Trapeze D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Pl.bmp", 0, 127, 255, "Clavicule G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Pr.bmp", 0, 127, 255, "Clavicule D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Ql.bmp", 174, 100, 45, "Cou G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Qr.bmp", 174, 100, 45, "Cou D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Rl.bmp", 139, 108, 66, "Eins G", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Rr.bmp", 139, 108, 66, "Eins D", NULL, NULL))
        if (err)
            *err = 1;

    if (make_morpho_part(&morpho.part[++i], "base_morpho_Sc.bmp", 240, 227, 107, "Levre inf.", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Tc.bmp", 118, 111, 100, "Levre sup.", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Uc.bmp", 255, 228, 196, "Sternum", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Vc.bmp", 133, 109, 77, "Gorge", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Wc.bmp", 78, 61, 40, "Menton", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Xc.bmp", 254, 254, 226, "???", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Yc.bmp", 244, 254, 254, "Pif", NULL, NULL))
        if (err)
            *err = 1;
    if (make_morpho_part(&morpho.part[++i], "base_morpho_Zc.bmp", 232, 214, 48, "???Truc", NULL, NULL))
        if (err)
            *err = 1;
    dim[0] = 42;
    dim[1] = 42;
    pos[0] = 9;
    pos[1] = 63;
    if (make_morpho_part(&morpho.part[++i], NULL, 58, 142, 186, "Globe G", pos, dim))
        if (err)
            *err = 1;
    pos[0] = 9;
    pos[1] = 117;
    if (make_morpho_part(&morpho.part[++i], NULL, 84, 114, 174, "Globe D", pos, dim))
        if (err)
            *err = 1;
    pos[0] = 9;
    pos[1] = 170;
    if (make_morpho_part(&morpho.part[++i], NULL, 84, 114, 0, "Dentition", pos, dim))
        if (err)
            *err = 1;

    pos[0] = 9;
    pos[1] = 8;
    if (make_morpho_part(&morpho.part[++i], NULL, 0, 50, 0, "Quit!", pos, dim))
        if (err)
            *err = 1;

    /*typedef struct s_morpho_group
    {
        SDL_Surface         *surf;
        uchar               color[4];
        char                name[32];
    }               t_morpho_group;*/
    /*
    typedef struct s_moprho
    {
        SDL_Surface             *surface;
        uint                    pos[2];
        struct s_morpho_group   part[26];
        ///t_morpho_node   *root;
    }               t_morpho;
    */
    return (morpho);
}

static t_userInterface             *build_ui(t_mega *mega)
{
    uint                        i;
    uint                        j;
    t_userInterface             *ui;


    if (!mega)
        return (NULL);
    if (!(ui = (t_userInterface *)ALLOC(sizeof(struct s_userInterface))))
        return (NULL);
    /// ************************* ///
    /*
        char            path[STRING_SIZE * 8];
        char            uiCross[] = "kill.bmp";

        path[0] = '\0';
        strncpy(path, UI_ASSET_PATH, (uint)strlen(UI_ASSET_PATH));
        strncpy(path + (uint)strlen(UI_ASSET_PATH), uiCross, strlen(uiCross));
        printf("UI: Loading [%s]\n", path);
    */
    /*
        if (!(ui->spKill = SDL_LoadBMP(path)))
        {
            printf("build_ui failed : Can't open [%s]\n", path);
            if (ui)
                FREE(ui);
            return (NULL);
        }
    */
    /**
        i = -1;
        while (++i < TOTAL_DATATYPE_COUNT)
        {
            j = -1;
            while (++j < TOTAL_INSTRUCTION_COUNT)
                instructionTable[i][j] = ;
        }
    */
    ///instructionTable[0][0] = ;

    printf("UI @ %p\n", ui);
    memset(ui, 0, sizeof(struct s_userInterface));
    ui->sigFrame = 0;
    ui->font.charset = NULL;
    ui->font_bis.charset = NULL;
    ui->font = ui_newFont((uchar *)_orange, (uchar *)_gray_gray, 1.0);
    if (!(ui->font.charset))
    {
        FREE(ui);
        return (NULL);
    }
    ui->font_bis = ui_newFont((uchar *)_blue_crystal, (uchar *)_blue_night, 1.0);
    if (!(ui->font_bis.charset))
    {
        ui_releaseFont(&ui->font);
        FREE(ui);
        return (NULL);
    }
    if (ui_initAssets(ui))
    {
        FREE(ui);
        return (NULL);
    }
    /// Init Cursors ///
    if (ui_initCursor(ui))
        printf("ui_initCursor: Error.\n");
    /// Init Cursors ///
    /// ************************* ///
    i = -1;
    DEBUG //
    while (++i < UI_BOX_COUNT)
        ui->box[i].content = NULL;//
    DEBUG //
    ui->active = 1;
    ui->event = ui_setDefaultEvent();
    ui->sigRefresh = 0;
    ui->morpho = build_morpho(mega->screen, &i);

    if (i == 1) /*** ERROR LOADING ASSETS ***/
    {
        printf("Error loading assets\n");
        if (ui->morpho.surface)
        {
            SDL_FreeSurface(ui->morpho.surface);
            ui->morpho.surface = NULL;
        }
        i = -1;
        while (++i < 44)
            if (ui->morpho.part[i].surf)
            {
                SDL_FreeSurface(ui->morpho.part[i].surf);
                ui->morpho.part[i].surf = NULL;
            }
        FREE(ui);
        return (NULL);
    }
    i = -1;
    while (++i < UI_BOX_COUNT)
        if (set_default_box(&ui->box[i]))
        {
            printf("Error allocating memory\n");
            i = -1;
            while (++i < 8)
                ui_releaseBox(&ui->box[i]); ///
            if (ui->morpho.surface)
            {
                SDL_FreeSurface(ui->morpho.surface);
                ui->morpho.surface = NULL;
            }
            i = -1;
            while (++i < 44)
                if (ui->morpho.part[i].surf)
                {
                    SDL_FreeSurface(ui->morpho.part[i].surf);
                    ui->morpho.part[i].surf = NULL;
                }
            FREE(ui);
            return (NULL);
        }
    return (ui);
}

/**
 ** mega_construct :
 ** Boot function.
 ** Start all program component.
 ** Return : pointer to mega structure or NULL if error.
 ** Input :
 ** - RGBA mask
 ** - User's picture file input (filename)
 **
**/
t_mega      *mega_construct(Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask, const char *picture_filename)
{
    t_mega                *mega;
    struct s_opencl       stcl;
    int err;

    if (!(mega = (t_mega *)ALLOC(sizeof(struct s_mega))))
        return (NULL);

    mega->screen = NULL;
    mega->viewport = NULL;
    mega->work_viewport = NULL;
    mega->hud_viewport = NULL;
    mega->log_viewport = NULL;
    mega->ui_viewport = NULL;
    mega->direct_viewport = NULL;
    mega->viewport_swp = NULL;
    mega->picture = NULL;
    mega->camera = NULL;
    mega->stcl = NULL;
    mega->ui = NULL;
    mega->timeMachine = NULL;

    mega->sun[0] = 15;
    mega->sun[1] = 15;
    mega->sun[2] = 15;
    mega->keyboardUp = 1;
    mega->mouse.skipDrag = 1;
    mega->mouse.mouseRle[0] = 0;
    mega->mouse.mouseRle[1] = 0;
    mega->mouse.motion_ft = USER_MOUSE_MOTION_IDLE;
    mega->mouse.mouseButtonUp = 1;
    mega->mouse.leftButton = 0;
    mega->mouse.draw_marker = 0;
    mega->mouse.MouseSensitiv = 0;

    mega->mouse.MouseSensitiv = 0;
    mega->selectStack = NULL;

    if (!(mega->screen = init_()))
    {
        DEBUG ///
        FREE(mega);
        return (NULL);
    }
    printf("new viewport\n");
    ///if (!(mega->viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask)))
    if (!(mega->viewport = new_surface32(mega->screen->w, mega->screen->h)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("new work viewport\n");
    ///if (!(mega->work_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask)))
    if (!(mega->work_viewport = new_surface32(mega->screen->w, mega->screen->h)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("new hud viewport\n");
    ///if (!(mega->hud_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask)))
    if (!(mega->hud_viewport = new_surface32(mega->screen->w, mega->screen->h)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("new log viewport\n");
    ///if (!(mega->log_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask)))
    if (!(mega->log_viewport = new_surface32(mega->screen->w, mega->screen->h)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("new ui viewport\n");
    ///if (!(mega->ui_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask)))
    if (!(mega->ui_viewport = new_surface32(mega->screen->w, mega->screen->h)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("new direct viewport\n");
    ///if (!(mega->direct_viewport = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask)))
    if (!(mega->direct_viewport = new_surface32(mega->screen->w, mega->screen->h)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("new viewport swp\n");
    ///if (!(mega->viewport_swp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, mega->screen->w, mega->screen->h, 32, rmask, gmask, bmask, amask)))
    if (!(mega->viewport_swp = new_surface32(mega->screen->w, mega->screen->h)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("new camera\n");
    if (!(mega->camera = new_camera(mega->screen, rmask, gmask, bmask, amask)))
    {
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("load %s\n", picture_filename);
    /// LoadCharset here before moving to build_ui() -> ui_newCharset.c
    if (!(mega->picture = SDL_LoadBMP(picture_filename)))
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        root_destructor(mega, 1);
        return (NULL);
    }
    printf("asset load\n");
    if (asset_load(mega->camera->data))
    {
        printf("OpenCL Build Data : ERROR.\n");
        root_destructor(mega, 1);
        return (NULL);
    }

    printf("new input manager\n");
    //int (*input_manager_[INPUT_MANAGER_FTSZ])(t_mega *, int); /// Verify syntax array[]
    if (!(mega->input_manager = ALLOC(sizeof(int (*)(t_mega *, int)) * INPUT_MANAGER_FTSZ))) /// DEBUG ALLOC
        return (NULL); /** Static table **/
    intput_manager_init(mega->input_manager, INPUT_MANAGER_FTSZ);
    /**toolset_init(mega->toolset, TOOLSET_SIZE);**/

    printf("new toolset\n");
    ///mega->currentTool = TOOLSET_NONE;
    mega->currentTool = TOOLSET_TRANSFORM;
    //mega->currentTool = TOOLSET_SCALE;
    build_toolset(mega);

    printf("new OpenCL\n");
    stcl = init_opencl(&err);
    if (err || !(mega->stcl = (t_opencl *)ALLOC(sizeof(struct s_opencl))))
    {
        printf("Init OpenCL : ERROR.\n");
        root_destructor(mega, 1);
        return (NULL);
    }
    *mega->stcl = stcl;
    DEBUG ///
    printf("set data OpenCL\n");
    if (opencl_build_data(mega))
    {
        printf("OpenCL Build Data : ERROR.\n");
        /// TODO
        //root_destructor(mega, 1);
        //return (NULL);
    }

    /** DeadCode **/
    /*
        return (memMgr_release());
    */
    /** DeadCode **/

    printf("new UI\n");
    /*** BUILD UI ***/
    if (!(mega->ui = build_ui(mega)))
    {
        printf("Build UI failed\n");
        return (NULL);
    }
    /*** BUILD WINDOWS ***/
    printf("set UI\n");
    uint        i;
    i = -1;
    while (++i < UI_BOX_COUNT)
        ui_newBox(mega, &mega->ui->box[i], i);
    mega->ui->boxCount = ui_totalBox(mega->ui);
    DEBUG //
    ///ui_swapBox(mega->ui, 0, 1);
    DEBUG //
    /*** BUILD HISTORY ***/
    printf("new historic\n");
    if (!(mega->timeMachine = history_new()))
    {
        printf("Build TimeMachine failed\n");
        return (NULL);
    }
    mega->timeMachine->param.type = HISTORY_RELINK_SELECTION;
    return (mega);
}
