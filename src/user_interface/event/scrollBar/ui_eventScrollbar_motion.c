#include "user_interface.h"

static void             ui_staticHorizontalBar(t_ui_box *box, struct s_mouse mouse)
{
    t_ui_scrollbar      *bar;
    int                 relClick[2];
    /*int                 dim[2];*/

    bar = &box->horizontal_bar; //
    relClick[0] = mouse.mousePos[0] - box->pos[0];
    relClick[1] = mouse.mousePos[1] - box->pos[1];
    relClick[0] -= UI_BORDER_WIDTH + 16;
    relClick[1] -= (box->dim[1] - (UI_BORDER_WIDTH + 16));
    /*dim[0] = box->dim[0] - ((16 + 16 + (16)) + UI_BORDER_WIDTH * 2);
    dim[1] = 16;*/
    bar->fPercent = (float)(relClick[0] - 7) / (float)bar->length;
    ui_clampScrollBarFactor(box);
    if (box->dim[0] < box->envDim[0])
        bar->shift = (int)(bar->fPercent * (float)(box->envDim[0] - box->dim[0]));
    else
        bar->shift = 0;
}

static void             ui_staticVerticalBar(t_ui_box *box, struct s_mouse mouse)
{
    t_ui_scrollbar      *bar;
    int                 relClick[2];
    /*int                 dim[2];*/

    bar = &box->vertical_bar; //
    relClick[0] = mouse.mousePos[0] - box->pos[0];
    relClick[1] = mouse.mousePos[1] - box->pos[1];
    relClick[1] -= 39;
    /*dim[0] = 16;
    dim[1] = box->dim[1] - ((16 + 16 + (16)) + UI_BORDER_WIDTH * 3);*/
    bar->fPercent = (float)(relClick[1] - 7) / (float)bar->length;
    ui_clampScrollBarFactor(box); ///
    if (box->dim[1] < box->envDim[1] + (39 + 18))
        bar->shift = (int)(bar->fPercent * (float)(box->envDim[1] - (box->dim[1] - (39 + 18))));
    else
        bar->shift = 0;
}

void            ui_eventScrollbar_motion(t_userInterface *ui, t_ui_box *box, struct s_mouse mouse)
{
    int             scrollbarHandle;

    if (!ui || !box)
        return ;
    scrollbarHandle = (int)ui->event.itemHandle;
    ui->event.itemHandle = (uchar)scrollbarHandle;
    if (scrollbarHandle % 5 == 2 && scrollbarHandle != 255) /*** Motion Scroller ***/
    {
        if (scrollbarHandle < 5) /** X Bar **/
            ui_staticHorizontalBar(box, mouse);
        if (scrollbarHandle >= 5 && scrollbarHandle < 255) /** Y Bar **/
            ui_staticVerticalBar(box, mouse);
    }
    ui->sigRefresh = 1; /// Test
}
