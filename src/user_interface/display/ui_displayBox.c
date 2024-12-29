#include "user_interface.h"

int                    ui_displayBox(t_mega *mega, SDL_Surface *viewport, uchar boxHandle)
{
    uint            k;
    uint            w;
    uint            h;
    uint            maxChar;
    uint            titleLen;
    int             point[18];
    uint             lineWidth = UI_BORDER_WIDTH;
    //uint             twoLineWidth;
    t_box_item      *item;
    uchar           barColor[4];
    int             *pIndex;
    t_ui_box        *box;
    uint            vrtOffset;

    if (!mega || !viewport || !mega->ui || !(box = &mega->ui->box[boxHandle]))
        return (0);
    w = (uint)box->dim[0];
    h = (uint)box->dim[1];
    //twoLineWidth = lineWidth << 1;
    /// Test ScrollBar EnvDim
    //int maxDim[2];
    //int minDim[2];
    //maxDim[0] = box->pos[0] + (int)box->dim[0];
    //maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
    //minDim[0] = box->pos[0] + 1;
    //minDim[1] = box->pos[1] + 23;
    /// Test ScrollBar EnvDim
    DEBUG ///
    ui_drawBox(mega, viewport, boxHandle); /// Test.
    w >>= 4;
    h >>= 4;
    vrtOffset = 39;
    /*int pos[2];*/
    uint _w;
    DEBUG ///
    switch (box->content->type)
    {
        case BOX_CONTENT_DISPLAY:
        {
            k = -1;
            while (++k < UI_BOX_CONTENT_MAX_ITEM  && k < box->content->n_item)
            {
                item = &box->content->item[k];
                if (item->status.active == 0)
                    continue;
                vrtOffset = ui_displayItem(mega, viewport, box, item, boxHandle, k, vrtOffset);
            }
            break;
        }
        default : { break; }
    }
    DEBUG ///
    if (box->envDim[0] > box->dim[0] || box->envDim[1] + (39 + 18) >= box->dim[1])
        ui_displayItemScrollBar(viewport, mega->ui, box);
    return (0);
}
