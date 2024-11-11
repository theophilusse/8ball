#include "user_interface.h"

void             ui_getBoxSide(t_ui_box *box, uchar i, uint *btnDim, int *btnPos)
{
    uint                borderWidth;
    /** FAILSAFE **/
    /*
        if (!btnDim)
            return ;
        btnDim[0] = 0;
        btnDim[1] = 0;
        if (!btnPos)
            return ;
        btnPos[0] = -1;
        btnPos[1] = -1;
    */
    if (i >= 8 || !box || !btnDim || !btnPos)
        return ;
    /**

        #define UI_UP_EDGE                        0 /// NOK.
        #define UI_DOWN_EDGE                      1
        #define UI_LEFT_EDGE                      2
        #define UI_RIGHT_EDGE                     3 ///
        #define UI_UPPER_LEFT_CORNER              4 /// NOK
        #define UI_UPPER_RIGHT_CORNER             5
        #define UI_LOWER_LEFT_CORNER              6
        #define UI_LOWER_RIGHT_CORNER             7 /// OK

    **/
    borderWidth = UI_BORDER_WIDTH;
    switch (i)
    {
        /// //////////////////// CORNERS
        case UI_UPPER_LEFT_CORNER:
        {
            /*btnPos[0] = box->pos[0];
            btnPos[1] = box->pos[1];*/
            btnPos[0] = 0;
            btnPos[1] = 0;
            btnDim[0] = borderWidth;
            btnDim[1] = borderWidth;
            break;
        }
        case UI_UPPER_RIGHT_CORNER:
        {
            ///
            /*btnPos[0] = box->pos[0] + ((int)box->dim[0] - borderWidth);
            btnPos[1] = box->pos[1];*/
            btnPos[0] = (int)box->dim[0] - borderWidth;
            btnPos[1] = 0;
            btnDim[0] = borderWidth;
            btnDim[1] = borderWidth;
            break;
        }
        case UI_LOWER_LEFT_CORNER:
        {
            /*btnPos[0] = box->pos[0];
            btnPos[1] = box->pos[1] + ((int)box->dim[1] - borderWidth);*/
            btnPos[0] = 0;
            btnPos[1] = (int)box->dim[1] - borderWidth;
            btnDim[0] = borderWidth;
            btnDim[1] = borderWidth;
            break;
        }
        case UI_LOWER_RIGHT_CORNER:
        {
            /*btnPos[0] = box->pos[0] + ((int)box->dim[0] - borderWidth);
            btnPos[1] = box->pos[1] + ((int)box->dim[1] - borderWidth);*/
            btnPos[0] = (int)box->dim[0] - borderWidth;
            btnPos[1] = (int)box->dim[1] - borderWidth;
            btnDim[0] = borderWidth;
            btnDim[1] = borderWidth;
            break;
        }
        /// //////////////////// EDGE
        case UI_UP_EDGE:
        {
            /*btnPos[0] = box->pos[0];
            btnPos[1] = box->pos[1];*/
            btnPos[0] = 0;
            btnPos[1] = 0;
            btnDim[0] = box->dim[0];
            btnDim[1] = borderWidth;
            break;
        }
        case UI_DOWN_EDGE:
        {
            /*btnPos[0] = box->pos[0];
            btnPos[1] = box->pos[1] + ((int)box->dim[1] - (borderWidth * 2));*/
            btnPos[0] = 0;
            btnPos[1] = (int)box->dim[1] - borderWidth;
            btnDim[0] = box->dim[0];
            btnDim[1] = borderWidth;
            break;
        }
        case UI_LEFT_EDGE:
        {
            /*btnPos[0] = box->pos[0];
            btnPos[1] = box->pos[1];*/
            btnPos[0] = 0;
            btnPos[1] = 0;
            btnDim[0] = borderWidth;
            btnDim[1] = box->dim[1];
            break;
        }
        case UI_RIGHT_EDGE:
        {
            /*btnPos[0] = box->pos[0] + ((int)box->dim[0] - borderWidth);
            btnPos[1] = box->pos[1];*/
            btnPos[0] = (int)box->dim[0] - borderWidth;
            btnPos[1] = 0;
            btnDim[0] = borderWidth;
            btnDim[1] = box->dim[1];
            break;
        }
    }
    return ;
    /**          **/
    if (((i >> 2) % 2) == 0)
    {
        /** Point . **/
        btnDim[0] = 5;
        btnDim[1] = 5;
        if (((i >> 1) % 2) == 0)
        {
            /** Down **/
            if ((i % 2) == 0) /** Right **/
            {
                btnPos[0] = box->pos[0] + box->dim[0] - 5;
                btnPos[1] = box->pos[1] + box->dim[1] - 5;
                return ;
            }
            else /** Left **/
            {
                btnPos[0] = box->pos[0];
                btnPos[1] = box->pos[1] + box->dim[1] - 5;
                return ;
            }
        }
        else
        {
            /** Up **/
            if ((i % 2) == 0) /** Right **/
            {
                btnPos[0] = box->pos[0] + box->dim[1] - 5;
                btnPos[1] = box->pos[1];
                return ;
            }
            else /** Left **/
            {
                btnPos[0] = box->pos[0];
                btnPos[1] = box->pos[1];
                return ;
            }
        }
    }
    else
    {
        /** Bar \ **/
        if (((i >> 1) % 2) == 0)
        {
            /** Hrz = **/
            btnDim[0] = box->dim[0];
            btnDim[1] = UI_BORDER_WIDTH;
            if ((i % 2) == 0) /** Right **/
            {
                btnPos[0] = box->pos[0];
                btnPos[1] = box->pos[1];
                return ;
            }
            else /** Left **/
            {
                btnPos[0] = box->pos[0] + btnDim[0];
                btnPos[1] = box->pos[1];
                return ;
            }
        }
        else
        {
            /** Vrt | **/
            btnDim[0] = UI_BORDER_WIDTH;
            btnDim[1] = box->dim[1];
            if ((i % 2) == 0) /** Down **/
            {
                btnPos[0] = box->pos[0];
                btnPos[1] = box->pos[1] + btnDim[1];
                return ;
            }
            else /** Up **/
            {
                btnPos[0] = box->pos[0];
                btnPos[1] = box->pos[1];
                return ;
            }
        }
    }
}
