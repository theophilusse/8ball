#include "user_interface.h"

int             ui_displayItemButton(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item,
                                     uchar boxHandle, uint itemHandle, uint vrtOffset)
{
    t_simple_button         *button;
    uchar                   buttonIsPressed;
    int         maxDim[2];
    int         minDim[2];
    int         pos[2];

    if (!(button = (t_simple_button *)item->ptr))
        return (0);
    maxDim[0] = box->pos[0] + (int)box->dim[0] - ((2 * UI_BORDER_WIDTH) + 16);
    maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
    minDim[0] = box->pos[0] + 1;
    minDim[1] = box->pos[1] + 23;
    if (mega->ui->event.itemHandle == itemHandle && mega->ui->event.handle == boxHandle /*&& box->z_index == 0*/ && mega->ui->event.flag == 1)
        buttonIsPressed = 1;
    else
        buttonIsPressed = 0;
    /// SCROLLBAR SHIFTING POS ///
    if (item->status.param[0] == 1 || item->pos[1] < vrtOffset)
    {
        item->status.param[0] = 0;
        if (item->pos[1] < vrtOffset) /// && rect_overlap() ??
            item->pos[1] = vrtOffset;
    }
    if (item->status.param[0] != 1)
        item->pos[1] = vrtOffset;
    pos[0] = item->pos[0] - box->horizontal_bar.shift;
    pos[1] = item->pos[1] - box->vertical_bar.shift;
    int shiftPos[2];
    ///shiftPos[0] = (point[0] + lineWidth) + pos[0]; /* Original **/
    /*shiftPos[0] = (39 + box->pos[0]) + pos[0];
    shiftPos[1] = box->pos[1] + pos[1];*/
    shiftPos[0] = pos[0] + box->pos[0];
    shiftPos[1] = pos[1] + box->pos[1];
    /*shiftPos[0] = pos[0];
    shiftPos[1] = pos[1];*/
    /// SCROLLBAR SHIFTING POS ///
    ui_drawButton(viewport, box, shiftPos, item->dim, buttonIsPressed, 1, NULL);
    if (button->srf)
    {
        SDL_Surface         *stretchSrf;
        uint                dimStretch[2];
        float               scaleDim[2];
        uchar               axisIndex;

        uint minDimScale;
        minDimScale = item->dim[0] > item->dim[1] ? item->dim[1] : item->dim[0];
        dimStretch[0] = item->dim[1];
        dimStretch[1] = item->dim[0];
        dimStretch[0] -= (2 * UI_BORDER_WIDTH);
        dimStretch[1] -= (2 * UI_BORDER_WIDTH);
        minDimScale -= (2 * UI_BORDER_WIDTH);
        scaleDim[0] = (dimStretch[0] / button->srf->w);
        scaleDim[1] = (dimStretch[1] / button->srf->h);
        if (minDimScale == dimStretch[1])
            axisIndex = 1;
        else
            axisIndex = 0;
        if (minDimScale < 14)
            scaleDim[axisIndex] = (1.0 / scaleDim[axisIndex]);
        if ((stretchSrf = stretch_surface(button->srf, button->srf->w * scaleDim[axisIndex], button->srf->h * scaleDim[axisIndex])))
        {
            blit_at_dim(stretchSrf, viewport, shiftPos[0] + ((int)item->dim[0] / 2) - (stretchSrf->w / 2),
                                        shiftPos[1] + (int)(item->dim[1] / 2) - (stretchSrf->h / 2), maxDim, minDim, 1);
            SDL_FreeSurface(stretchSrf);
        }
        ///SDL_Rect    rect;
        /*rect.h = button->srf->w * 2;
        rect.w = button->srf->h * 2;
        rect.x = ((int)item->dim[0] / 2) - (button->srf->w / 2);
        rect.y = (int)(item->dim[1] / 2) - (button->srf->h / 2);
        SDL_BlitSurface(button->srf, &rect, viewport, &viewport->clip_rect);*/
    }
    else
    {
        DEBUG ///
        printf("Simple Button Text Not Implemented\n");
    }
    return (vrtOffset + item->dim[1] + 32);
}

    /**
    if (item->pos[0] >= (int)box->dim[0] ||
        item->pos[1] >= (int)box->dim[1] ||
        item->pos[0] + (int)item->dim[0] < (int)box->dim[0] ||
        item->pos[1] + (int)item->dim[1] < (int)box->dim[1])
        break;
        **/
    ///if (item->pos[0] > (int)box->dim[0] - ((int)item->dim[0] + lineWidth) ||
    ///   item->pos[1] > (int)box->dim[1] - ((int)item->dim[1] + lineWidth) ||
    ///**if (item->pos[0] >= (int)box->dim[0] - lineWidth ||
    ///item->pos[1] >= (int)box->dim[1] - lineWidth ||**/
    ///item->pos[0] < lineWidth || item->pos[1] < lineWidth)
    /// break;

    //if (item->pos[0] > (int)box->dim[0] - ((int)item->dim[0] + lineWidth) || /// Good.
        ///item->pos[1] >= (int)box->dim[1] - lineWidth/* - ((int)item->dim[1] + lineWidth) */||
        //item->pos[1] >= (int)box->dim[1] - lineWidth)
    ///**if (item->pos[0] >= (int)box->dim[0] - lineWidth ||
    ///item->pos[1] >= (int)box->dim[1] - lineWidth ||**/
        ///item->pos[0] < lineWidth || item->pos[1] < lineWidth) /// Original
        ///item->pos[0] < (int)box->dim[0] * -1 || item->pos[1] < (int)box->dim[1] * -1) /// Test.
        ///item->pos[0] < -15 || item->pos[1] < -15)
        //break;
