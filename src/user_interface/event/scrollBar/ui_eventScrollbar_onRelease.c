#include "user_interface.h"

struct s_ui_event           ui_eventScrollbar_onRelease(t_mega *mega, t_ui_box *box)
{
    struct s_ui_event           event;
    int                         scrollbarHandle;
    int                         relClick[2];

    if (!box || !mega)
        return (ui_setDefaultEvent());
    relClick[0] = mega->mouse.mousePos[0] - box->pos[0];
    relClick[1] = mega->mouse.mousePos[1] - box->pos[1];
    if ((scrollbarHandle = ui_getScrollBarHandle(box, relClick)) != -1) /** Detect Scrollbar onRelease **/
    {
        ///BEEP///
        ///printf("scrollBar on Release :::: scrollBarHandle[%u]\n", scrollbarHandle); ///
        if (mega->ui->event.itemHandle == scrollbarHandle)
        {
            if (scrollbarHandle == 0)
                box->horizontal_bar.fPercent -= 0.1;
            if (scrollbarHandle == 1)
                box->horizontal_bar.fPercent += 0.1;

            ///if (scrollbarHandle == 2)
            if (scrollbarHandle == 5)
                box->vertical_bar.fPercent -= 0.1;
            ///if (scrollbarHandle == 3)
            if (scrollbarHandle == 6)
                box->vertical_bar.fPercent += 0.1;
            ui_clampScrollBarFactor(box); ///
            /** /// Original Original.
                box->horizontal_bar.shift = (uchar)(box->horizontal_bar.fPercent * (float)(box->envDim[0] - box->dim[0])); /// Test
                box->horizontal_bar.shift = (uchar)(box->horizontal_bar.fPercent * (float)(box->envDim[1] - box->dim[1])); /// Test
            */
            /** /// Original.
                box->horizontal_bar.shift = (uchar)(box->horizontal_bar.fPercent * (float)(box->envDim[0] - (box->dim[0] < box->envDim[0] ? box->dim[0] : box->envDim[0]))); /// Test
                box->horizontal_bar.shift = (uchar)(box->horizontal_bar.fPercent * (float)(box->envDim[1] - (box->dim[1] < box->envDim[1] ? box->dim[1] : box->envDim[1]))); /// Test
            */
            if ((scrollbarHandle % 5) == 0 || (scrollbarHandle % 5) == 1)
            {
                ///printf("box->envDim [%u][%u]\n", box->envDim[0], box->envDim[1]); ///
                /*if (box->dim[0] < box->envDim[0])*/
                    box->horizontal_bar.shift = (int)(box->horizontal_bar.fPercent * (float)(box->envDim[0] - box->dim[0])); /// Test
                /*else
                    box->horizontal_bar.shift = 0;
                if (box->dim[1] < box->envDim[1])*/
                    box->vertical_bar.shift = (int)(box->vertical_bar.fPercent * (float)(box->envDim[1] - (box->dim[1] - (39 + 18)))); /// Test
                /*else
                    box->vertical_bar.shift = 0;*/
            }
        }
        mega->ui->sigRefresh = 1;
    }
    else
        event = ui_setDefaultEvent();
    return (event);
}
