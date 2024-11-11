#include "user_interface.h"

static void            ui_debugBox(t_mega *mega, uint handle)
{
    t_ui_box *box;

    if (!(box = &mega->ui->box[handle]))
        return ;
    printf("%u::[%s](%u)\n", handle, box->title, box->active);

}

static void             ui_debugAllBox(t_mega *mega)
{
    uint i;

    i = UI_BOX_COUNT;
    /*i = mega->ui->boxCount;*/
    printf("boxCount: %u\n", mega->ui->boxCount);
    while (i-- > 0)
        ui_debugBox(mega, i); ///
    printf(":::::::::::::::::::::::::::::::::::\n");
}

void            ui_main(t_mega *mega, t_userInterface *ui)
{
    ///uchar    uiQueue[UI_BOX_COUNT]; /** Store Box's ID sort by z-index decreasing **/
    static uchar    uiQueue[UI_BOX_COUNT]; /** Store Box's ID sort by z-index decreasing **/ // Original
    uchar           z_index[UI_BOX_COUNT];
    uint            len;
    uchar           z;
    uint            i;
    uint            q;
    /* SDL_Surface     **charset; */ // Old
    SDL_Surface     *viewport;
    char            flag = 0;

    if (!mega || !ui)
        return ;
    viewport = mega->ui_viewport;
    /*** Rogue. ***/
    uint                index;

    DEBUG ///
    if (mega->stcl->option.edit_mode)
    {
        if (ui->morpho.active == 1)
        {
            set_alpha(viewport, SDL_ALPHA_TRANSPARENT); /** Clear UI **/
            flag = 1;
            blit_at(ui->morpho.surface, viewport,  ui->morpho.pos[0], ui->morpho.pos[1]); /// CHANGE
                    /*mega.viewport->w - mega.ui->morpho.surface->w,
                        mega.viewport->h - mega.ui->morpho.surface->h);*/
            index = -1;
            while (++index < 44)
                if (ui->morpho.part[index].active)
                    blit_at(ui->morpho.part[index].surf, viewport, ui->morpho.pos[0], ui->morpho.pos[1]); /// CHANGE
                            /*mega.viewport->w - mega.ui->morpho.surface->w,
                             mega.viewport->h - mega.ui->morpho.surface->h);*/
        }
    }
    DEBUG ///
    /** Rogue. ***/
    //blit_at_dim(tile, s, x, y, NULL, NULL, 0);
    if (ui->sigRefresh != 1)
        return ;
    ui->sigRefresh = 0;
    if (flag != 1)
        set_alpha(viewport, SDL_ALPHA_TRANSPARENT); /** Clear UI **/

    DEBUG ///
    t_ui_box        *box;

    if (!(box = (t_ui_box *)ui->box))
        return ;
    /**
        DEBUG ///
        ui_debugAllBox(mega);
    **/
    i = ui->boxCount;
    while (i-- > 0)
    {
        /*if (box->z_index == 255)
            continue;*/
        if (ui->box[i].active != 0)
        {
            /// Do.
            /**
            ui_debugBox(mega, i); ///
            */
            ui_displayBox(mega, viewport, i);
        }
    }
    DEBUG ///
    ///charset_print(viewport, ui->font.charset, 0, viewport->h - 16, mega->tool[mega->currentTool].name);
    charset_print(viewport, mega->ui->font.charset, mega->screen->w - ((int)len + 1), mega->screen->h - 16, mega->tool[mega->currentTool].name);
}
