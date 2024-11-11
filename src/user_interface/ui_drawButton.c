#include "user_interface.h"

uchar           uiColor_button_black[4] = { 0, 0, 0, SDL_ALPHA_OPAQUE};
uchar           uiColor_button_white[4] = { 254, 254, 254, SDL_ALPHA_OPAQUE};
uchar           uiColor_button_dark[4] = { 127, 127, 127, SDL_ALPHA_OPAQUE};
uchar           uiColor_button_light[4] = { 219, 219, 219, SDL_ALPHA_OPAQUE};
uchar           uiColor_button_base[4] = { 195, 195, 195, SDL_ALPHA_OPAQUE};

static void     ui_setButtonColor(uchar *color, uchar isPressed, uchar i)
{
    if (!color)
        return ;
    color[3] = SDL_ALPHA_OPAQUE;
    if (isPressed == 1)
    {
        switch (i)
        {
            case 1: { i = 2; break; }
            case 2: { i = 1; break; }
            case 3: { i = 4; break; }
            case 4: { i = 3; break; }
        }
    }
    switch (i)
    {
        case 0:
        {
            color[0] = uiColor_button_base[0];
            color[1] = uiColor_button_base[1];
            color[2] = uiColor_button_base[2];
            break;
        };
        case 1:
        {
            color[0] = uiColor_button_black[0];
            color[1] = uiColor_button_black[1];
            color[2] = uiColor_button_black[2];
            break;
        };
        case 2:
        {
            color[0] = uiColor_button_white[0];
            color[1] = uiColor_button_white[1];
            color[2] = uiColor_button_white[2];
            break;
        };
        case 3:
        {
            color[0] = uiColor_button_dark[0];
            color[1] = uiColor_button_dark[1];
            color[2] = uiColor_button_dark[2];
            break;
        };
        case 4:
        {
            color[0] = uiColor_button_light[0];
            color[1] = uiColor_button_light[1];
            color[2] = uiColor_button_light[2];
            break;
        };
        default: { break ; };
    }
    if (isPressed == 1 && i != 1 && i != 2) /** Button is ON **/
    {
        color[0] -= 40;
        color[1] -= 40;
        color[2] -= 40;
    }
}

void            ui_drawButton(SDL_Surface *s, t_ui_box *box, int *pos, uint *dim, uchar isPressed, uchar isItem, SDL_Surface *pic)
{
    uint            j;
    uint            x;
    uint            y;
    uchar           color[4];
    int             maxDim[2];
    int             minDim[2];

    if (!pos || !dim || !s || !box)
        return ;
    if (isItem == 1)
    {
        maxDim[0] = box->pos[0] + (int)box->dim[0] - 16;
        maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
        minDim[0] = box->pos[0] + 1;
        minDim[1] = box->pos[1] + 23;
    }
    else
    {
        maxDim[0] = s->w;
        maxDim[1] = s->h;
        minDim[0] = 0;
        minDim[1] = 0;
    }
    ui_setButtonColor(color, isPressed, 0); /// Base
    square_dim(s, pos[0] + 2, pos[1] + 2, (int)dim[0] - 2, (int)dim[1] - 2, color, maxDim, minDim);

    ui_setButtonColor(color, isPressed, 1); /// DOWN-RIGHT
    put_pixel_dim(s, color, pos[0] + dim[0] - 1, pos[1] + dim[1], maxDim, minDim);
    put_pixel_dim(s, color, pos[0] + (int)(dim[0] - 2), pos[1] + (int)(dim[1] - 1), maxDim, minDim);
    ui_setButtonColor(color, isPressed, 2); /// UP-LEFT
    put_pixel_dim(s, color, pos[0], pos[1], maxDim, minDim);
    put_pixel_dim(s, color, pos[0] + 1, pos[1] + 1, maxDim, minDim);

    ui_setButtonColor(color, isPressed, 4); /// Light
    draw_line_dim(s, color, pos[0] + 1, pos[1], pos[0] + dim[0] - 1, pos[1], maxDim, minDim); /** Horizontal line UP   **/
    draw_line_dim(s, color, pos[0] + 2, pos[1] + 1, pos[0] + dim[0] - 2, pos[1] + 1, maxDim, minDim); /** Horizontal line UP   **/

    draw_line_dim(s, color, pos[0], pos[1] + 1, pos[0], pos[1] + dim[1], maxDim, minDim); /** Vertical line LEFT **/
    draw_line_dim(s, color, pos[0] + 1, pos[1] + 2, pos[0] + 1, pos[1] + dim[1] - 1, maxDim, minDim); /** Horizontal line LEFT **/

    ui_setButtonColor(color, isPressed, 3); /// Dark
    draw_line_dim(s, color, pos[0], pos[1] + dim[1], pos[0] + dim[0] - 1, pos[1] + dim[1], maxDim, minDim); /** Horizontal line DOWN **/
    draw_line_dim(s, color, pos[0] + 1, pos[1] + dim[1] - 1, pos[0] + dim[0] - 2, pos[1] + dim[1] - 1, maxDim, minDim); /** Horizontal line DOWN **/
    draw_line_dim(s, color, pos[0] + dim[0] - 1, pos[1], pos[0] + dim[0] - 1, pos[1] + dim[1], maxDim, minDim); /** Vertical line RIGHT **/
    draw_line_dim(s, color, pos[0] + dim[0] - 2, pos[1] + 1, pos[0] + dim[0] - 2, pos[1] + dim[1] - 1, maxDim, minDim); /** Horizontal line RIGHT **/
    if (pic &&
        pos[0] - box->pos[0] < (uint)box->dim[0] - 16 && pos[1] - box->pos[1] > 16 &&
        pos[1] - box->pos[1] < (uint)box->dim[1] - 16)
        blit_at(pic, s, pos[0], pos[1]);
    /*
        ui_setButtonColor(color, isPressed, 1); /// Black
        ui_setButtonColor(color, isPressed, 2); /// White
    */
}
