#include "user_interface.h"

/** A Vérifier / Clean **/
int                 ui_getBoxHandle_byTitle(t_userInterface *ui, const char *boxTitle, uchar *handle)
{
    uint            i;
    //int             k;
    t_ui_box        *box;

    if (handle)
        *handle = -1;
    if (!ui)
        return (0);
    //k = -1;
    i = -1;
    ///while (++i < ui->boxCount)
    while (++i < UI_BOX_COUNT)
        if ((box = &ui->box[i]) && strcmp((const char *)box->title, (char *)boxTitle) == 0)
        {
            *handle = i;
            return (1);
        }
    return (0);
}

/** A Vérifier / Clean **/
int                 ui_getBoxHandleAt(t_userInterface *ui, int *onClick, uchar *handle)
{
    uint            i;
    //uint            min_z_index[2];
    int             k;
    t_ui_box        *box;

    if (handle)
        *handle = -1;
    if (!ui || !onClick || onClick[0] < 0 || onClick[1] < 0)
        return (0);
    //min_z_index[0] = 255;
    k = -1;
    i = -1;
    while (++i < ui->boxCount)
        if ((box = &ui->box[i]) && box->active != 0)
            if (isInZone(onClick, box->dim, box->pos))
                ///if (box->z_index != 255 && box->z_index < (uchar)min_z_index[0])
                {
                    break;
                    /*min_z_index[0] = (int)box->z_index;
                    min_z_index[1] = i;*/
                }
    if ((k = (int)i) < ui->boxCount && handle) /** Change Window Focus **/
    {
        ui_foreground(ui, k, 1);///
        *handle = 0;
        /*uchar        old_zIndex;

        old_zIndex = ui->box[k].z_index;
        i = -1;
        while (++i < UI_BOX_COUNT)
        {
            if (ui->box[i].z_index != 255)
            ///if (box[i].z_index != 255 && box[i].z_index < old_zIndex)
                ui->box[i].z_index++;
        }
        ui->box[k].z_index = 0;*/
        return (1);
    }
    return (0);
}
