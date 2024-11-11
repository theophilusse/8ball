#include "user_interface.h"

int                 ui_stringGetPtrAt(t_mega *mega, t_userInterface *ui, t_box_item *item, int *relClick)
{
    int             ret;
    t_ui_box        *box;
    //int             textClick[2];

    if (!mega || !ui || !item || !relClick)
        return (-1);
    /*textClick[0] = relClick[0] - item->pos[0];
    textClick[1] = relClick[1] - item->pos[1];*/
    //ui->event.itemHandle;
    ///printf("Item Dim [%u][%u]\n", item->dim[0], item->dim[1]); ///
    /*if (!isInZone(relClick, item->dim, item->pos))
        return (NULL);*/
    if (ui->event.handle == 255 || ui->event.handle > UI_BOX_COUNT)
        return (-1);
    box = &ui->box[ui->event.handle];

    int lineWidth = UI_BORDER_WIDTH;
    int twoLineWidth = lineWidth * 2;
    ret = charset_getOffsetWidth(box, mega->ui->font.charset,
                        item->pos[0] + lineWidth,
                        (int)item->pos[1],
                        ///(uint)(box->dim[0] - (twoLineWidth + item->pos[0])),
                        (uint)(box->dim[0] - (twoLineWidth + item->pos[0] + 32)),
                        SDL_TRUE, (char *)item->ptr, relClick);
    return (ret);
}
