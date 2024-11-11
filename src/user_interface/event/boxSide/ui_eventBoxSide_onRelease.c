#include "user_interface.h"

struct s_ui_event           ui_eventBoxSide_onRelease(t_mega *mega, t_ui_box *box)
{
    struct s_ui_event       event;

    event = ui_setDefaultEvent();
    return (event);
}
