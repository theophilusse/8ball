#include "user_interface.h"

void            ui_drawBox(t_mega *mega, SDL_Surface *viewport, uchar boxHandle)
{
    uint            maxChar;
    uint            titleLen;
    int             point[18];
    int             lineWidth = UI_BORDER_WIDTH;
    //uint             twoLineWidth;
    uchar           barColor[4];
    uchar           *lineColor;
    uchar           boxColor[4];
    t_ui_box        *box;

    if (!mega || !viewport || !mega->ui || !(box = &mega->ui->box[boxHandle]))
        return ;
    ///if (box->z_index != 0)
    if (boxHandle != 0)
    {
        barColor[0] = _medium_green[0] >> 1;
        barColor[1] = _medium_green[1] >> 1;
        barColor[2] = _medium_green[2] >> 1;
        barColor[3] = SDL_ALPHA_OPAQUE;
        boxColor[3] = (uchar)((boxHandle - 1) * 14);
        printf("Z-Index/Handle : [%u]\n", boxHandle);/// DEBUG .
        if (boxColor[3] < _gray_gray[0])
        {
            boxColor[0] = _gray_gray[0] - boxColor[3];
            boxColor[1] = _gray_gray[1] - boxColor[3];
            boxColor[2] = _gray_gray[2] - boxColor[3];
        }
        else
            memset((void *)boxColor, 0, 3);
        boxColor[3] = SDL_ALPHA_OPAQUE;
        ///boxColor[3] = SDL_ALPHA_OPAQUE / n_visible;
        lineColor = (uchar *)_black;
    }
    else
    {
        barColor[0] = _medium_green[0];
        barColor[1] = _medium_green[1];
        barColor[2] = _medium_green[2];
        barColor[3] = SDL_ALPHA_OPAQUE;
        boxColor[0] = box->content->color[0];
        boxColor[1] = box->content->color[1];
        boxColor[2] = box->content->color[2];
        boxColor[3] = SDL_ALPHA_OPAQUE;
        lineColor = (uchar *)_black_blue;
    }
    //twoLineWidth = lineWidth << 1;
    point[0] = box->pos[0]; /// upper LEFT CORNER
    point[1] = box->pos[1];

    point[2] = box->pos[0] + box->dim[0]; /// upper RIGHT CORNER
    point[3] = box->pos[1];

    point[4] = box->pos[0]; /// middle LEFT CORNER
    point[5] = box->pos[1] + lineWidth + 16;

    point[6] = box->dim[0]; ///  middle RIGHT CORNER
    point[7] = lineWidth + 16;

    point[8] = box->pos[0]; /// lower LEFT CORNER
    point[9] = box->pos[1] + box->dim[1];

    point[10] = box->pos[0] + box->dim[0]; /// lower RIGHT CORNER
    point[11] = box->pos[1] + box->dim[1];

    point[12] = box->pos[0] + (box->dim[0] / 2); /// CENTER (optionnal)
    point[13] = box->pos[1] + (box->dim[1] / 2);

    maxChar = box->dim[0] >> 4;
    if ((titleLen = strlen(box->title)) + 5 > maxChar)
        titleLen = maxChar;
    point[14] = box->pos[0] + (box->dim[0] / 2) - ((titleLen * 16) / 2); /// TITLE
    point[15] = box->pos[1] + 2;

    point[16] = box->pos[0] + box->dim[0] - (14 + lineWidth); /// KILL BUTTON
    point[17] = box->pos[1] + (lineWidth - 1);


    DEBUG ///
    square(viewport, point[0], point[1],
                    point[6], point[7], (uchar *)barColor); /// Square CF.
    square(viewport, point[4], point[5],
                    box->dim[0], box->dim[1] - (lineWidth + 16), boxColor); /// Square AD.
    /**
        draw_line_width(viewport, (uchar *)lineColor, point[0], point[1], /// Line upperLeftCorner->upperRightCorner
                                    point[2], point[3], lineWidth);
    **/

    /// Line upperLeftCorner->upperRightCorner
    ///lineWidth--;
    lineWidth = 0;
    /// Test.
    /// base line width = &lineWidth.
    DEBUG ///
    line_hrz_width(viewport, (uchar *)lineColor,
                   new_scanline(point[1], point[0], point[2], &lineWidth));


    /**
    draw_line_width(viewport, (uchar *)lineColor, point[4], point[5], /// Line middleLeftCorner->middleRightCorner
                                point[4] + point[6], point[7] + box->pos[1], lineWidth);
    **/
    DEBUG ///
    line_hrz_width(viewport, (uchar *)lineColor,
                   new_scanline(point[5], point[4], point[4] + point[6], &lineWidth));



    /**
        draw_line_width(viewport, (uchar *)lineColor, point[8], point[9], /// Line lowerLeftCorner->lowerRightCorner
                                    point[10], point[11], lineWidth);
    **/
    DEBUG ///
    line_hrz_width(viewport, (uchar *)lineColor,
                   new_scanline(point[9], point[8], point[10], &lineWidth));
    DEBUG ///
    blit_at(mega->ui->assets.spKill, viewport, point[16], point[17]);

    DEBUG ///
    charset_printStopWidth(viewport, mega->ui->font_bis.charset, point[14], point[15], (uint)(box->dim[0] - 16), box->title);

    /**
        draw_line_width(viewport, (uchar *)lineColor, point[0], point[1], /// Line upperLeftCorner->lowerLeftCorner
                                    point[8], point[9], lineWidth);
    **/
    DEBUG ///
    line_vrt_width(viewport, (uchar *)lineColor,
                   new_scanline(point[0], point[1], point[9], &lineWidth));
    /**
        draw_line_width(viewport, (uchar *)lineColor, point[2], point[3], /// Line upperRightCorner->lowerRightCorner
                                    point[10], point[11], lineWidth);
    **/
    DEBUG ///
    line_vrt_width(viewport, (uchar *)lineColor,
                   new_scanline(point[2] - 1, point[3], point[11], &lineWidth));
}
