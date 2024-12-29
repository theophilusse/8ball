#include "HeightMap.h"

t_conf          *make_conf(void)
{
    t_conf          *config;

    if (!(config = (t_conf *)malloc(sizeof(struct s_conf))))
        return (NULL);
    config->offset[0] = 0;
    config->offset[1] = 0;
    config->dim[0] = DEFAULT_ZOOM;
    config->dim[1] = DEFAULT_ZOOM;
    config->f = 1.0;
    config->height = 1.0;
    config->pxsz = 4;
    config->mouse_rad = EDIT_RADIUS;
    config->mouse_int = EDIT_INTENSITY;
    config->edit_mod = 1;
    config->color_scheme = 0;
    config->render_type = RENDER_CLOUD;
    return (config);
}
