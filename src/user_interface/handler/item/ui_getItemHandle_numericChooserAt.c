#include "user_interface.h" 
int          ui_getItemHandle_numericChooserAt(t_userInterface *ui, t_ui_box *box, t_box_item *item, int *onClick, uchar *handle, uchar itemHandle) 
{ 
    int             relClick[2]; 
    int             btnPos[2]; 
    uint            btnDim[2]; 
    if (!item || !box) 
        return (0); 
    relClick[0] = onClick[0]; 
    relClick[1] = onClick[1]; 
    btnPos[0] = item->pos[0] - box->horizontal_bar.shift; 
    btnPos[1] = item->pos[1] - box->vertical_bar.shift; 
    btnDim[0] = item->dim[0]; 
    btnDim[1] = item->dim[1]; 
    if (isInZone(relClick, btnDim, btnPos)) 
    { 
        if (ui) 
            ui->sigRefresh = 1; 
        if (handle) 
            *handle = (uchar)itemHandle; 
        return (1); 
    } 
    return (0); 
} 
