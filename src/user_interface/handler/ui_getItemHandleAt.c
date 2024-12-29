#include "user_interface.h"

static int          ui_getItemHandle_pictureAt(t_userInterface *ui, t_ui_box *box, t_box_item *item, int *onClick, uchar *handle, uchar itemHandle)
{
    int             relClick[2];
    int             btnPos[2];
    uint            btnDim[2];

    if (!item || !box)
        return (0);
    relClick[0] = onClick[0];
    relClick[1] = onClick[1];
    btnPos[0] = item->pos[0] - box->horizontal_bar.shift;/// + UI_BORDER_WIDTH;
    btnPos[1] = item->pos[1] - box->vertical_bar.shift;///(16 + (2 * UI_BORDER_WIDTH));;
    btnDim[0] = item->dim[0];
    btnDim[1] = item->dim[1];
    if (isInZone(relClick, btnDim, btnPos))
    {
        if (ui)
            ui->sigRefresh = 1;
        if (handle)
            *handle = (uchar)itemHandle;
        return (1);
    }
    return (0);
}

static int          ui_getItemHandle_buttonAt(t_userInterface *ui, t_ui_box *box, t_box_item *item, int *onClick, uchar *handle, uchar itemHandle)
{
    int             relClick[2];
    int             btnPos[2];
    uint            btnDim[2];

    if (!item || !box)
        return (0);
    relClick[0] = onClick[0];
    relClick[1] = onClick[1];
    btnPos[0] = item->pos[0] - box->horizontal_bar.shift;/// + UI_BORDER_WIDTH;
    btnPos[1] = item->pos[1] - box->vertical_bar.shift;///(16 + (2 * UI_BORDER_WIDTH));;
    btnDim[0] = item->dim[0];
    btnDim[1] = item->dim[1];
    if (isInZone(relClick, btnDim, btnPos))
    {
        if (ui)
            ui->sigRefresh = 1;
        if (handle)
            *handle = (uchar)itemHandle;
        return (1);
    }
    return (0);
}

static int         ui_getItemHandle_stringAt(t_userInterface *ui, t_ui_box *box, t_box_item *item, int *onClick, uchar *handle, uchar itemHandle)
{
    int         relClick[2];
    int         btnPos[2];
    uint         btnDim[2];

    if (!item || !box)
        return (0);
    relClick[0] = onClick[0];
    relClick[1] = onClick[1];
    btnPos[0] = item->pos[0] - box->horizontal_bar.shift;/// + UI_BORDER_WIDTH;
    btnPos[1] = item->pos[1] - box->vertical_bar.shift;///(16 + (2 * UI_BORDER_WIDTH));;
    btnDim[0] = item->dim[0];
    btnDim[1] = item->dim[1];
    if (!isInZone(relClick, btnDim, btnPos))
        return (0);
    if (handle)
        *handle = (uchar)itemHandle;
    printf("\tBTN%u: pos.[%d][%d] ; dim.[%u][%u]\n", itemHandle,
        btnPos[0],
        btnPos[1],
        btnDim[0],
        btnDim[1]);///
    ///BEEP///
    /** item->status.active = 0; **/
    if (ui)
        ui->sigRefresh = 1;
    return (1);
}

static int         ui_getItemHandle_numericChooserAt(t_userInterface *ui, t_ui_box *box, t_box_item *item, int *onClick, uchar *handle, uchar itemHandle)
{
    int             relClick[2];
    int             btnPos[2];
    uint            btnDim[2];

    if (!ui || !box || !item || !onClick || !handle)
        return (0);
    /*if (!item || !box)
        return (0);*/
    relClick[0] = onClick[0];
    relClick[1] = onClick[1];
    btnPos[0] = item->pos[0] - box->horizontal_bar.shift;/// + UI_BORDER_WIDTH;
    btnPos[1] = item->pos[1] - box->vertical_bar.shift;///(16 + (2 * UI_BORDER_WIDTH));;
    btnDim[0] = item->dim[0];
    btnDim[1] = item->dim[1];
    if (isInZone(relClick, btnDim, btnPos))
    {
        if (ui)
            ui->sigRefresh = 1;
        if (handle)
            *handle = (uchar)itemHandle;
        return (1);
    }
    return (0);
}

/** Boggy zone detection **/
uchar             ui_getItemHandleAt(t_userInterface *ui, t_ui_box *box, int *onClick, uchar *handle)
{
    t_box_item       *item;
    uint             i;
    //uint             btnDim[2];
    int              btnPos[2];

    if (!box || !onClick)
        return (UI_ITEMTYPE_EMPTY);
    if (handle)
        ///*handle = -1;
        *handle = 255;
    i = -1;
    //int relClick[2];
    /*relClick[0] = onClick[0] + box->horizontal_bar.shift;
    relClick[1] = onClick[1] + box->vertical_bar.shift;*/
    //relClick[0] = onClick[0] - 4;
    //relClick[1] = onClick[1] - (39 + 16);
    item = &box->content->item[0];
    while (++i < UI_BOX_CONTENT_MAX_ITEM && i < box->content->n_item)
    {
        /** /// Original.
        btnPos[0] = box->pos[0] + item->pos[0] - box->horizontal_bar.shift;/// + UI_BORDER_WIDTH;
        btnPos[1] = box->pos[1] + item->pos[1] - box->vertical_bar.shift - 16;///(16 + (2 * UI_BORDER_WIDTH));;
        */
        /*btnPos[0] = item->pos[0];
        btnPos[1] = item->pos[1];*/
        //btnDim[0] = item->dim[0];
        ///btnDim[1] = item->dim[1] + 16;
        ///btnDim[1] = item->dim[1] - 16;
        //btnDim[1] = item->dim[1];
        ///printf("GetItemHandle At[%d][%d], #[%u]:(%u ; %u)\n", relClick[0], relClick[1], i, item->pos[0], item->pos[1]);
        ///if (item->status.active != 0 && isInZone(onClick, btnDim, btnPos))
        if (item->status.active != 0)
        {
            ///DEBUG ///
            /**if (handle)
                *handle = (uchar)i;*/
            //ui_swapBox(mega->ui, handle);
            //item->status.active = 0;
            switch (item->type)
            {
                case UI_ITEMTYPE_STRING:
                {
                    if (ui_getItemHandle_stringAt(ui, box, item, onClick, handle, i))
                        return (item->type);
                    /*break;*/
                }
                case UI_ITEMTYPE_SIMPLE_BUTTON: // Test.
                {
                    if (ui_getItemHandle_buttonAt(ui, box, item, onClick, handle, i))
                        return (item->type);
                    /*break;*/
                }
                case UI_ITEMTYPE_NUMERICCHOOSER:
                {
                    if (ui_getItemHandle_numericChooserAt(ui, box, item, onClick, handle, i))
                        return (item->type);
                }
                default: { break; }
            }
            ///return (1);
            ///return (item->type);
        }
        item++;
    }
    return (UI_ITEMTYPE_EMPTY);
}
