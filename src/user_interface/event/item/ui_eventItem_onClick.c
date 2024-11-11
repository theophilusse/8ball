#include "user_interface.h"

int             ui_eventItem_onClick(t_mega *mega, t_ui_box *box, uchar boxHandle, uchar itemHandle, uchar itemType, int *onClick)
{
    t_box_item      *item;
    int         itmPos[2];
    int         relClick[2];

    /*relClick[0] = onClick[0] - box->pos[0];
    relClick[1] = onClick[1] - box->pos[1];*/
    if (!box->content || boxHandle == 255 || itemHandle == 255)
        return (0);
    item = &box->content->item[itemHandle];
    /*relClick[0] = onClick[0] - box->content->item[itemHandle].pos[0];
    relClick[1] = onClick[1] - box->content->item[itemHandle].pos[1];*/
    /// Test ///
    /*relClick[0] += box->horizontal_bar.shift;
    relClick[1] += box->vertical_bar.shift;*/
    /*relClick[0] -= box->horizontal_bar.shift;
    relClick[1] -= box->vertical_bar.shift;*/
    /// Test ///
    ///*//
    /*relClick[0] += box->horizontal_bar.shift;
    relClick[1] += box->vertical_bar.shift;*/
    //*/
    ///printf("itemIndex[%u] Type: [%u]\n", itemHandle, itemType); /** Item Handle **/
    ///printf("ONCLICK :: [%d][%d]\n", onClick[0], onClick[1]); /** Item Handle **/
    ///printf("RELCLICK :: [%d][%d]\n", relClick[0], relClick[1]); /** Item Handle **/
    ///printf("ITEMPOS :: [%d][%d]\n", box->content->item[itemHandle].pos[0], box->content->item[itemHandle].pos[1]); /** Item Handle **/
    mega->ui->event = ui_setEvent(UI_EVENT_ITEMCLICK, boxHandle);
    mega->ui->event.itemHandle = itemHandle;
    switch (itemType)
    {
        case UI_ITEMTYPE_STRING:
        {
            /// Test.
            ui_eventItem_string_onClick(mega, box, item, onClick);
            break;
        }
        case UI_ITEMTYPE_SIMPLE_BUTTON:
        {
            ui_eventItem_simpleButton_onClick(mega, box, itemHandle, onClick);
            break;
        }
        case UI_ITEMTYPE_PICTURE:
        {
            ui_eventItem_picture_onClick();
            break;
        }
        case UI_ITEMTYPE_NUMERICCHOOSER:
        {
            ui_eventItem_numericChooser_onClick(mega, box, itemHandle, onClick);
            break;
        }
    }
    return (0);
}
