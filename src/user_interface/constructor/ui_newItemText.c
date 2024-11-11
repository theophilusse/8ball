#include "user_interface.h"

struct s_box_item            ui_newItemText(t_mega *mega, t_ui_box *box, char *str, int *pos)
{
    uint                    width;
    struct s_box_item       item;

    if (!mega || !box || !str) /// || pos || !dim)
        return (set_default_box_item());
    ///item.pos[0] = 32; /// Test.
    item.pos[0] = 16; /// Test.
    item.pos[1] = -1; /// Test.
    if (pos)
    {
        item.status.param[0] = 1;
        item.pos[0] = pos[0]; /// Test.
        item.pos[1] = pos[1]; /// Test./
    }
    item.blockSize = strlen(str);
    item.dataSize = sizeof(char);
    width = (box->dim[0] - (uint)item.pos[0]) / 16;
    if (width == 0)
        width = 1;
    /*else
        width--;*/
    item.dim[0] = (width - 1) * 16;
    item.dim[1] = ((item.blockSize / (width + 1)) * 16)/* - (32 + UI_BORDER_WIDTH * 2)*/;
    ///item->dim[1] = ((box->content->item[1].blockSize / width) + 1) * 16/* - (32 + UI_BORDER_WIDTH * 2)*/;
    ///item->dim[1] = (2 * 16)/* - (32 + UI_BORDER_WIDTH * 2)*/;

    item.ptr = ft_strdup((const char *)str);
    item.type = UI_ITEMTYPE_STRING; /// RAW String.
    item.status.active = 1;
    ///box->content->item[0].status.factor = 0.0; // Unused.

    /// ui_newItemText(mega, str, pos, dim); /// Todo.
    return (item);
}
