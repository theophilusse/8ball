#include "user_interface.h"

int             ui_functionExportDXF(void *pMega, int flag)
{
    t_mega          *mega;

    if (!(mega = (t_mega *)pMega))
        return (1);
    printf("Exporting.\n");
    export_cloud_to_dxf(mega, mega->picture->w * mega->picture->h);
    return (0);
}
