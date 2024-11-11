#include "user_interface.h"

void            ui_drawScrollBar(t_userInterface *ui, t_ui_box *box, struct s_ui_scrollbar sb, SDL_Surface *viewport)
{
    t_ui_assets     *assets;
    int             pos[2];
    uint            dim[2];
    uchar           _gray_bar[4] = { 170, 170, 170, SDL_ALPHA_OPAQUE };
    uchar           activeButton[5];

    if (!(assets = &ui->assets) || !box)
        return ;
    activeButton[0] = 0; /// First Arrow
    activeButton[1] = 0; /// Second Arrow
    activeButton[2] = 0; /// Cursor
    activeButton[3] = 0; /// First Block
    activeButton[4] = 0; /// Second Block
    if (ui->event.type == UI_EVENT_SCROLLBAR && ui->event.itemHandle != 255 /*&& box->z_index == 0*/)
    {
        if (ui->event.itemHandle < 5 && sb.axis == 0)
            activeButton[ui->event.itemHandle] = 1;
        if (ui->event.itemHandle >= 5 && sb.axis == 1)
            activeButton[(ui->event.itemHandle % 5)] = 1;

    }
    if (sb.axis == 0) /*** Horizontal ScrollBar **/
    {
        /** Arrow Left **/
        dim[0] = assets->arrow_l->w;
        dim[1] = assets->arrow_l->h;
        pos[0] = box->pos[0] + UI_BORDER_WIDTH - 1;
        pos[1] = box->pos[1] + ((int)box->dim[1] - (UI_BORDER_WIDTH + (int)dim[1] - 1)),
        ui_drawButton(viewport, box, pos, dim, activeButton[0], 0, assets->arrow_l); /// Good.
        ///blit_at(assets->arrow_l, viewport, pos[0], pos[1]);

        /** Horizontal Bar **/
        dim[0] = box->dim[0] - (UI_BORDER_WIDTH + assets->arrow_l->w + assets->arrow_r->w + assets->grid->w);
        dim[1] = assets->arrow_l->h + 1;
        pos[0] = box->pos[0] + UI_BORDER_WIDTH + assets->arrow_l->w - 1;
        pos[1] = box->pos[1] + ((int)box->dim[1] - (UI_BORDER_WIDTH + (int)dim[1])) + 2,
        sb.length = dim[0] - assets->scroller->w;
        square(viewport, pos[0], pos[1], (int)dim[0], (int)dim[1], _gray_bar);

        /** Horizontal Scroller **/
        pos[0] = pos[0] + (sb.fPercent * (float)sb.length);
        blit_at(assets->scroller, viewport, pos[0], pos[1]);

        /** Arrow Right **/
        dim[0] = assets->arrow_r->w;
        dim[1] = assets->arrow_r->h;
        pos[0] = box->pos[0] + ((int)box->dim[0] - (UI_BORDER_WIDTH + (int)dim[0] * 2)) + 2,
        pos[1] = box->pos[1] + ((int)box->dim[1] - (UI_BORDER_WIDTH + (int)dim[1])) + 1;
        ui_drawButton(viewport, box, pos, dim, activeButton[1], 0, assets->arrow_r);
        ///blit_at(assets->arrow_r, viewport, pos[0], pos[1]);
    }
    if (sb.axis == 1) /*** Vertical ScrollBar **/
    {
        /** Arrow Up ***/
        dim[0] = assets->arrow_u->w;
        dim[1] = assets->arrow_u->h;
        pos[0] = box->pos[0] + ((int)box->dim[0] - (UI_BORDER_WIDTH + (int)dim[0])) + 2,
        pos[1] = box->pos[1] + (16 + 2 * UI_BORDER_WIDTH) - 1;
        ui_drawButton(viewport, box, pos, dim, activeButton[0], 0, assets->arrow_u);
        ///blit_at(assets->arrow_u, viewport, pos[0], pos[1]);

        /** Vertical Bar **/
        dim[0] = assets->arrow_l->w;
        dim[1] = box->dim[1] - ((2 * UI_BORDER_WIDTH) + assets->arrow_u->h + assets->arrow_d->h + assets->grid->h + 18);
        pos[0] = box->pos[0] + ((int)box->dim[0] - (UI_BORDER_WIDTH + (int)dim[0])) + 2,
        pos[1] = box->pos[1] + (16 + 2 * UI_BORDER_WIDTH + assets->arrow_u->h);
        sb.length = dim[1] - assets->scroller->h;
        square(viewport, pos[0], pos[1], (int)dim[0], (int)dim[1], _gray_bar);

        /** Vertical Scroller **/
        pos[1] = pos[1] + (sb.fPercent * (float)sb.length);
        blit_at(assets->scroller, viewport, pos[0], pos[1]);

        /** Arrow Down **/
        dim[0] = assets->arrow_d->w;
        dim[1] = assets->arrow_d->h;
        pos[0] = box->pos[0] + ((int)box->dim[0] - (UI_BORDER_WIDTH + (int)dim[0])) + 2,
        pos[1] = box->pos[1] + ((int)box->dim[1] - (16 + UI_BORDER_WIDTH + (int)dim[1])) + 1;
        ui_drawButton(viewport, box, pos, dim, activeButton[1], 0, assets->arrow_d);
        ///blit_at(assets->arrow_d, viewport, pos[0], pos[1]);
    }
}
