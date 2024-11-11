#include "user_interface.h"

struct s_ui_event            ui_eventItem_onRelease(t_mega *mega, t_ui_box *box)
{
    struct s_ui_event   event;
    t_box_content       *content;
    t_box_item          *item;
    int                 relClick[2];

    if (!box || !(content = box->content) || mega->ui->event.itemHandle >= content->n_item)
        return (ui_setDefaultEvent());
    event = mega->ui->event;
    item = &content->item[mega->ui->event.itemHandle];
    relClick[0] = mega->mouse.mousePos[0] - box->pos[0];
    relClick[1] = mega->mouse.mousePos[1] - box->pos[1];
    switch (item->type)
    {
        case UI_ITEMTYPE_STRING: /** Select Text **/
        {
            event = ui_eventItem_string_onRelease(mega, box, item, event, relClick);
            break;
        }
        case UI_ITEMTYPE_SIMPLE_BUTTON:
        {
            event = ui_eventItem_simpleButton_onRelease(mega, box, item, relClick);
            break;
        }
        case UI_ITEMTYPE_PICTURE:
        {
            event = ui_eventItem_picture_onRelease();
            break;
        }
        case UI_ITEMTYPE_NUMERICCHOOSER:
        {
            event = ui_eventItem_numericChooser_onRelease(mega, box, item, relClick);
            break;
        }
        default: { break; }
    }
    return (event);
}
