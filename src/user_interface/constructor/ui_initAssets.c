#include "user_interface.h"

struct s_ui_assets          ui_setDefaultAssets(void)
{
    struct s_ui_assets      assets;

    assets.arrow_d = NULL;
    assets.arrow_u = NULL;
    assets.arrow_l = NULL;
    assets.arrow_r = NULL;
    assets.button_off = NULL;
    assets.button_on = NULL;
    assets.grid = NULL;
    assets.scroller = NULL;
    assets.cross = NULL;
    assets.spKill = NULL;
    assets.fall = NULL;
    assets.save = NULL;
    assets.azerty = NULL;
    assets.bye = NULL;
    return (assets);
}

static SDL_Surface              *ui_loadAsset(const char *path, uchar filterWhite)
{
    SDL_Surface *swap;
    SDL_Surface *alphaSurf;
    SDL_Surface *ret;

    ret = NULL;
    if (!path)
        return (NULL);
    if (!(swap = SDL_LoadBMP(path)))
        return (NULL);
    if (!(alphaSurf = new_surface32((uint)swap->w, (uint)swap->h)))
    {
        SDL_FreeSurface(swap);
        return (NULL);
    }
    blit(swap, alphaSurf);
    SDL_FreeSurface(swap);
    ret = alphaSurf;
    if (filterWhite == 1)
        setWhitePixelsTransparent(ret); /// Test
    return (ret);
}

int             ui_initAssets(t_userInterface *ui)
{
    struct s_ui_assets      assets;
    SDL_Surface             *swap;

    assets = ui_setDefaultAssets();
    if (!ui)
        return (1);
    assets.spKill = ui_loadAsset("rc/asset/button/kill.bmp", 0);
    assets.button_on = ui_loadAsset("rc/asset/button/button_on.bmp", 0);
    assets.button_off = ui_loadAsset("rc/asset/button/button_off.bmp", 0);
    assets.grid = ui_loadAsset("rc/asset/sym/grid.bmp", 0);
    assets.scroller = ui_loadAsset("rc/asset/button/scroller.bmp", 0);
    assets.arrow_d = ui_loadAsset("rc/asset/sym/arrow_d.bmp", 1);
    assets.arrow_u = ui_loadAsset("rc/asset/sym/arrow_u.bmp", 1);
    assets.arrow_l = ui_loadAsset("rc/asset/sym/arrow_l.bmp", 1);
    assets.arrow_r = ui_loadAsset("rc/asset/sym/arrow_r.bmp", 1);
    assets.cross = ui_loadAsset("rc/asset/sym/cross.bmp", 1);
    assets.save = ui_loadAsset("rc/asset/sym/save.bmp", 1);
    assets.fall = ui_loadAsset("rc/asset/sym/fall.bmp", 1);
    assets.azerty = ui_loadAsset("rc/asset/pic/azerty.bmp", 0);
    assets.nagscreen = ui_loadAsset("rc/nagscreen_64.bmp", 0);
    assets.bye = ui_loadAsset("rc/asset/sym/bye.bmp", 1);
    ui->assets = assets;
    return (0);
}
