#include "user_interface.h"

uint        ui_getScrollBarLength(t_ui_box *box, uchar axis)
{
    if (!box || axis >= 2)
        return (1);
    return (box->dim[axis] - ((16 + 16 + 16) + UI_BORDER_WIDTH * 2));
}
