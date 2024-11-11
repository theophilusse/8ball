#include "user_interface.h"

struct s_ui_event            ui_interfaceOnRelease(t_mega *mega)
{
    t_ui_box                *box;
    struct s_ui_event       event;

    box = NULL;
    if (mega->ui->event.type != UI_EVENT_NONE)///
    {
        event = mega->ui->event;
        ///printf("Event.Handle ::: *[%u]/[%u]\n", event.handle, mega->ui->event.handle);///
        if (event.handle < UI_BOX_COUNT && event.handle != 255)
            box = &mega->ui->box[event.handle];
        SDL_SetCursor(mega->ui->cursor[UI_CURSOR_ARROW]);
        switch (event.type)
        {
            case UI_EVENT_BOXKILL:
            {
                /*** Simple Button onRelease ***/
                event = ui_eventBoxKill_onRelease(mega, box);
                break;
            }
            case UI_EVENT_ITEMCLICK:
            {
                event = ui_eventItem_onRelease(mega, box);
                break;
            }
            case UI_EVENT_BARGRAB:
            {
                event = ui_eventBarGrab_onRelease(mega, box);
                break;
            }
            case UI_EVENT_SCROLLBAR:
            {
                event = ui_eventScrollbar_onRelease(mega, box);
                break;
            }
            case UI_EVENT_BOXRESIZE:
            {
                if (!box)
                    break;
                event = ui_eventBoxSide_onRelease(mega, box);
                break;
            }
            default : { break; }
        }
    }
    else
    {
        uchar           dbgCursorOnRelease;
        if ((dbgCursorOnRelease = ui_getFrontBoxHandle(mega->ui)) < UI_BOX_COUNT)
            event.handle = dbgCursorOnRelease;
    }
    return (event);
}
