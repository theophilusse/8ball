#include "user_interface.h"

uint             ui_displayItem(t_mega *mega, SDL_Surface *viewport, t_ui_box *box, t_box_item *item, uchar boxHandle, uchar itemHandle, uint vrtOffset)
{
    ///if (item->pos[1] == -1) // Static Position. (bad)
    ///item->pos[1] = currentVerticalPos; /// Responsive.
    /** /// Original. // Keep
        item->pos[1] = currentVerticalPos - point[1] + 16; /// Responsive.
    */
    /*item->pos[1] -= box->vertical_bar.shift;*/
    /** /// Original.
        pos[0] = point[0] + item->pos[0] + lineWidth;
        pos[1] = (int)item->pos[1] + (int)box->pos[1];
    */
    /*pos[0] = item->pos[0] - box->horizontal_bar.shift;
    pos[1] = item->pos[1] - box->vertical_bar.shift;*/
    /*pos[0] = item->pos[0] - box->horizontal_bar.shift;
    pos[1] = item->pos[1] - box->vertical_bar.shift;*/
    ///item->pos[1] = currentVerticalPos - point[1] + 16; /// Responsive. TEST
    /**
        printf("Bars Shift [%u][%u]\n",
        box->horizontal_bar.shift,
        box->vertical_bar.shift);
    */
    /**
    pos[0] = point[0] + item->pos[0] + lineWidth - box->horizontal_bar.shift;
    pos[1] = (int)item->pos[1] + (int)box->pos[1] - box->vertical_bar.shift;
    */
    DEBUG ///
    printf("DBG Item @ %p | type[%d]\n", item, item->type); ///
    switch (item->type)
    {
        case UI_ITEMTYPE_STRING:
        {
            vrtOffset = ui_displayItemString(viewport, mega, box, item, boxHandle, itemHandle, vrtOffset);///
            break;
        }
        case UI_ITEMTYPE_SIMPLE_BUTTON:
        {
            vrtOffset = ui_displayItemButton(viewport, mega, box, item, boxHandle, itemHandle, vrtOffset);
            break;
        }
        case UI_ITEMTYPE_PICTURE:
        {
            vrtOffset = ui_displayItemPicture(viewport, mega, box, item, boxHandle, itemHandle, vrtOffset);
            break;
        }
        case UI_ITEMTYPE_NUMERICCHOOSER:
        {
            vrtOffset = ui_displayItem_numericChooser(viewport, mega, box, item, boxHandle, itemHandle, vrtOffset);
            break;
        }
        default : { break; }
    }
    DEBUG ///
    /** Todo **/
    /// Refresh environement dimension for scrollar ui_newBox -> ui_getBoxEnvDim.c
    ///box->envDim[1] = currentVerticalPos + 16; /// Refresh Environement Dimension for scrollbar.
    return (vrtOffset);
}
