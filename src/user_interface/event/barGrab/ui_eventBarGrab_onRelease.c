#include "user_interface.h"

struct s_ui_event           ui_eventBarGrab_onRelease(t_mega *mega, t_ui_box *box)
{
    struct s_ui_event       event;

    if (!mega || !box)
        return (ui_setDefaultEvent());
    event = ui_setDefaultEvent();
    return (event);
}
