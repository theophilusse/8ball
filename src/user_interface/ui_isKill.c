#include "user_interface.h"

int             ui_isKill(t_ui_box *box, int *onClick)
{
    uint            btnDim[2];
    int             btnPos[2];

    if (!box || !onClick)
        return (0);
    btnPos[0] = (int)box->dim[0];//box->pos[0] + (box->dim[0] - 20);
    btnPos[0] -= 16 + UI_BORDER_WIDTH;//box->pos[0] + (box->dim[0] - 20);
    btnPos[1] = (UI_BORDER_WIDTH - 1);
    btnDim[0] = 16;
    btnDim[1] = 16;
    if (isInZone(onClick, btnDim, btnPos))
        return (1);
    return (0);
}
