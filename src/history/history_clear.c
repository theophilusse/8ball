#include "history.h"

void            history_clear(t_history *timeMachine)
{
    t_history           *del;

    if (!timeMachine)
        return ;
    while (timeMachine)
    {
        del = timeMachine;
        if (del->param.selection)
            flush_selection(del->param.selection, NULL, 0, NULL); ///
        timeMachine = timeMachine->redo;
        FREE(del);
    }
}
