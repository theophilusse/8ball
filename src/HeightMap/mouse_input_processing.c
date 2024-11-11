#include "HeightMap.h"

uchar           button_color_red[4] =
{
    255,
    0,
    0,
    255
};

void        editor_input_processing(t_grid *data, int *click, Uint8 button, t_conf **conf)
{
    if (!data || !conf || !conf[0] || !conf[1] || !click)
        return ;
    printf("edit mode = %d\n", conf[1]->edit_mod);
    switch (conf[1]->edit_mod)
    {
        //case TOOL_SQUARE_DEL: square_del(data, click, button, conf[1]);
        case TOOL_SQUARE_DEL: square_del(data, click, button, conf[data->persp + 1]);
            break;
        //case TOOL_SQUARE_ADD: square_add(data, click, button, conf[1]);
        case TOOL_SQUARE_ADD: square_add(data, click, button, conf[data->persp + 1]);
            break;
        //case TOOL_SQUARE_ADD_GRAD: square_add_grad(data, click, button, conf[1]);
        case TOOL_SQUARE_ADD_GRAD: square_add_grad(data, click, button, conf[data->persp + 1]);
            break;
    }
}


int        mouse_input_processing(t_grid *data, SDL_Surface *editor, SDL_Surface *viewport, t_toolbar *upper_toolbar, t_conf **conf, SDL_Cursor **cursor)
{
    int             click[2];
    //int             click_e[2];
    Uint8           button;
    int     zone;

    if (!data || !editor || !viewport || !upper_toolbar || !conf || !conf[0] || !conf[1] || !cursor || !cursor[0] || !cursor[1] || !cursor[2])
        return (-1);
    SDL_PumpEvents();
    zone = -1;
    button = SDL_GetMouseState(&click[0], &click[1]);
    /*click_e[0] = click[0] - 16;
    click_e[1] = click[1] - 16;*/
    if (click[0] < 0 || click[1] < 0)
        return (-2);
    SDL_SetCursor(cursor[0]);
    if (on_surface(viewport, (int *)click))
    {
        zone = 0;
        click_surface(viewport, (int *)click, &click[0], &click[1]);
    }
    //if (zone == -1 && on_area((int *)click, editor->clip_rect.x/* - 16*/, editor->clip_rect.y, editor->w, editor->h))
    //if (zone == -1 && on_surface(editor, (int *)click_e))
    if (zone == -1 && on_surface(editor, (int *)click))
    {
        click[0] += 16;
        click[1] += 16;
        zone = 1;
        SDL_SetCursor(cursor[1]);
        click_surface(editor, (int *)click, &click[0], &click[1]);
        //circle(editor, button_color_red, click[0], click[1], conf[1]->mouse_rad);

        //ellipse(editor, (uchar *)button_color_red, click[0], click[1]);
        //ellipse(editor, (uchar *)button_color_red, click[0], click[1], conf[1]->dim[0] * conf[1]->mouse_rad, conf[1]->dim[1] * conf[1]->mouse_rad);
        //ellipse(editor, (uchar *)button_color_red, click[0], click[1], (long)(conf[1]->dim[0] * conf[1]->mouse_rad), (long)(conf[1]->dim[1] * conf[1]->mouse_rad));
        ellipse(editor, (uchar *)button_color_red, click[0], click[1],
                (long)(2 * conf[1]->dim[0] * conf[1]->mouse_rad), (long)(2 * conf[1]->dim[1] * conf[1]->mouse_rad));

        editor_input_processing(data, (int *)click, button, conf);
    }
    if (zone == -1 && on_surface(upper_toolbar->viewport, (int *)click))
    {
        zone = 2;
        click_surface(upper_toolbar->viewport, (int *)click, &click[0], &click[1]);
        toolbar_input_processing(upper_toolbar, (int *)click, button);
    }
    return (zone);
}
