#include "user_interface.h"

int             ui_interfaceOnClick(t_mega *mega, uchar handle, int *onClick)
{
    t_ui_box        *box;
    uchar            sideGrab;
    uchar            itemHandle;
    uchar            itemType;
    int              scrollbarHandle;
    int              relClick[2];

    if (!((t_ui_box *)(box = &mega->ui->box[handle]))->content) /** Grab Box **/
        return (0);
    relClick[0] = onClick[0] - box->pos[0];
    relClick[1] = onClick[1] - box->pos[1];
    if (ui_isKill(box, relClick)) /** Detect Kill Button **/
    {
        DEBUG ///
        return (ui_eventBoxKill_onClick(mega, handle));
    }
    if (ui_isResize(box, relClick, &sideGrab))
    {
        DEBUG ///
        return (ui_eventBoxSide_onClick(mega, handle, sideGrab));
    }
    if ((scrollbarHandle = ui_getScrollBarHandle(box, relClick)) != -1) /** Detect Scrollbar Click **/
    {
        DEBUG ///
        return (ui_eventScrollbar_onClick(mega, handle, (uchar)scrollbarHandle));
    }
    if (ui_isGrabBar(box, relClick)) /** Detect Upper Bar Click **/
    {
        DEBUG ///
        /// active = 2 ??
        return (ui_eventBarGrab_onClick(mega, handle));
    }
    if ((itemType = ui_getItemHandleAt(mega->ui, box, relClick, &itemHandle)) != UI_ITEMTYPE_EMPTY) /** Get Item Handle **/
    {
        DEBUG ///
        return (ui_eventItem_onClick(mega, box, handle, itemHandle, itemType, relClick));
    }
    return (0);
}
