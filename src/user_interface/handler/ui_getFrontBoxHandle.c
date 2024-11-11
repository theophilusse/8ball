#include "user_interface.h"

/**
 ** ui_getFrontBoxHandle
 **
 ** ui: userInterface pointer.
 ** minHandle: 255 by default.
 ** Return: Box handle with minimum zIndex value. (expect zIndex == 0).
 **
**/
uchar               ui_getFrontBoxHandle(t_userInterface *ui)
{
    uint            i;

    if (!ui)
        return (UI_BOX_COUNT);
    i = -1;
    while (++i < UI_BOX_COUNT)
    {
        ///if (ui->box[i].z_index < min_zIndex && //
        /*if (ui->box[i].z_index != 255 && ui->box[i].z_index < min_zIndex &&
            (minHandle == 255 || (minHandle != 255 && minHandle < ui->box[i].z_index)))*/
        if (ui->box[i].active != 0)
        {
            /*min_zIndex = ui->box[i].z_index;*/
            return (i);
        }
    }
    return (UI_BOX_COUNT);
}
