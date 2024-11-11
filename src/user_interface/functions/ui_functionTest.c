#include "user_interface.h"

int             ui_functionTest(void *pMega, int flag)
{
    t_mega          *mega;

    if (!(mega = (t_mega *)pMega))
        return (1);
    DEBUG ///
    BEEP_WARNING
    return (0);
}
