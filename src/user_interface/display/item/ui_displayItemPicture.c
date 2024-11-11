#include "user_interface.h"

int             ui_displayItemPicture(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item,
                                     uchar boxHandle, uint itemHandle, uint vrtOffset)
{
    SDL_Surface *surf;
    int         maxDim[2];
    int         minDim[2];
    int         pos[2];

    if (!item)
        return (0);
    maxDim[0] = box->pos[0] + (int)box->dim[0] - (UI_BORDER_WIDTH + 16);
    maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
    minDim[0] = box->pos[0] + 1;
    minDim[1] = box->pos[1] + 23;
    /// SCROLLBAR SHIFTING POS ///
    if (item->status.param[0] == 1 || item->pos[1] < vrtOffset)
    {
        item->status.param[0] = 0;
        if (item->pos[1] < vrtOffset) /// && rect_overlap() ??
            item->pos[1] = vrtOffset;
    }
    if (item->status.param[0] != 1)
        item->pos[1] = vrtOffset;
    pos[0] = (item->pos[0] - box->horizontal_bar.shift) + box->pos[0];
    pos[1] = (item->pos[1] - box->vertical_bar.shift) + box->pos[1];
    if (item->ptr)
    {
        surf = (SDL_Surface *)item->ptr;
        ///blit_at_dim(surf, mega->screen, pos[0], pos[1], maxDim, minDim, 1);
        blit_at_dim(surf, viewport, pos[0], pos[1], maxDim, minDim, 1); /// Original
        ///blit_at_dim(surf, viewport, pos[0], pos[1], maxDim, minDim, 0); /// Test BGRA
        /**
        blit_at_dim(surf, viewport, shiftPos[0] + ((int)item->dim[0] / 2) - (surf->w / 2),
                                        shiftPos[1] + (int)(item->dim[1] / 2) - (surf->h / 2), maxDim, minDim, 1);
        */
    }
    return (vrtOffset + item->dim[1]);
}
