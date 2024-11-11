#include "user_interface.h"

struct s_ui_event       ui_setDefaultEvent(void)
{
    struct s_ui_event       event;

    event.flag = 0;
    event.handle = 255;
    event.itemHandle = 255;
    event.ptr = NULL;
    event.pIndex[0] = -1;
    event.pIndex[1] = -1;
    event.type = UI_EVENT_NONE;
    return (event);
}

struct s_ui_event       ui_setEvent(uchar type, uchar handle)
{
    struct s_ui_event       event;

    event = ui_setDefaultEvent();
    event.type = type;
    event.flag = 0;
    event.handle = handle;
    event.ptr = NULL;
    return (event);
}
