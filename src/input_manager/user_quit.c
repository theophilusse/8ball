#include "input_manager.h"

int             user_quit(t_mega *mega, int flg)
{
    if (!mega)
        return (1);
    if (root_destructor(mega, 0))
        return (1);
    exit(flg);
}
