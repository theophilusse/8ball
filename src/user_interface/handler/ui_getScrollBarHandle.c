#include "user_interface.h"

static int      ui_scrollBarIsActive(t_ui_box *box, struct s_ui_scrollbar bar)
{
    if (!box || bar.axis >= 2)
        return (0);
    if (box->dim[bar.axis] < box->envDim[bar.axis] + (bar.axis == 1 ? 39 + 16 : 0))
        return (1);
    return (0);
}

int             ui_getScrollBarHandle(t_ui_box *box, int *onClick)
{
    int         relClick[2];
    int         subClick[2];
    uint        dim[2];
    uint        subDim[2];
    int         subPos[2];
    int         pos[2];
    int         scrollbarHandle;

    if (!box || !onClick)
        return (-1);
    /*relClick[0] = onClick[0] - box->pos[0];
    relClick[1] = onClick[1] - box->pos[1];*/
    relClick[0] = onClick[0];
    relClick[1] = onClick[1];
    if (ui_scrollBarIsActive(box, box->horizontal_bar)) /** X bar **/
    {
        scrollbarHandle = 0;
        pos[0] = UI_BORDER_WIDTH;
        pos[1] = (box->dim[1] - (UI_BORDER_WIDTH + 16));
        dim[0] = box->dim[0] - (16 + UI_BORDER_WIDTH * 2);
        dim[1] = 16;
        if (isInZone(relClick, dim, pos))
        {
            subClick[0] = relClick[0] - pos[0];
            subClick[1] = relClick[1] - pos[1];
            subDim[0] = 16;
            subDim[1] = 16;
            subPos[0] = 0;
            subPos[1] = 0;
            if (isInZone(subClick, subDim, subPos)) /// Left Button
                return (scrollbarHandle);
            subPos[0] = (int)dim[0] - 16;
            subPos[1] = 0;
            if (isInZone(subClick, subDim, subPos))
                return (scrollbarHandle + 1);
            /// /// /// /// Testing.
            box->horizontal_bar.length = dim[0] - (16 + 16 + 16); /// Testing.
            subPos[0] = (box->horizontal_bar.length * box->horizontal_bar.fPercent) + 16;
            subPos[1] = 0;
            if (isInZone(subClick, subDim, subPos))
                return (scrollbarHandle + 2);
        }
    }
    if (ui_scrollBarIsActive(box, box->vertical_bar)) /** Y bar **/
    {
        scrollbarHandle = 5;
        pos[0] = (box->dim[0] - (UI_BORDER_WIDTH + 16));
        pos[1] = UI_BORDER_WIDTH + (int)box->font->dim;
        ///pos[1] = ;
        dim[0] = 16;
        ///dim[1] = box->dim[1] - (16 + 16 + UI_BORDER_WIDTH * 2);
        dim[1] = box->dim[1] - (16 + 16 + UI_BORDER_WIDTH * 2);
        if (isInZone(relClick, dim, pos))
        {
            subClick[0] = relClick[0] - pos[0];
            subClick[1] = relClick[1] - pos[1];
            subDim[0] = 16;
            subDim[1] = 16;
            subPos[0] = 0;
            subPos[1] = 0;
            if (isInZone(subClick, subDim, subPos)) /// Up Button
                return (scrollbarHandle);
            subPos[0] = 0;
            subPos[1] = (int)dim[1] - 16;
            if (isInZone(subClick, subDim, subPos))
                return (scrollbarHandle + 1);
            /// /// /// /// Testing.
            ///box->vertical_bar.length = dim[1]; /// Testing.
            ///subPos[1] = 16;
            ///subClick[1] -= 16;
            ///box->vertical_bar.length = dim[1] + 16; /// Testing.
            box->vertical_bar.length = dim[1] - (16 + 16 + 16); /// Testing.
            printf("Uint.VrtBar.Length [%u]\n", box->vertical_bar.length); ///
            subClick[0] = subClick[0];
            subClick[1] = subClick[1] - 16;
            subDim[0] = 16;
            subDim[1] = 16;
            subPos[0] = 0;
            subPos[1] = (box->vertical_bar.length * box->vertical_bar.fPercent);
            if (isInZone(subClick, subDim, subPos))
                return (scrollbarHandle + 2);
            /*
            ///ui_getScrollButtonPos(box, 1, subPos);
            ///subClick[1] -= 16;
            subClick[1] += 16;
            ///subPos[0] = 0;
            subPos[1] = (int)(box->vertical_bar.fPercent * (float)box->vertical_bar.length);/// + (2*UI_BORDER_WIDTH + 32);
            printf("SubPos at[%u][%u]\n", subPos[0], subPos[1]);
            if (isInZone(subClick, subDim, subPos))
                return (scrollbarHandle + 2);*/

            /*
            box->vertical_bar.length = dim[1] - (16 + 16); /// Testing.
            ///box->vertical_bar.length = dim[1] - (16 + 16 + 16); /// Testing.
            ///subPos[0] = (int)dim[0] - (16 + UI_BORDER_WIDTH);
            subPos[0] = 0;///(int)dim[0] - (16 + UI_BORDER_WIDTH);
            ///subPos[1] = (box->vertical_bar.length * box->vertical_bar.fPercent) + (16 + UI_BORDER_WIDTH);
            subPos[1] = (box->vertical_bar.length * box->vertical_bar.fPercent);
            if (isInZone(subClick, subDim, subPos))
                return (scrollbarHandle + 2);
            */

        }
    }
    return (-1);
}
