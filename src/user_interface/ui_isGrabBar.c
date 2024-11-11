#include "user_interface.h"

int             ui_isGrabBar(t_ui_box *box, int *onClick)
{
    uint            btnDim[2];
    int             btnPos[2];

    if (!box || !onClick)
        return (0);
    /*btnPos[0] = box->pos[0] + UI_BORDER_WIDTH;
    btnPos[1] = box->pos[1] + (UI_BORDER_WIDTH - 1);*/
    btnPos[0] = 0;
    btnPos[1] = 0;
    btnDim[0] = box->dim[0] - (16 + UI_BORDER_WIDTH);
    btnDim[1] = 16 + UI_BORDER_WIDTH;
    if (isInZone(onClick, btnDim, btnPos))
        return (1);
    return (0);
}
