#include "user_interface.h"

struct s_box_item           ui_newItemSimpleButton(SDL_Surface *surf, const char *name, int (*fptr)(void *, int), int *pos, uint *dim)
{
    t_simple_button             *button;
    struct s_box_item           item;

    if (!name)
        return (set_default_box_item());
    if (!(button = (t_simple_button *)ALLOC(sizeof(struct s_simple_button))))
        return (set_default_box_item());
    button->srf = NULL;
    button->txt[0] = '\0';
    strncat(button->txt, (const char *)name, strlen(name));
    item.pos[0] = 72;
    item.pos[1] = -1;
    if (pos)
    {
        item.pos[0] = pos[0];
        item.pos[1] = pos[1];
    }
    /*else
    {
        item.status.param[0] = 1;
    }*/
    item.dim[0] = dim ? dim[0] : 64;
    item.dim[1] = dim ? dim[1] : 24;
    item.blockSize = 1;
    item.dataSize = sizeof(struct s_simple_button);
    item.status.active = 1;
    item.ptr = NULL;
    button->srf = surf; /// Debug Test.
    button->fptr = fptr ? fptr : ui_functionTest;
    item.type = UI_ITEMTYPE_SIMPLE_BUTTON;
    item.ptr = button;
    return (item);
};
