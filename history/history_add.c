#include "history.h"

    /***********  History ************/
    /**
    typedef struct s_history_param
    {
        uchar           _c_u;
        char            _c_s;
        uint            _d_u;
        int             _d_s;
        float           _f32;
        double          _f64;
        char            buf[32];
        uint            n;
        size_t          _sz;
        void            *ptr;
        struct s_select_node   *selection;
    }               s_history_param;

    typedef struct s_history
    {
        struct s_history        *undo; /// Prev
        struct s_history        *redo; /// Next
        struct s_history_param  param;
    }               t_history;
    **/
    /*********************************/

t_history            *history_add(t_history *timeMachine, struct s_history_param userEvent)
{
    t_history                   *event;

    return (NULL); /// DEBUG
    if (!timeMachine || !(event = history_new()))
        return (NULL);
    if (timeMachine->redo)
        history_clear(timeMachine->redo); /** DEBUG **/

    history_display(timeMachine); /// DEBUG .

    /*while (timeMachine->redo) // Not useful because of previous deletion
        timeMachine = timeMachine->redo;*/
    event->redo = NULL;
    event->param = userEvent;
    timeMachine->redo = event;
    event->undo = timeMachine;
    return (event);
}
