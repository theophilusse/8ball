#include "user_interface.h"

int             ui_functionBye(void *pMega, int flag)
{
    t_mega          *mega;

    if (!(mega = (t_mega *)pMega))
        return (1);
    printf("Bye !\n");
    root_destructor(mega, 0);
    return (1);
}
