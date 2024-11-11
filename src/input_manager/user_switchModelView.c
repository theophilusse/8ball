#include "input_manager.h"

int            user_switchModelView(t_mega *mega, int flg)
{
    if (!mega)
        return (1);
    printf("Switch model view ");
    mega->stcl->option.display_model = mega->stcl->option.display_model == 1 ? 0 : 1;
    if (mega->stcl->option.display_model == 1)
        printf("[ON]\n");
    else
        printf("[OFF]\n");
    return (0);
}
