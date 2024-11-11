#include "camera.h"

uint         model_getLastHandle(t_camdata *dat)
{
    t_model         *model;
    uint            modHandle;

    if (!dat)
        return (0);
    model = &dat->model[0];
    modHandle = 0;
    while (model->active != 0 && modHandle < MAX_MODEL)
    {
        modHandle++;
        model++;
    }
    return (modHandle >= MAX_MODEL ? 0 : modHandle);
}