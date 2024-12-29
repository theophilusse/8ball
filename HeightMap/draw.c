#include "HeightMap.h"

void        draw_background(SDL_Surface *bg)
{
    uchar       rgb[4];
    int         i[2];
    int         j[2];
    int         k[2];

    if (!bg)
        return ;
    rgb[0] = 128;
    rgb[1] = 200;
    rgb[2] = 128;
    rgb[3] = 255;
    i[1] = -1;
    while (++i[1] < bg->h)
    {
        i[0] = -1;
        /*while (++i[0] < bg->w)
            put_pixel(bg, (uchar *)rgb, i[0], i[1]); // Gray font*/
        //i[0]++;
    }

    rgb[0] = 255;
    rgb[1] = 255;
    rgb[2] = 255;
    rgb[3] = 255;

    i[0] = 100;
    i[1] = 100;
    j[0] = -100;
    j[1] = 100;

    k[0] = 0;
    k[1] = 0;
    while (k[0] < bg->w)
    {
        draw_line(bg, (uchar *)rgb, k[0], k[1], i[0], i[1]);
        draw_line(bg, (uchar *)rgb, k[0], k[1], j[0], j[1]);
        k[0] += GRID_SIZE;
    }
    /*
    i[0] = 0;
    i[1] = bg->w - 1;
    j[0] = 0;
    j[1] = bg->h - 1;
    while (i[0] < bg->w)
    {
        draw_line(bg, (uchar *)rgb, i[0], j[0], i[1], j[1]);
        i[0] += GRID_SIZE;
        j[1] -= GRID_SIZE;
    }

    i[0] = 0;
    i[1] = bg->w - 1;
    j[0] = 0;
    j[1] = bg->h - 1;
    while (j[0] < bg->h)
    {
        draw_line(bg, (uchar *)rgb, i[0], j[0], i[1], j[1]);
        j[0] += GRID_SIZE;
        i[1] -= GRID_SIZE;
    }
    //////////////////////////////////////////////////
    i[0] = 0;
    i[1] = bg->w - 1;
    j[1] = 0;
    j[0] = bg->h - 1;
    while (i[0] < bg->w)
    {
        draw_line(bg, (uchar *)rgb, i[0], j[0], i[1], j[1]);
        i[0] += GRID_SIZE;
        j[1] += GRID_SIZE;
    }

    i[0] = 0;
    i[1] = 0;
    j[0] = 0;
    j[1] = 0;
    while (j[0] < bg->h)
    {
        draw_line(bg, (uchar *)rgb, i[0], j[0], i[1], j[1]);
        j[0] += GRID_SIZE;
        i[1] += GRID_SIZE;
    }
    */
}

void        draw_cloud(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, int i, int j)
{
    int         posX;
    int         posY;
    double       height[3];
    uchar       color[4];
    double         tmp[4];

    if (!g || !viewport || g->x < 1 || g->y < 1)
    {
        return ;
    }
    height[0] = *(g->ptr + (j * g->x + i));
    color_scheme((uchar *)color, conf->color_scheme, (void *)&height[0]);
    height[0] /= 2;
    if (1) // Set button
    {
        tmp[0] = msk->x / 100;
        tmp[1] = g->x / 100;
        tmp[2] = tmp[0] * ((double)i * tmp[1]);

        tmp[0] = msk->y / 100;
        tmp[1] = g->y / 100;
        tmp[3] = tmp[0] * ((double)j * tmp[1]);

        if (tmp[2] >= 0 && tmp[3] >= 0 && tmp[2] < msk->x && tmp[3] < msk->y)
            height[1] = *(msk->ptr + ((int)tmp[3] * msk->x + (int)tmp[2])) - 128;
    }
    color_scheme((uchar *)color, conf->color_scheme, (void *)&height);
    //perspective(g, conf, viewport, &posX, &posY, i, j, height * g->conf->f);
    height[2] = height[0] + ((height[1] * conf->f) - 128);
    perspective(g, conf, viewport, &posX, &posY, i, j, height[2]); // Works
    //perspective(g, conf, viewport, &posX, &posY, i, j, height); // Works

    ///*rx += (ix * (20 * conf->dim[0])) + iy * (20 * conf->dim[0]);
    ///*ry += (iy * (20 * conf->dim[0])) - ((double)height * conf->f + ix * (20 * conf->dim[0]));

    posX += (viewport->w / 4) + conf->offset[0];
    posY += (viewport->h / 4) + conf->offset[1];
    //if (posX >= 0 && posY >= 0 && posY < viewport->clip_rect.y + viewport->h && posX < viewport->clip_rect.x + viewport->w)
    if (posX < 0 && posY < 0)
        return ;
    square(viewport, posX, posY, conf->pxsz, conf->pxsz, color); // Keep This
    /*put_pixel(viewport, color, posX, posY);*/
}

void        draw_wireframe(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, int i, int j)
{
    int         k;
    double       height;
    int         posX[3];
    int         posY[3];
    int         shift[2];
    uchar       color[4];

    if (!g || !viewport || g->x < 1 || g->y < 1)
        return ;
    k = conf->pxsz;
    shift[0] = (viewport->w / 4) + conf->offset[0];
    shift[1] = (viewport->h / 4) + conf->offset[1];
    height = *(g->ptr + (j * g->x + i)) * g->conf->f;
    perspective(g, conf, viewport, &posX[0], &posY[0], i, j, height);
    posX[0] += shift[0];
    posY[0] += shift[1];
    if (j < (int)g->y - 1 && (height = *(g->ptr + ((j + 1) * g->x + i))) * g->conf->f >= conf->height)
    {
        perspective(g, conf, viewport, &posX[1], &posY[1], i, j + 1, height * g->conf->f);
        posX[1] += shift[0];
        posY[1] += shift[1];
        if (posX[1] >= 0 && posY[1] >= 0 && posX[1] < viewport->w && posY[1] < (int)viewport->h)
        {
            color_scheme((uchar *)color, conf->color_scheme, (void *)&height);
            draw_line_width(viewport, color, posX[0], posY[0], posX[1], posY[1], k);
            /*k = -1;
            while (++k < conf->pxsz)
                draw_line(viewport, color, posX[0] + k, posY[0], posX[1] + k, posY[1]);*/
        }
    }
    if (i < (int)g->x - 1 && (height = *(g->ptr + (j * g->x + (i + 1)))) * g->conf->f >= conf->height)
    {
        perspective(g, conf, viewport, &posX[2], &posY[2], i + 1, j, height * g->conf->f);
        posX[2] += shift[0];
        posY[2] += shift[1];
        if (posX[2] >= 0 && posY[2] >= 0 && posX[2] < (int)viewport->w && posY[2] < (int)viewport->h)
        {
            color_scheme((uchar *)color, conf->color_scheme, (void *)&height);
            draw_line_width(viewport, color, posX[0], posY[0], posX[2], posY[2], k);
            /*k = -1;
            while (++k < conf->pxsz)
                draw_line(viewport, color, posX[0], posY[0] + k, posX[2], posY[2] + k);*/
        }
    }
    //if (posX >= 0 && posY >= 0 && posY < viewport->clip_rect.y + viewport->h && posX < viewport->clip_rect.x + viewport->w)
    //square(viewport, posX, posY, conf->pxsz, conf->pxsz, color); // Keep This
    /*put_pixel(viewport, color, posX, posY);*/

}

/*void        draw_triangle(SDL_Surface *s, uchar *color, int *a, int *b, int *c)
{
    int         tmp0, tmp1;
    int         *higher;
    int         *middle;
    int         *lower;
    int         x, y, x1, x2;

    if (!a || !b || !c || !s || !color)
        return ;
    higher = c;
    middle = a;
    lower = b;
    //if ((y1 < y2 && y1 > y3) || (y1 < y3 && y1 > y2))
    if ((a[1] < b[1] && a[1] > c[1]) || (a[1] < c[1] && a[1] > b[1]))
    {
        middle = a;
        higher = c[1] > middle[1] ? c : b;
        lower = higher == c ? b : c;
    }
    //if ((y2 < y1 && y2 > y3) || (y2 < y3 && y2 > y1))
    if ((b[1] < a[1] && b[1] > c[1]) || (b[1] < c[1] && b[1] > a[1]))
    {
        middle = b;
        higher = c[1] > middle[1] ? c : a;
        lower = higher == c ? a : c;
    }
    //if ((y3 < y1 && y3 > y2) || (y3 < y2 && y3 > y1))
    if ((c[1] < a[1] && c[1] > b[1]) || (c[1] < b[1] && c[1] > a[1]))
    {
        middle = c;
        higher = a[1] > middle[1] ? a : b;
        lower = higher == a ? b : a;
    }
    if (!lower || !middle || !higher)
        return ;
    y = middle[1];
    //while (y < lower[1]) // Up triangle first
    while (y < higher[1]) // Up triangle first
    {
        // on trace le segment horizontal à la hauteur y
        // il faut calculer ses 2 extremités, avec le théoreme de Thales par exemple si tu connais
        // ça doit donner un truc du genre (je suis pas sur, il faut vérifier) :
        //x1 = higher[0] + (lower[0] - higher[0])*(y-higher[1])/(lower[1]-higher[1]);
        //x2 = middle[0] + (lower[0] - middle[0])*(y-higher[1])/(lower[1]-higher[1]);

        //tmp = abs(higher[1]-lower[1]);
        tmp0 = abs(lower[0]-higher[0]);
        tmp1 = abs(lower[1]-higher[1]);
        //printf("tmp0 : [%d], tmp1 : [%d]\n", tmp0, tmp1);
        if (tmp1 < 1)
        {
            y++;
            continue;
        }
        x1 = higher[0] + tmp0*(higher[1]-y)/tmp1;
        x2 = middle[0] + (middle[0]-lower[0])*(higher[1]-y)/tmp1;
        //printf("X1[%d] -> X2[%d]\n", x1, x2);
        x = x1;
        while (x < x2)
        {
            put_pixel(s, color, x,y);
            x++;
        }
        y++;
    }
}*/

/*void        draw_polygon(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, int i, int j)
{
    double       height;
    int         posX[3];
    int         posY[3];
    int         shift[2];
    uchar       color[4];
    int         a[2];
    int         b[2];
    int         c[2];

    if (!g || !viewport || g->x < 1 || g->y < 1)
        return ;
    shift[0] = (viewport->w / 4) + conf->offset[0];
    shift[1] = (viewport->h / 4) + conf->offset[1];
    height = *(g->ptr + (j * g->x + i)) * g->conf->f;
    perspective(g, conf, viewport, &posX[0], &posY[0], i, j, height);
    posX[0] += shift[0];
    posY[0] += shift[1];
    if (j < (int)g->y - 1 && (height = *(g->ptr + ((j + 1) * g->x + i))) * g->conf->f >= conf->height)
    {
        perspective(g, conf, viewport, &posX[1], &posY[1], i, j + 1, height * g->conf->f);
        posX[1] += shift[0];
        posY[1] += shift[1];
        color_scheme((uchar *)color, conf->color_scheme, (void *)&height);
        //if (posX[1] >= 0 && posY[1] >= 0 && posX[1] < viewport->w && posY[1] < (int)viewport->h)
        //{
        //    k = -1;
        //  while (++k < conf->pxsz)
        //       draw_line(viewport, color, posX[0] + k, posY[0], posX[1] + k, posY[1]);
        //}
    }
    else
        return ;
    if (i < (int)g->x - 1 && (height = *(g->ptr + (j * g->x + (i + 1)))) * g->conf->f >= conf->height)
    {
        perspective(g, conf, viewport, &posX[2], &posY[2], i + 1, j, height * g->conf->f);
        posX[2] += shift[0];
        posY[2] += shift[1];
        color_scheme((uchar *)color, conf->color_scheme, (void *)&height);
        //if (posX[2] >= 0 && posY[2] >= 0 && posX[2] < (int)viewport->w && posY[2] < (int)viewport->h)
        //{
        //    k = -1;
        //    while (++k < conf->pxsz)
        //        draw_line(viewport, color, posX[0], posY[0] + k, posX[2], posY[2] + k);
        //}
    }
    else
        return ;
    a[0] = posX[0];
    a[1] = posY[0];
    b[0] = posX[1];
    b[1] = posY[1];
    c[0] = posX[2];
    c[1] = posY[2];
    draw_triangle(viewport, color, (int *)a, (int *)b, (int *)c);
}*/

//draw_mask(data, config[1], editor, (uchar *)&color4);
void            draw_mask(t_grid *g, t_conf *conf, SDL_Surface *viewport, uchar *color) // ! Need Improvements !
{
    uint        i;
    uint        j;
    double      l[2];
    int         p;
    int         posX;
    int         posY;
    int         height;
    /*uchar       *ptr;*/

    if (g->x < 1 || g->y < 1)
        return ;
    p = 1;
    while ((l[1] = sqrt((double)(g->x * g->x + g->y * g->y)) / 100) < 0)
    {
        l[1] *= 2;
        p *= 2;
    }
    i = g->x + 1;
    j = 0;
    if (!g || !viewport)
        return ;
    while (j < g->y)
    {
        height = *(g->ptr + (j * g->x + i));
        //if (height >= MIN_HEIGHT)
        if (height /* * g->f */ >= conf->height)
        {
            posX = i * conf->dim[0];
            posY = j * conf->dim[1];
            /*if (!(ptr = (uchar *)getpixel_addr(viewport, i, j)))
                return ;
            color[0] = (*(g->ptr + (j * g->x + i)) / 2) + *(ptr);
            color[1] = (*(g->ptr + (j * g->x + i)) / 2) + *(ptr + 1);
            color[2] = (*(g->ptr + (j * g->x + i)) / 2) + *(ptr + 2);
            */
            color[0] = *(g->ptr + (j * g->x + i));
            color[1] = *(g->ptr + (j * g->x + i));
            color[2] = *(g->ptr + (j * g->x + i));
            square(viewport, posX + conf->offset[0], posY + conf->offset[1], conf->pxsz, conf->pxsz, (uchar *)color);
        }
        if (i == 0)
        {
            i = g->x + 1;
            if (++j == g->y)
                break ;
        }
        else
            i--;
    }
}

void            draw_viewport(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, uchar *color)
{
    uint        i;
    uint        j;
    double      l[2];
    int         p;
    double       height;
    void        (*render_function)(t_grid *, t_grid *, t_conf *, SDL_Surface *, int, int);

    if (!g || !viewport || g->x < 1 || g->y < 1)
        return ;
    switch (conf->render_type) /// Select render
    {
        case RENDER_CLOUD: render_function = draw_cloud; break;

        case RENDER_WIREFRAME: render_function = draw_wireframe; break;

        //case RENDER_POLYGON: render_function = draw_polygon; break;

        default: return ;
    }
    p = 1;
    while ((l[1] = sqrt((double)(g->x * g->x + g->y * g->y)) / 100) < 0)
    {
        l[1] *= 2;
        p *= 2;
    }
    i = g->x + 1;
    j = 0;
    while (j < g->y)
    {
        height = *(g->ptr + (j * g->x + i));
        //if (height >= MIN_HEIGHT)
        if (height * conf->f >= conf->height)
        {
            //move_camera(g, &posX, &posY, );
            render_function(g, msk, conf, viewport, i, j);
        }
        if (i == 0)
        {
            i = g->x + 1;
            if (++j == g->y)
                break ;
        }
        else
            i--;
    }
}

void        draw_heightmap(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, uchar *color)
{
    double       tmp[4];
    uint        i;
    uint        j;
    double      l[2];
    int         p;
    int         posX;
    int         posY;
    int         height;

    if (g->x < 1 || g->y < 1)
        return ;
    p = 1;
    while ((l[1] = sqrt((double)(g->x * g->x + g->y * g->y)) / 100) < 0)
    {
        l[1] *= 2;
        p *= 2;
    }
    i = g->x + 1;
    j = 0;
    if (!g || !viewport)
        return ;
    while (j < g->y)
    {
        height = *(g->ptr + (j * g->x + i));
        //if (height >= MIN_HEIGHT)
        if (height /* * g->f */ >= conf->height)
        {
            posX = i * conf->dim[0];
            posY = j * conf->dim[1];
            color[0] = *(g->ptr + (j * g->x + i));
            color[1] = *(g->ptr + (j * g->x + i));
            color[2] = *(g->ptr + (j * g->x + i));

            /****Test Mask****/

            if (1) // Set button
            {
                tmp[0] = msk->x / 100;
                tmp[1] = g->x / 100;
                tmp[2] = tmp[0] * ((double)i * tmp[1]);

                tmp[0] = msk->y / 100;
                tmp[1] = g->y / 100;
                tmp[3] = tmp[0] * ((double)j * tmp[1]);
                if (tmp[2] >= 0 && tmp[3] >= 0 && tmp[2] < msk->x && tmp[3] < msk->y)
                {
                    /* height[1] = *(msk->ptr + ((int)tmp[3] * msk->x + (int)tmp[2])) - 128; */
                    color[0] = (color[0] / 2) + (*(msk->ptr + (j * g->x + i)) / 3);
                    color[1] = (color[1] / 2) + (*(msk->ptr + (j * g->x + i)) / 3);
                    color[2] = (color[2] / 2) + (*(msk->ptr + (j * g->x + i)) / 3);
                }
            }

            /****Test Mask****/

            square(viewport, posX + conf->offset[0], posY + conf->offset[1], conf->pxsz, conf->pxsz, (uchar *)color);
        }
        if (i == 0)
        {
            i = g->x + 1;
            if (++j == g->y)
                break ;
        }
        else
            i--;
    }
}

void            draw_button(t_button *b, int offset_x, int offset_y)
{
    int         i;
    int         j;
    uchar       color[4];
    uchar       color_picto[4];
    uchar       *ptr_picto;

    if (!b || !b->s)
    {
        DEBUG //
        return ;
    }
    color[0] = b->color[0];
    color[1] = b->color[1];
    color[2] = b->color[2];
    color[3] = b->color[3];
    j = -1;
    //printf("Offset[%d][%d]\nClip Rect[%d][%d]\n", offset_x, offset_y, b->s->clip_rect.x, b->s->clip_rect.y);
    while (++j < b->s->h)
    {
        i = -1;
        while (++i < b->s->w)
        {
            //printf("pos[%d][%d] offset[%d][%d]\n", i, j, x, y);
            ///put_pixel(b->s, b->color, i + x, j + y);
            put_pixel(b->s, (uchar *)color, i, j);
            if ((ptr_picto = (uchar *)getpixel_addr(b->picto, i, j)))
            {
                /*color_picto[0] = ptr_picto[2]; // Works but not trensparency
                color_picto[1] = ptr_picto[1];
                color_picto[2] = ptr_picto[0];
                color_picto[3] = 255;*/

                color_picto[0] = ptr_picto[0];
                color_picto[1] = ptr_picto[1];
                color_picto[2] = ptr_picto[2];
                color_picto[3] = 255;

                /*color_picto[0] = ptr_picto[3];
                color_picto[1] = ptr_picto[2];
                color_picto[2] = ptr_picto[1];
                color_picto[3] = ptr_picto[0];*/

                /*color_picto[0] = ptr_picto[0];
                color_picto[1] = 0;
                color_picto[2] = 0;
                color_picto[3] = 255;*/
                /*printf("color[%u][%u][%u][%u]\n",
                       color_picto[0],
                       color_picto[1],
                       color_picto[2],
                       color_picto[3]
                       );*/
                put_pixel(b->s, (uchar *)color_picto, i, j);
            }
            /*
            if (b->state == BUTTON_IDLE)
            {
                put_pixel();
            }
            if (b->state == BUTTON_CLICK)
            {

            }
            if (b->state == BUTTON_LOCK)
            {

            }*/
        }
    }
}

void        draw_toolbar(t_toolbar *bar)
{
    int                i;
    int                offset_x;
    int                offset_y;
    struct SDL_Rect    rect;

    if (!bar)
        return ;
    offset_x = bar->viewport->clip_rect.x;
    offset_y = bar->viewport->clip_rect.y;
    i = -1;
    //printf("N picto : %d\n", bar->n);
    while (++i < bar->n)
    {
        if (!bar->btn[i])
            continue ;
        /*rect.x = 10;
        rect.y = 10;*/
        offset_x = bar->btn[i]->s->clip_rect.x;
        offset_y = bar->btn[i]->s->clip_rect.y;
        rect.x = offset_x;
        rect.y = 10;
        rect.h = 32;
        rect.w = 32;
        draw_button(bar->btn[i], offset_x, offset_y);
        ///SDL_BlitSurface(bar->btn[i]->s, 0, bar->viewport, &bar->btn[i]->s->clip_rect);
        SDL_BlitSurface(bar->btn[i]->s, 0, bar->viewport, &rect); // Humm..
    }
}
