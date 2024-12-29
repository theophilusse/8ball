#include "camera.h"

static struct s_model       default_model(void)
{
    struct s_model  m;

    /**
        m.active = 0;
        m.f = NULL;
        m.v = NULL;
        m.n = NULL;
        m.nf = 0;
        m.nv = 0;
        m.nn = 0;
        m.proj = NULL;
        m._translate[0] = 0;
        m._translate[1] = 0;
        m._translate[2] = 0;
        m._scale[0] = 0;
        m._scale[1] = 0;
        m._scale[2] = 0;
        m._rotate[0] = 0;
        m._rotate[1] = 0;
        m._rotate[2] = 0;
    **/
    memset(&m, 0, sizeof(struct s_model));
    m._ambiant_color[0] = 128;
    m._ambiant_color[1] = 128;
    m._ambiant_color[2] = 128;
    /*m._ambiant_color[3] = SDL_OPAQUE;*/
    return (m);
}

void         release_model(t_camdata *dat, uint objHandle)
{
    t_model            *model;
    int                bottomIndex;
    int                copySz;

    if (!dat || objHandle >= MAX_MODEL)
        return ;
    model = &dat->model[objHandle];
    if (model->active == 0)
    {
        printf("Bad model handle\n");
        return ;
    }
    /** Shift Model Stack. **/
    bottomIndex = model_getLastHandle(dat);
    history_updateDeletion(objHandle);
    ///release_modelPointers(objHandle);
    release_modelPointers(model);
    if (bottomIndex > 0 &&
        (copySz = bottomIndex - (int)objHandle) > 0)
        memcpy((void *)model, (void *)(model + 1),
               sizeof(struct s_model) * copySz);
    model = &dat->model[bottomIndex];
    *model = default_model();
}
