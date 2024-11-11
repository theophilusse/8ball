#include "user_interface.h"

void             ui_setBoxSide(t_userInterface *ui, t_ui_box *box, uchar i, t_mouse *mouse)
{
    int             boxDim[2];
    int             boxPos[2];
    int             oldPos[2];
    int             *mouseDrag;
    int             *mousePos;

    if (i >= 8 || !box || !mouse || !ui)
        return ;
    mouseDrag = mouse->mouseDrag;
    mousePos = mouse->mousePos;
    /**/
    boxDim[0] = (int)box->dim[0];
    boxDim[1] = (int)box->dim[1];//
    oldPos[0] = box->pos[0];
    oldPos[1] = box->pos[1];
    boxPos[0] = oldPos[0];
    boxPos[1] = oldPos[1];
    /**/
    /**** DEBUG ***/
    switch (i)
    {
        /// //////////////////// CORNERS
        case UI_UPPER_LEFT_CORNER:
        {
            boxDim[0] = (int)box->dim[0] - mouseDrag[0];
            boxDim[1] = (int)box->dim[1] - mouseDrag[1];
            boxPos[0] = box->pos[0] + mouseDrag[0];
            boxPos[1] = box->pos[1] + mouseDrag[1];
            break;
        }
        case UI_UPPER_RIGHT_CORNER:
        {
            boxDim[0] = (int)box->dim[0] + mouseDrag[0];
            boxDim[1] = (int)box->dim[1] - mouseDrag[1];
            boxPos[1] = box->pos[1] + mouseDrag[1];
            break;
        }
        case UI_LOWER_LEFT_CORNER:
        {
            boxDim[0] = (int)box->dim[0] - mouseDrag[0];
            boxDim[1] = (int)box->dim[1] + mouseDrag[1];
            boxPos[0] = box->pos[0] + mouseDrag[0];
            break;
        }
        case UI_LOWER_RIGHT_CORNER:
        {
            boxDim[0] = (int)box->dim[0] + mouseDrag[0];
            boxDim[1] = (int)box->dim[1] + mouseDrag[1];
            break ;
        }
        /// //////////////////// EDGE
        case UI_UP_EDGE:
        {
            boxDim[1] = (int)box->dim[1] - mouseDrag[1];
            boxPos[1] = box->pos[1] + mouseDrag[1];
            break;
        }
        case UI_DOWN_EDGE:
        {
            boxDim[1] = (int)box->dim[1] + mouseDrag[1];
            break;
        }
        case UI_LEFT_EDGE:
        {
            boxPos[0] = box->pos[0] + mouseDrag[0];
            boxDim[0] = (int)box->dim[0] - mouseDrag[0];
            break;
        }
        case UI_RIGHT_EDGE:
        {
            boxDim[0] = (int)box->dim[0] + mouseDrag[0];
            break;
        }
    }
    ui->sigRefresh = 1;
    if (boxDim[0] >= 100)
    {
        box->dim[0] = (uint)boxDim[0];
        box->pos[0] = boxPos[0];
        box->pos[1] = boxPos[1];
    }
    else
    {
        box->dim[0] = 100;
        box->pos[0] = boxPos[0];
        box->pos[1] = boxPos[1];
    }
    if (boxDim[1] >= 100)
    {
        box->dim[1] = (uint)boxDim[1];
        box->pos[0] = boxPos[0];
        box->pos[1] = boxPos[1];
    }
    else
    {
        box->dim[1] = 100;
        box->pos[1] = oldPos[1];
        box->pos[0] = boxPos[0];
        box->pos[1] = boxPos[1];
    }
}
