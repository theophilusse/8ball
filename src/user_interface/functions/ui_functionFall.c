#include "user_interface.h"

int             ui_functionFall(void *pMega, int flag)
{
    t_mega          *mega;

    if (!(mega = (t_mega *)pMega))
        return (1);
    printf("user_computeCloud ");
    if (mega->input_manager[USER_COMPUTE_CLOUD](mega, 0))
        return (1);
    return (0);
}
