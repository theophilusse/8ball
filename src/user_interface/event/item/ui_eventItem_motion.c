#include "user_interface.h"

void            ui_eventItem_motion(t_mega *mega, t_userInterface *ui, t_ui_box *box, struct s_mouse mouse)
{
    t_box_content       *content;
    t_box_item          *item;
    int             itmPos[2];
    int             relClick[2];
    int             swap;

    if (!box)
        return ;
    if (!(content = box->content) || ui->event.itemHandle >= content->n_item)
        return ;
    relClick[0] = mouse.mousePos[0] - box->pos[0];
    relClick[1] = mouse.mousePos[1] - box->pos[1];
    item = &content->item[ui->event.itemHandle];
    itmPos[0] = item->pos[0] - box->horizontal_bar.shift;
    itmPos[1] = item->pos[1] - box->vertical_bar.shift;
    /*relClick[0] -= item->pos[0];
    relClick[1] -= item->pos[1];*/
    relClick[0] -= itmPos[0];
    relClick[1] -= itmPos[1];
    /// Test ///
    /*relClick[0] += box->horizontal_bar.shift;
    relClick[1] += box->vertical_bar.shift;*/
    /*relClick[0] -= box->horizontal_bar.shift;
    relClick[1] -= box->vertical_bar.shift;*/
    /// Test ///
    switch (item->type)
    {
        case UI_ITEMTYPE_STRING: /** Select Text **/
        {
            ui_eventItem_string_motion(mega, ui, item, relClick);
            break;
        }
        case UI_ITEMTYPE_SIMPLE_BUTTON:
        {
            ui_eventItem_simpleButton_motion();
            break;
        }
        case UI_ITEMTYPE_PICTURE:
        {
            ui_eventItem_picture_motion();
        }
        case UI_ITEMTYPE_NUMERICCHOOSER:
        {
            /*ui_eventItem_numericChooser_motion(mega, mega->ui, item, mouse.mouseDrag);*/ /// Old.
            ///ui_eventItem_numericChooser_motion(mega, box, item, mouse.mouseDrag);
            ui_eventItem_numericChooser_motion(mega, box, item, mouse.mouseRle);
            ///static void ui_eventItem_numericChooser_motion(t_mega *mega, t_ui_box *box, t_box_item *item, int *mouseDrag)
        }
        default: { break; }
    }
}
