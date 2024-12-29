#include "HeightMap.h"

void        btn_square_add(void *input)
{
    t_conf    *conf;

    DEBUG //
    if (!(conf = (t_conf *)input))
        return ;
    conf->edit_mod = TOOL_SQUARE_ADD;
}


void        btn_square_add_grad(void *input)
{
    t_conf    *conf;

    DEBUG //
    if (!(conf = (t_conf *)input))
        return ;
    conf->edit_mod = TOOL_SQUARE_ADD_GRAD;
}

void        btn_square_del(void *input)
{
    t_conf    *conf;

    DEBUG //
    if (!(conf = (t_conf *)input))
        return ;
    conf->edit_mod = TOOL_SQUARE_DEL;
}


void        btn_render_cloud(void *input)
{
    t_conf    *conf;

    DEBUG //
    if (!(conf = (t_conf *)input))
        return ;
    conf->render_type = RENDER_CLOUD;
}

void        btn_render_wireframe(void *input)
{
    t_conf    *conf;

    DEBUG //
    if (!(conf = (t_conf *)input))
        return ;
    conf->render_type = RENDER_WIREFRAME;
}

void        btn_render_polygon(void *input)
{
    t_conf    *conf;

    DEBUG //
    if (!(conf = (t_conf *)input))
        return ;
    conf->render_type = RENDER_POLYGON;
}
