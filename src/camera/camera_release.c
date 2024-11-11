#include "camera.h"

void 		camera_release(t_mega *mega)
{
    uint        i;

    if (mega->camera)
    {
        if (mega->camera->data)
        {
            i = -1;
            while (++i < MAX_MODEL)
                if (mega->camera->data->model[i].active == 1)
                    if (mega->camera->data->model[i].proj)
                        FREE(mega->camera->data->model[i].proj);
            if (mega->camera->data->zbuffer)
                FREE(mega->camera->data->zbuffer);
            FREE(mega->camera->data);
        }
        FREE(mega->camera);
    }
}
