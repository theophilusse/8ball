#include "user_interface.h"

void            ui_releaseBox(t_ui_box *box)
{
    t_box_content       *content;
    uint                i;

    if (!box)
        return ;
    if (!(content = box->content))
        return ;
    i = -1;
    while (++i < UI_BOX_CONTENT_MAX_ITEM)
        ui_releaseItem(&content->item[i]);
    FREE(content);
    box->content = NULL;
}
