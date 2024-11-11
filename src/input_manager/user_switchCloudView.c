#include "input_manager.h"

int            user_switchCloudView(t_mega *mega, int flg)
{
    if (!mega)
        return (1);
    printf("Switch cloud view ");
    mega->stcl->option.display_cloud = mega->stcl->option.display_cloud == 1 ? 0 : 1;
    if (mega->stcl->option.display_cloud == 1)
        printf("[ON]\n");
    else
        printf("[OFF]\n");
    return (0);
}
