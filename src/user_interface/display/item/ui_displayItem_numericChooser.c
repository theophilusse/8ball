#include "user_interface.h"

int             ui_displayItem_numericChooser(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item,
                    uchar boxHandle, uint itemHandle, uint vrtOffset)
{
    ///DATATYPE	*DATAPTR;
    uchar       rgbColor[4] = { 128 , 0 , 0 , SDL_ALPHA_OPAQUE };
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
        item->pos[1] = vrtOffset;
    }
    if (item->status.param[0] != 1)
        item->pos[1] = vrtOffset;
    pos[0] = (item->pos[0] - box->horizontal_bar.shift) + box->pos[0];
    pos[1] = (item->pos[1] - box->vertical_bar.shift) + box->pos[1];
    DEBUG ///
    square_dim(viewport, pos[0], pos[1], (int)item->dim[0], (int)item->dim[1], rgbColor, maxDim, minDim);

    int posShift[2];
    uint dim[2];
    uchar isPressed;

    ///if (mega->ui->event.type == UI_ITEMTYPE_NUMERICCHOOSER)
    if (mega->ui->event.itemHandle == itemHandle && mega->ui->event.handle == boxHandle && /*box->z_index == 0 &&*/ mega->ui->event.flag != 0)
        isPressed = 1;
    else
        isPressed = 0;
    dim[0] = 16;
    dim[1] = 16;
    posShift[0] = pos[0] + (item->dim[0] - 16);
    posShift[1] = pos[1];
    ///ui_drawButton(viewport, box, pos, dim, 0, 0);

    char        b[3];

    b[0] = mega->ui->event.flag == 1 ? 1 : 0;
    b[1] = mega->ui->event.flag == 2 ? 1 : 0;
    b[2] = mega->ui->event.flag == 3 ? 1 : 0;
    ui_drawButton(viewport, box, pos, dim, isPressed == 1 && b[1] == 1, 1, mega->ui->assets.arrow_l);
    ui_drawButton(viewport, box, posShift, dim, isPressed == 1 && b[2] == 1, 1, mega->ui->assets.arrow_r);

    /* ***************************** */
    /** /// OUT OF BOUND
        blit_at(mega->ui->assets.arrow_l, viewport, pos[0], pos[1]);
        blit_at(mega->ui->assets.arrow_r, viewport, posShift[0], posShift[1]);
    */
    /** /// NOTHING
    //
        maxDim[0] = box->pos[0] + (int)box->dim[0] - ((2 * UI_BORDER_WIDTH) + 16);
        maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
        minDim[0] = box->pos[0] + 1;
        minDim[1] = box->pos[1] + 23;
    //
        blit_at_dim(mega->ui->assets.arrow_l, viewport, pos[0], pos[1], maxDim, minDim, 1);
        blit_at_dim(mega->ui->assets.arrow_r, viewport, posShift[0], posShift[1], maxDim, minDim, 1);
    */
    /** /// CRASH
        t_ui_assets         *assets;

        assets = &mega->ui->assets;
        DEBUG ///
        blit_at_dimRect(assets->arrow_l, viewport, pos[0], pos[1], maxDim, minDim, 0);
        blit_at_dimRect(assets->arrow_r, viewport, posShift[0], posShift[1], maxDim, minDim, 0);
    */
    /** /// WORKING
        /// ???
    */
    /* ***************************** */

    int zoneWidth;
    size_t textWidth;
    char valuePreview[32];

    memset((void *)valuePreview, 0, 32);
    zoneWidth = (item->dim[0] - 32) / 16;
    if (zoneWidth < 3 || !item->ptr)
        return (vrtOffset + item->dim[1]); /// Can't display value !

    uchar dataType;
    dataType = item->status.param[2];
    /*
    if (dataType != UI_DATATYPE_INT)
        return (vrtOffset + item->dim[1]); /// FOR NOW PRINT ONLY INTEGERS !
    */
    valToStr(item->ptr, (char *)valuePreview, dataType);
    ///uint_get(item->ptr, valuePreview);
    /*textWidth = strlen((const char *)valuePreview);
    if (textWidth > zoneWidth && textWidth > 3)
    {
        valuePreview[textWidth - 1] = '.';
        valuePreview[textWidth - 2] = '.';
        valuePreview[textWidth - 3] = '.';
    }*/
    valuePreview[zoneWidth] = '\0';
    printf("valuePreview : [%s]\n", valuePreview);
    ///return (vrtOffset + item->dim[1]);
    /**
        charset_print(viewport, mega->ui->font_bis.charset, pos[0] + 16, pos[1], valuePreview);
    */
    /**
        charset_print(viewport, mega->ui->font_bis.charset, pos[0] + 16, pos[1], valuePreview);
        charset_printWidthSelection(viewport, box, mega->ui->font_bis.charset, mega->ui->font.charset,
                                    pos[0] + 16, pos[1], )
    */
        ///charset_printStopWidthSelection(viewport, box, mega->ui->font_bis.charset, mega->ui->font.charset,
        charset_printStopWidthSelection(viewport, box, mega->ui->font_bis.charset, mega->ui->font.charset,
                                        pos[0] + 16, pos[1], zoneWidth - 16, valuePreview, NULL, maxDim, minDim);
    return (vrtOffset + item->dim[1]);
}
