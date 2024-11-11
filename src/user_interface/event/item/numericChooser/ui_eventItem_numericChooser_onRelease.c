#include "user_interface.h"

struct s_ui_event       ui_eventItem_numericChooser_onRelease(t_mega *mega, t_ui_box *box, t_box_item *item, int *onClick)
{
    uchar                   tabNext;
    int                     itmPos[2];
    ///DATATYPE         *DATAPTR;
    struct s_ftData_zone        zone;

    if (!mega || !box || !item || !onClick || !item->ptr)
        return (ui_setDefaultEvent());
    /*itmPos[0] = item->pos[0] - box->horizontal_bar.shift;
    itmPos[1] = item->pos[1] - box->vertical_bar.shift;*/
    itmPos[0] = item->pos[0] - box->horizontal_bar.shift;
    itmPos[1] = item->pos[1] - box->vertical_bar.shift;
    if (isInZone(onClick, item->dim, itmPos))
    {
        int     posShift[2];
        uint    dim[2];


        dim[0] = (item->dim[0] - 32);
        dim[1] = 16;
        posShift[0] = itmPos[0] + 16;
        posShift[1] = itmPos[1];
        tabNext = 0;
        if (mega->ui->event.flag == 1 && isInZone(onClick, dim, posShift))
        {
            /// CALL internal ui_function
            if (item->ft.idx[0])
            {
                zone.pos[0] = posShift[0] + box->pos[0];
                zone.pos[1] = posShift[1] + box->pos[1];
                zone.dim[0] = dim[0];
                zone.dim[1] = dim[1];
                zone.maxDim[0] = box->pos[0] + (int)box->dim[0] - (UI_BORDER_WIDTH + 16);
                zone.maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
                zone.minDim[0] = box->pos[0] + 1;
                zone.minDim[1] = box->pos[1] + 23;
                ///item->ft.idx[0](item->ptr, (int)item->status.param[2], posShift, dim);
                /*
                    #define FTCAST_         (void (*)(void*, int, struct s_ftData_zone))
                */
                item->ft.idx[0](item->ptr, (int)item->status.param[2], (int *)&zone, (void *)&tabNext);
                if (tabNext == 1)
                {
                    printf("TABULATION DOWN ::: Todo. (get next item)\n", tabNext);///
                    /**
                    while (++item->type != UI_ITEMTYPE_NUMERICCHOOSER)
                        if (item->type == UI_ITEMTYPE_EMPTY)
                            break;
                    if (item->type == UI_ITEMTYPE_NUMERICCHOOSER)
                    {
                        ui_eventItem_numericChooser_onRelease(mega, );
                    }
                    mega->ui->event.itemHandle
                    */
                }
                ///FTCAST_(item->ft.idx[0])(item->ptr, (int)item->status.param[2], (int *)&zone);
            }
        }

        dim[0] = 16;
        dim[1] = 16;
        posShift[0] = itmPos[0] + (item->dim[0] - 16);
        posShift[1] = itmPos[1];

        uint        *ptrUint;
        int         *ptrInt;
        double      *ptrDouble;
        if (mega->ui->event.flag == 2 && isInZone(onClick, dim, itmPos))
        {
            if (item->ft.idx[1])
                item->ft.idx[1](mega, 2, NULL, NULL);
            else
                switch (item->status.param[2])
                {
                    case UI_DATATYPE_INT:
                    {
                        int         swpInt;

                        ptrInt = (int *)item->ptr;
                        swpInt = *ptrInt;
                        *ptrInt = *ptrInt - (int)item->status.factor;
                        break;
                    }
                    case UI_DATATYPE_UINT:
                    {
                        ptrUint = (uint *)item->ptr;
                        if ((uint)item->status.factor < *ptrUint)
                            *ptrUint = *ptrUint - (uint)item->status.factor;
                        //*ptrUint = *ptrUint - swpUint;
                        break;
                    }
                    case UI_DATATYPE_DOUBLE:
                    {
                        ptrDouble = (double *)item->ptr;
                        *ptrDouble = *ptrDouble - (double)item->status.factor;
                        break;
                    }
                }
            DEBUG ///
        }
        if (mega->ui->event.flag == 3 && isInZone(onClick, dim, posShift))
        {
            if (item->ft.idx[2])
                item->ft.idx[2](mega, 3, NULL, NULL);
            else
                switch (item->status.param[2])
                {
                    case UI_DATATYPE_INT:
                    {
                        ptrInt = (int *)item->ptr;
                        *ptrInt = *ptrInt + (int)item->status.factor;
                        break;
                    }
                    case UI_DATATYPE_UINT:
                    {
                        ptrUint = (uint *)item->ptr;
                        if (item->status.factor > 0)
                            *ptrUint = *ptrUint + (uint)item->status.factor;
                        break;
                    }
                    case UI_DATATYPE_DOUBLE:
                    {
                        ptrDouble = (double *)item->ptr;
                        *ptrDouble = *ptrDouble + (double)item->status.factor;
                        break;
                    }
                }
            DEBUG ///
        }
    }
    mega->ui->sigRefresh = 1;
    mega->ui->event.flag = 0;
    return (ui_setDefaultEvent());

    /*if ((!DATAPTR = item->ptr))
        return ;*/
    itmPos[0] = item->pos[0] - box->horizontal_bar.shift;
    itmPos[1] = item->pos[1] - box->vertical_bar.shift;
    ///printf("ONRELEASE\n\tL-> onClick[d]\n", onClick[0], onClick[1]);
    if (isInZone(onClick, item->dim, itmPos))
           printf("Call Function\n");
    mega->ui->sigRefresh = 1;
    return (ui_setDefaultEvent());
}
