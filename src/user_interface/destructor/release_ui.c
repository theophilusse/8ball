#include "user_interface.h"

void            release_ui(t_userInterface *ui)
{
    uint                i;
    uint                j;

    if (!ui)
        return ;
    i = -1;
    while (++i < 8)
        if (ui->box[i].content)
        {
            t_simple_button         *button;

            j = -1;
            while (++j < UI_BOX_CONTENT_MAX_ITEM)
                switch (ui->box[i].content->item[j].type)
                {
                    case UI_ITEMTYPE_SIMPLE_BUTTON:
                    {
                        button = (t_simple_button *)ui->box[i].content->item[j].ptr;
                        /*if (button->srf)
                            SDL_FreeSurface(button->srf);
                        button->srf = NULL;*/
                        FREE(button);
                    }
                }
            FREE(ui->box[i].content);
            ui->box[i].content = NULL;
            if (ui->box[i].viewport)
                SDL_FreeSurface(ui->box[i].viewport);
            ui->box[i].viewport = NULL;
        }
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
    i = -1;
    while (++i < UI_CURSOR_COUNT)
        if (ui->cursor[i])
        {
            SDL_FreeCursor(ui->cursor[i]);
            ui->cursor[i] = NULL;
        }
    ui_releaseAssets(&ui->assets);
    ui_releaseFont(&ui->font);
    ui_releaseFont(&ui->font_bis);
    FREE(ui);
}