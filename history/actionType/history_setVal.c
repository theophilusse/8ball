#include "history.h"

void             history_setVal(t_mega *mega, t_history *timeMachine, uint undo)
{
    if (!mega || !timeMachine)
        return ;
    if (undo)
    {
        strToVal(timeMachine->param.buf, timeMachine->param.ptr, timeMachine->param._c_u);
    }
    else
    {
        switch (timeMachine->param._c_u)
        {
            case UI_DATATYPE_INT: *((int *)timeMachine->param.ptr) = timeMachine->param._d_s; break;
            case UI_DATATYPE_UINT: *((uint *)timeMachine->param.ptr) = timeMachine->param._d_u; break;
            case UI_DATATYPE_FLOAT: *((float *)timeMachine->param.ptr) = timeMachine->param._f32; break;
            case UI_DATATYPE_DOUBLE: *((double *)timeMachine->param.ptr) = timeMachine->param._f64; break;
            /** case UI_DATATYPE_STR: *((char *)timeMachine->param.ptr) = timeMachine->param.ptr; break; **/
        }
    }
}
