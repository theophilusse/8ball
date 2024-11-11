#include "user_interface.h"

struct s_box_item            ui_newItemPicture(t_mega *mega, t_ui_box *box, SDL_Surface *picture, int *pos)
{
    struct s_box_item       item;

    if (!mega || !box || !picture) /// || pos || !dim)
        return (set_default_box_item());
    item = set_default_box_item();
    item.pos[0] = 32; /// Test.
    item.pos[1] = -1; /// Test.
    if (pos)
    {
        item.status.param[0] = 1;
        item.pos[0] = pos[0]; /// Test.
        item.pos[1] = pos[1]; /// Test./
    }
    item.dim[0] = picture->w;
    item.dim[1] = picture->h;
    item.ptr = picture;
    item.type = UI_ITEMTYPE_PICTURE; /// RAW String.
    item.status.active = 1;
    return (item);
}
