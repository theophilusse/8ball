#include "user_interface.h"

int             ui_getItemHeight_numericChooser(t_box_item *item, int currentVerticalPos)
{
    if (!item)
         return (currentVerticalPos);
    ///return (currentVerticalPos + item->dim[1] + 32);
    return (currentVerticalPos + item->dim[1]);
}
