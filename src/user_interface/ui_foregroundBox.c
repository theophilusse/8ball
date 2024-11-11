#include "user_interface.h"

/*** DONT USE : see ui_swapPos.c ***/
void                    ui_foregroundAll(t_userInterface *ui, uchar handle) /** Used When Box Is Swapped Away **/
{
    uint            i;
    t_ui_box        *box;

    if (!ui || handle > UI_BOX_COUNT || !(box = &ui->box[0]))
        return ;
    i = -1;
    /*
    while (++i < UI_BOX_COUNT)
        if (box[i].z_index != 255) /// Foreach visible box
            box[i].z_index--; /// Decrease Z-Index
            */
    ui->sigRefresh = 1; /** Refresh UI **/
}

/*** DONT USE : see ui_swapPos.c ***/
void                    ui_foreground(t_userInterface *ui, uchar handle, uchar active)
{
    uint            i;
    t_ui_box        *box;
    struct s_ui_box swpBox;
    struct s_ui_box bufBox[UI_BOX_COUNT];

    if (!ui || handle > UI_BOX_COUNT || !(box = &ui->box[0]))
        return ;
    ///box[handle].active = box[handle].active == 1 ? 0 : 1;
    ///box[handle].z_index = 0;
    /** Stack POP. **/
    swpBox = ui->box[handle];
    /*if (setActive == 1)
        swpBox.active = swpBox.active == 1 ? 0 : 1;
        */
    if (swpBox.active == 0 && active == 1)
        ui->boxCount++;
    swpBox.active = active;
    /*swpBox.z_index = 1;*/
    memcpy((void *)(bufBox) , (void *)(&box[0]) , (size_t)(sizeof(struct s_ui_box) * handle));
    memcpy((void *)(&box[1]) , (void *)(bufBox) , (size_t)(sizeof(struct s_ui_box) * handle));
    box[0] = swpBox;

    /*old_handle = handle;*/
    ui->sigRefresh = 1;
    return ;
    /*
    i = -1;
    while (++i < UI_BOX_COUNT)
        if (box[i].z_index != 255)
            box[i].z_index++;
    box[handle].z_index = 0;
    ui->sigRefresh = 1;
    */
}
