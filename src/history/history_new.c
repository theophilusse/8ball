#include "history.h"

struct s_history_param             set_default_history_params(void)
{
    struct s_history_param            h_param;


    h_param.ptr = NULL;
    h_param.buf[0] = '\0';
    h_param.n = 0;
    h_param.selection = NULL;
    h_param.vrt.model = -1;
    h_param.vrt.ptr = NULL;
    h_param._c_s = '\0';
    h_param._c_u = '\0';
    h_param._d_s = 0;
    h_param._d_u = 0;
    h_param._f32 = 0.0;
    h_param._f64 = 0.0;
    h_param.vec[0] = 0.0;
    h_param.vec[1] = 0.0;
    h_param.vec[2] = 0.0;
    h_param._sz = 0;
    h_param.type = HISTORY_IDLE; /// Idle.
    return (h_param);
}

t_history            *history_new(void)
{
    t_history                   *timeMachine;

    if (!(timeMachine = (t_history *)ALLOC(sizeof(struct s_history))))
        return (NULL);
    timeMachine->redo = NULL;
    timeMachine->undo = NULL;
    timeMachine->param = set_default_history_params();
    return (timeMachine);
}
