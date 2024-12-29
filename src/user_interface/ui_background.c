#include "user_interface.h"

void 			ui_background(t_userInterface *ui, uchar handle, uchar active)
{
    struct s_ui_box swpBox;
    struct s_ui_box bufBox[UI_BOX_COUNT];
    t_ui_box        *box;
    uchar           cpyFrom;
    uint            cpySz;

    DEBUG //
	if (!ui || handle >= UI_BOX_COUNT || !(box = &ui->box[0]))
		return ;
    DEBUG //
    cpyFrom = handle + 1;
    ///cpySz = ui->boxCount - (cpyFrom - 1);
    cpySz = ui->boxCount - cpyFrom;
    DEBUG //
    swpBox = ui->box[handle];
    DEBUG //
    /*if (setActive == 1)
        swpBox.active = swpBox.active == 1 ? 0 : 1;*/
    DEBUG //
    if (swpBox.active == 1 && active == 0)
        ui->boxCount--;
    DEBUG //
    swpBox.active = active;
    DEBUG //
    /*swpBox.z_index = 1;*/
    /// CRASH TODO
    memcpy((void *)(bufBox) , (void *)(&box[cpyFrom]) , (size_t)(sizeof(struct s_ui_box) * cpySz));
    DEBUG //
    box[handle + cpySz] = swpBox;
    DEBUG //
    memcpy( (void *)(&box[handle]) , (void *)(bufBox) , (size_t)(sizeof(struct s_ui_box) * cpySz));
    DEBUG //
    /*old_handle = handle;*/
    ui->sigRefresh = 1;
    DEBUG //
    return ;
}
