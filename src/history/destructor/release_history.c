#include "history.h"

void            release_history(t_history **timeMachine)
{
    t_history           *next;
    t_history           *h;

    if (!timeMachine || !(h = *timeMachine))
    {
        *timeMachine = NULL;
        return ;
    }
    *timeMachine = NULL;
    while (h->undo)
        h = h->undo;
    while (h)
    {
        next = h->redo;
        FREE(h);
        h = next;
    }
}