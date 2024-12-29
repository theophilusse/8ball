#include "history.h"

t_history               *history_undo(t_mega *mega, t_history *timeMachine)
{
    t_history             *undo;
    uint                  i;
    uint                    debugAsync;

    if (!mega || !timeMachine)
        return (NULL);
    if (!(undo = timeMachine->undo))
    {
        BEEP
        return (timeMachine);
    }
    /**
        history_display(undo); /// Debug
    */

    if (timeMachine && history_isAsync(timeMachine->param.type))
        debugAsync = 1;
    else
        debugAsync = 0;
    if (timeMachine->param.type == 3) /** Test: DESELECT **/
    {
        // Then Select
        mega->selectStack = push_selection(timeMachine->param.vrt, mega->selectStack); //
    }
    if (debugAsync == 1)
    {
        BEEP_WARNING /// Debug.
        switch (timeMachine->param.type)
        {
            case HISTORY_TRANSFORM:
            {
                printf("HISTORY_TRANSFORM"); // Work.
                history_toolTransform(mega, timeMachine->param.vec, 1);
                break;
            }
            case HISTORY_SCALE:
            {
                printf("HISTORY_SCALE"); // Work.
                history_toolScale(mega, timeMachine, 1);
                break;
            }
            case HISTORY_ROTATE:
            {
                printf("HISTORY_ROTATE"); // Work.
                history_toolRotate(mega, timeMachine, 1);
                break;
            }
            case HISTORY_RESIZE:
            {
                printf("HISTORY_RESIZE"); // Work.
                history_toolResize(mega, timeMachine, 1);
                break;
            }
            case HISTORY_SELECT_UNIQUE:
            {
                printf("SELECT_UNIQUE\n");
                flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = copy_selection(timeMachine->param.selection);
                //mega->selectStack = NULL;
                //mega->selectStack = push_selection(undo->param.vrt, mega->selectStack);
                ///mega->selectStack = NULL;
                ///selection_deselectPtr(mega->selectStack, undo->param.vrt.ptr); /// This bug
                break;
            }
            case HISTORY_DESELECT:
            {
                printf("DESELECT !\n"); /*** DEBUG ***/
                /*if (selection_isSelected(undo->param.vrt.ptr, mega->selectStack))
                    BEEP_WARNING*/
                    //selection_deselectPtr(mega->selectStack, undo->param.vrt.ptr);
                break ; // Debug.
                //mega->selectStack = push_selection(undo->param.vrt, mega->selectStack);
                //mega->selectStack = push_selection(timeMachine->param.vrt, mega->selectStack); // Org
                ///mega->selectStack = selection_deselectPtr(mega->selectStack, undo->param.vrt.ptr);
                break;
            }
            case HISTORY_DESELECT_ALL: /// SELECT: Type A ; Select/Deselct All vertices
            {
                printf("HISTORY_DESELECT_ALL\n"); // Work.
                history_selectionRelink(mega, timeMachine, 1);
                break;
            }
            case HISTORY_SET_VALUE:
            {
                printf("HISTORY_SET_VALUE\n");
                history_setVal(mega, timeMachine, 1);
                break;
            }
            default: { printf("Undo Type [ASYNC] : [%u]\n", timeMachine->param.type); break; }
        }
    }
    /** Revese action **/
    if (history_typeSelection(undo->param.type) && debugAsync == 0 /*Test*/) /** TYPE : Selection **/
    {
        switch (undo->param.type)
        {
            case HISTORY_RELINK_SELECTION: /// SELECT: Type A ; Select/Deselct All vertices
            {
                printf("RELINK SELECTION\n"); /*** WORK ? ***/
                history_selectionRelink(mega, undo, 1);
                break;
            }
            /*case HISTORY_DESELECT_ALL: /// SELECT: Type A ; Select/Deselct All vertices
            {
                printf("HISTORY_DESELECT_ALL\n"); //WORK ?
                history_selectionRelink(mega, undo, 1);
                break;
            }*/
            case HISTORY_SELECT:
            {
                printf("SELECT\n"); /*** DEBUG ***/
                if (undo->redo /*** ASYNC ***/
                    && (undo->redo->param.type == HISTORY_SELECT || undo->redo->param.type == HISTORY_SELECT_UNIQUE))
                    mega->selectStack = push_selection(undo->redo->param.vrt, mega->selectStack);
                else
                {
                    if (undo->redo /*** ASYNC ***/
                        && (undo->redo->param.type == HISTORY_RELINK_SELECTION || undo->redo->param.type == HISTORY_DESELECT_ALL))
                    {
                        ///mega->selectStack = push_selection(undo->param.vrt, mega->selectStack); /// Test
                        flush_selection(mega->selectStack, NULL, 0, NULL);
                        mega->selectStack = copy_selection(undo->redo->param.selection); /// Test
                        ///history_relinkSelection(mega, undo, 1);
                    }
                }
                break;
            }
            /*case HISTORY_SELECT_UNIQUE: /// Buggin' first time !!!
            {
                printf("SELECT_UNIQUE\n"); /// GOOD ? BUG AFTER TRANSFORM
                flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = copy_selection(undo->param.selection);
                break;
            }*/
            default: { printf("Undo Type : [%u]\n", undo->param.type); }
        }
    }
    mega->tool[mega->currentTool].hud.active = mega->selectStack ? 1 : 0;
    selection_center(mega->selectStack, &mega->tool[mega->currentTool].hud.org);
    return (undo);
}
