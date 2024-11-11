#include "user_interface.h"

void            ui_displayItemScrollBar(SDL_Surface *viewport, t_userInterface *ui, t_ui_box *box)
{
    if (!box || !viewport || !ui)
        return ;
    blit_at(ui->assets.grid, viewport,
            box->pos[0] + (box->dim[0] - ui->assets.grid->w) - 1,
            box->pos[1] + (box->dim[1] - ui->assets.grid->h) - 1);
            /*
                point[16] - 16,///pos[0],// + ((int)box->dim[0] - (twoLineWidth + 16)),
                point[17] - 16);///pos[1]);// + ((int)box->dim[1] - (twoLineWidth + 16)));
            */
    if (box->envDim[0] > box->dim[0])
        ui_drawScrollBar(ui, box, box->horizontal_bar, viewport);
    if (box->envDim[1] + (39 + 18) >= box->dim[1])
        ui_drawScrollBar(ui, box, box->vertical_bar, viewport);
}
