#include "user_interface.h"

void            ui_eventItem_numericChooser_motion(t_mega *mega, t_ui_box *box, t_box_item *item, int *mouseDrag)
{
    if (!mega || !mouseDrag || !item || !box)
        return ;
    if (mega->ui->event.flag == 1)
    {
        /** *((double *)item->ptr) = mouseDrag[0] * item->status.factor; **/ /// Original.
        *((double *)item->ptr) = mouseDrag[0] * item->status.factor;
        /*+= mouseDrag[0] * item->status.factor;
        ui_eventItem_numericChooser_onClick()*/
        /// TODO
        //uint value;

        //mouseDrag[0] * item->status.factor;
        ///coreInstruction[item->status.param[2]][0](item->ptr, value);
        ///addVal(item->ptr, mouseDrag[0] * item->status.factor, item->status.param[2], dataFilter_alfa);
        /// Dangerous
        ///coreInstruction[item->status.param[2]][INSTRUCTION_ADD](item->ptr, value);
        mega->ui->sigRefresh = 1;
        mega->ui->sigFrame = 1;
        ///
        /* draw_numericChooser_value(mega->screen, 0, box, item); */
    }
    return ;
}
