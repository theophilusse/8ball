#include "mouse.h"

int             mouse_clickUI(t_ui_box *box, int *relClick)
{
    uint            i;
    t_box_content   *content;
    t_box_item      *item;

    if (!box || !relClick)
        return (-1);
    if (relClick[0] < 0 || relClick[1] < 0)
        return (-1);
    if (!(content = box->content))
        return (-1);
    i = -1;
    while (++i < UI_BOX_CONTENT_MAX_ITEM && i < box->content->n_item)
    {
        item = &content->item[i];
        if (isInZone(relClick, item->dim, item->pos))
            return (i);
    }
    return (-1); /** Return box->content->Item INDEX **/
}
