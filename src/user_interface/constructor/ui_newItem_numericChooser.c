#include "user_interface.h"

struct s_box_item            ui_newItem_numericChooser(t_mega *mega, t_ui_box *box, uint digits, int *pos, void *data, float itemFactor, uchar datatype, struct s_ui_function ft)
{
    struct s_box_item       item;

    if (!mega || !box)
        return (set_default_box_item());
    item = set_default_box_item();
    item.pos[0] = 32;
    item.pos[1] = -1;
    if (pos)
    {
          item.status.param[0] = 1;
          item.pos[0] = pos[0];
          item.pos[1] = pos[1];
    }
    item.dim[0] = 32 + (digits * 16);
    item.dim[1] = 16;
    item.ptr = data;
    item.type = UI_ITEMTYPE_NUMERICCHOOSER;
    item.status.active = 1;
    item.status.factor = itemFactor;
    item.status.param[2] = datatype;
    item.ft = ft;
    return (item);
}
