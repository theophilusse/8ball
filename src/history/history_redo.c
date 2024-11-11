#include "history.h"

t_history               *history_redo(t_mega *mega, t_history *timeMachine)
{
    t_history           *redo;
    uint                    i;
    uint                    debugAsync;

    if (!mega || !timeMachine)
        return (NULL);
    if (!(redo = timeMachine->redo)) /* Nothing to redo, return last node*/
    {
        BEEP
        return (timeMachine);
    }
    /**
        history_display(redo); /// Debug
    */

    /*
        if (timeMachine && history_isAsync(timeMachine->param.type))
            debugAsync = 1;
        else
            debugAsync = 0;
    */
    /** Redo action **/
    ///if (history_typeSelection(redo->param.type)) /** TYPE : Selection **/
    if (redo->param.type != HISTORY_IDLE) /** TYPE : Selection **/
    {
        switch (redo->param.type)
        {
            case HISTORY_RELINK_SELECTION:
            {
                printf("RELINK\n"); /*** DEBUG ***/
                /** history_relinkSelection(mega, redo, 1); **/
                BEEP_WARNING
                flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = copy_selection(redo->param.selection);
                break;
            }
            case HISTORY_DESELECT_ALL:
            {
                printf("HISTORY_DESELECT_ALL\n");
                flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = NULL;
            }
            case HISTORY_SELECT:
            {
                printf("SELECT\n"); /*** DEBUG ***/
                ///mega->selectStack = push_selection(redo->param.vrt, NULL);
                if (!selection_isSelected(redo->param.vrt.ptr, mega->selectStack)) // Test
                    mega->selectStack = push_selection(redo->param.vrt, mega->selectStack); // Test
                break;
            }
            case HISTORY_SELECT_UNIQUE: /** Seems to works **/
            {
                printf("SELECT UNIQUE\n"); /*** DEBUG ***/
                flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = push_selection(redo->param.vrt, NULL);
                break;
            }
            case HISTORY_DESELECT:
            {
                printf("DESELECT\n"); /*** DEBUG ***/
                ///mega->selectStack = push_selection(redo->param.vrt, mega->selectStack); /// TEST
                mega->selectStack = selection_deselectPtr(mega->selectStack, redo->param.vrt.ptr);
                break;
            }
            case HISTORY_TRANSFORM:
            {
                history_toolTransform(mega, redo->param.vec, 0);
                break;
            }
            case HISTORY_SCALE:
            {
                printf("HISTORY_SCALE"); // Work.
                history_toolScale(mega, redo, 0);
                break;
            }
            case HISTORY_ROTATE:
            {
                printf("HISTORY_ROTATE"); // Work.
                history_toolRotate(mega, redo, 0);
                break;
            }
            case HISTORY_RESIZE:
            {
                printf("HISTORY_ROTATE"); // Work.
                history_toolResize(mega, redo, 0);
                break;
            }
            case HISTORY_SET_VALUE:
            {
                printf("HISTORY_SET_VALUE\n"); // Work.
                history_setVal(mega, redo, 0);
                break;
            }
            default: { printf("Redo Type : [%u]\n", redo->param.type); }
        }
    }
    mega->tool[mega->currentTool].hud.active = mega->selectStack ? 1 : 0;
    selection_center(mega->selectStack, &mega->tool[mega->currentTool].hud.org);
    return (redo);
}
