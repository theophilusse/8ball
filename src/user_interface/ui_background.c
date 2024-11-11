#include "user_interface.h"

void 			ui_background(t_userInterface *ui, uchar handle, uchar active)
{
    struct s_ui_box swpBox;
    struct s_ui_box bufBox[UI_BOX_COUNT];
    t_ui_box        *box;
    uchar           cpyFrom;
    uint            cpySz;

	if (!ui || handle >= UI_BOX_COUNT || !(box = &ui->box[0]))
		return ;
    cpyFrom = handle + 1;
    ///cpySz = ui->boxCount - (cpyFrom - 1);
    cpySz = ui->boxCount - cpyFrom;
    swpBox = ui->box[handle];
    /*if (setActive == 1)
        swpBox.active = swpBox.active == 1 ? 0 : 1;*/
    if (swpBox.active == 1 && active == 0)
        ui->boxCount--;
    swpBox.active = active;
    /*swpBox.z_index = 1;*/
    memcpy((void *)(bufBox) , (void *)(&box[cpyFrom]) , (size_t)(sizeof(struct s_ui_box) * cpySz));
    box[handle + cpySz] = swpBox;
    memcpy( (void *)(&box[handle]) , (void *)(bufBox) , (size_t)(sizeof(struct s_ui_box) * cpySz));
    /*old_handle = handle;*/
    ui->sigRefresh = 1;
    return ;
}
