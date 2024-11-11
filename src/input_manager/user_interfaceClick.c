#include "input_manager.h"

int         user_interfaceClick(t_mega *mega, int flg)
{
    int              onClick[2];
    uchar            handle;
    //uint             i;

    if (!mega || !mega->camera || !mega->ui)
        return (1);
    onClick[0] = mega->mouse.onClick[0];
    onClick[1] = mega->mouse.onClick[1];
    ///mega->ui->event.handle = 255; /// Test.
    if (ui_getBoxHandleAt(mega->ui, onClick, &handle) && handle != 255) /** Get Box Handle **/
    {
        mega->ui->event.handle = 0;
        /*** Test ***/
        /*
            onClick[0] -= mega->ui->box[handle].pos[0];
            onClick[1] -= mega->ui->box[handle].pos[1];
        */
        /*** Test ***/
        return (ui_interfaceOnClick(mega, handle, onClick));
    }
    else
    {
        uint            morphoDim[2];
        int             morphoPos[2];
        morphoDim[0] = mega->ui->morpho.surface->w;
        morphoDim[1] = mega->ui->morpho.surface->h;
        morphoPos[0] = (int)mega->ui->morpho.pos[0];
        morphoPos[1] = (int)mega->ui->morpho.pos[1];
        if (mega->ui->morpho.active == 1 && isInZone(onClick, morphoDim, morphoPos))
        {
            if (mega->input_manager[USER_MORPHO_CLICK](mega, 0))
                return (1);
        }
    }
    return (0);
}
