#include "user_interface.h"

struct s_ui_event       ui_eventItem_simpleButton_onRelease(t_mega *mega, t_ui_box *box, t_box_item *item, int *onClick)
{
    int                     itmPos[2];
    t_simple_button         *button;

    if ((button = item->ptr))
    {
        itmPos[0] = item->pos[0] - box->horizontal_bar.shift;
        itmPos[1] = item->pos[1] - box->vertical_bar.shift;
        printf("ONRELEASE\n\tL-> onClick[%d][%d]\n", onClick[0], onClick[1]);
        if (isInZone(onClick, item->dim, itmPos))
            if (button->fptr((void *)mega, 0))
                printf("Button: ERROR\n");
        mega->ui->sigRefresh = 1;
    }
    return (ui_setDefaultEvent());
}
