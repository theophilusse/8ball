#include "user_interface.h"

void            ui_releaseItem(t_box_item *item)
{
    if (!item)
        return ;
    switch (item->type)
    {
        case UI_ITEMTYPE_STRING:
        {
            ui_releaseItem_string(item);
            break;
        }
        case UI_ITEMTYPE_SIMPLE_BUTTON:
        {
            ui_releaseItem_simpleButton(item);
            break;
        }
        case UI_ITEMTYPE_NUMERICCHOOSER:
        {
            ui_releaseItem_numericChooser(item);
            break;
        }
    }
}
