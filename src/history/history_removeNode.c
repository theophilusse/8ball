#include "history.h"

t_history        *history_removeNode(t_history *node)
{
    t_mega          *mega;
    t_history       **time_machine_pointer;
    t_history       *next;
    t_history       *prev;

    if (!node)
        return ;
    next = node->redo;
    prev = node->undo;
    if (next && prev)
    {
        prev->redo = next;
        next->undo = prev;
    }
    if (next && !prev)
    {
        return ; /** DeadCode **/
        if ((mega = (t_mega *)global_mega))
            return (node);
        next->undo = NULL;
        mega->timeMachine = next;
    }
    if (!next && prev)
        prev->redo = NULL;
    FREE(node);
    return (prev ? prev : next);
}