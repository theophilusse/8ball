#include "user_interface.h"

void            ui_releaseItem_string(t_box_item *item)
{
    if (item->ptr)
        FREE(item->ptr);
}
