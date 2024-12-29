#include "camera.h"

void                 release_modelPointers(t_model *model)
{
    if (model->proj)
        FREE(model->proj);
    model->proj = NULL;
    if (model->f)
        FREE(model->f);
    model->f = NULL;
    if (model->n)
        FREE(model->n);
    model->n = NULL;
    if (model->v)
        FREE(model->v);
    model->v = NULL;
}
