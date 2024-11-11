#include "input_manager.h"

int      isInUI(t_userInterface *ui, int *onClick)
{
    t_ui_box        *box;
    uint            morphoDim[2]; ///
    int             morphoPos[2]; ///
    uint            i;

    if (!ui || !(box = &ui->box[0]) ||
        !onClick || onClick[0] < 0 || onClick[1] < 0)
        return (0);
    i = -1;
    while (++i < UI_BOX_COUNT)
    {
        if (box->active != 0 && isInZone(onClick, box->dim, box->pos))
            return (1);
        box++;
    }
    /** Morpho. **/
    if (ui->morpho.active == 1)
    {
        if (!ui->morpho.surface)
            return (0);
        morphoDim[0] = ui->morpho.surface->w;
        morphoDim[1] = ui->morpho.surface->h;
        morphoPos[0] = (int)ui->morpho.pos[0];
        morphoPos[1] = (int)ui->morpho.pos[1];
        /*onClick[0] >= ui->morpho.pos[0] &&
        onClick[1] >= ui->morpho.pos[1])*/
        if (isInZone(onClick, morphoDim, morphoPos))
            return (1);
    }
    /** Morpho **/
    return (0);
}

int             user_onLeftClick(t_mega *mega, int flg)
{
    uint            k;
    int             ax;
    int             ay;


    if (!mega || !mega->viewport)
        return (1);
    ////SDL_GetMouseState(&mega->mouse.mouseRelative[0], &mega->mouse.mouseRelative[1]);
    /// Left Click Down
    /** Need to implement multi window **/
    int             handle;

    /*
        ui_isClick(mega->ui, mega->mouse.onClick, &handle); /// Temp
        printf("Handle is : %d\n", handle);
    */
    ///mega->ui->sigRefresh = 1;
    if (isInCanva(mega->viewport, &mega->mouse.onClick[0], &mega->mouse.onClick[1], 1))
    {
        /** /// Get relative click
        mega->mouse.onClick[0] -= mega->viewport.clip_rect.x;
        mega->mouse.onClick[1] -= mega->viewport.clip_rect.y;
        **/
        if (mega->ui->active == 1
            && isInUI(mega->ui, mega->mouse.onClick)) /*** User Interface Zone ***/
        {
            /// Get relative click
            if (mega->input_manager[USER_INTERFACE_CLICK](mega, 0))
                return (1);
            return (0);
        }
        else if (mega->input_manager[USER_CANVA_CLICK](mega, 0)) /*** User Canva Zone ***/
            return (1);
    }
    return (0);
}
