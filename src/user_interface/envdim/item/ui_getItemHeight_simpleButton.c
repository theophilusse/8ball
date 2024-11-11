#include "user_interface.h"

int             ui_getItemHeight_simpleButton(t_box_item *item, int currentVerticalPos)
{
    if (!item)
        return (currentVerticalPos);
    return (currentVerticalPos + item->dim[1] + 32);
}
