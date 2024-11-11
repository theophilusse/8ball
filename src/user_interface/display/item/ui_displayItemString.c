#include "user_interface.h"

int             ui_displayItemString(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item,
                                     uchar boxHandle, uint itemHandle, uint vrtOffset)
{
    int             *pIndex;
    int             pos[2];
    int             maxDim[2];
    int             minDim[2];
    int             _w;
    uint            currentVerticalPos;

    if (!viewport || !mega || !box || !item)
        return (0);
    maxDim[0] = box->pos[0] + (int)box->dim[0] - ((2 * UI_BORDER_WIDTH) + 16);
    maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
    minDim[0] = box->pos[0] + 1;
    minDim[1] = box->pos[1] + 23;
    if (item->status.param[0] == 1 || item->pos[1] < vrtOffset)
    {
        item->status.param[0] = 0;
        if (item->pos[1] < vrtOffset /** && rect_overlap() ?? **/)
            item->pos[1] = vrtOffset;
    }
    if (item->status.param[0] != 1)
        item->pos[1] = vrtOffset;
    DEBUG ///
    pIndex = NULL;
    _w = box->dim[0] - (((UI_BORDER_WIDTH * 2) + 32) + item->pos[0]);
    pos[0] = item->pos[0] - box->horizontal_bar.shift;
    pos[1] = item->pos[1] - box->vertical_bar.shift;
    if (mega->ui->event.itemHandle == itemHandle && mega->ui->event.handle == boxHandle /*&& box->z_index == 0*/)
        pIndex = mega->ui->event.pIndex;
    DEBUG ///
    /* printf("[ITEMHANDLE : %u] Current Vertical POSITION [%u]\n", itemHandle, vrtOffset); /// Debug. */
    currentVerticalPos = charset_printWidthSelection(viewport, box, box->font->charset, mega->ui->font_bis.charset,
                                /// /// Original.
                                /** /// Test
                                    pos[0] + 39 + box->pos[0],
                                    pos[1] + box->pos[1], ///
                                */
                                /// Test
                                    pos[0],
                                    pos[1],
                                _w,
                                SDL_TRUE, (char *)item->ptr, pIndex,
                                maxDim, minDim);
    DEBUG ///
    ///item->dim[1] = currentVerticalPos - pos[1]; /// Original.
    /* printf("[ITEMHANDLE : %u] Current Vertical POSITION [%u] (pos.[%d])\n", itemHandle, currentVerticalPos, pos[1]); /// Debug. */
    item->dim[1] = currentVerticalPos - pos[1]; /// Original.
    ///item->dim[1] = currentVerticalPos - vrtOffset; /// Test.
    ///item->dim[1] = currentVerticalPos - (pos[1] + box->pos[1]); /// Test
    ///item->dim[1] = currentVerticalPos; /// Test.
    ///item->dim[1] = currentVerticalPos - pos[1] + box->vertical_bar.shift; /// Test
    ///return (currentVerticalPos - (/*pos[1] +*/ box->pos[1]));
    /* printf("Dsp: Dim.Y [%u]\n", item->dim[1]);/// /// */
    ///return (vrtOffset + item->dim[1]);
    /* printf("RETURN : %u\n", (uint)((int)item->pos[1] + item->dim[1])); */
    DEBUG ///
    return ((uint)((int)item->pos[1] + item->dim[1]) + 16);
}
