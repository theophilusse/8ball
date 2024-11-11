#include "user_interface.h"

int             ui_isResize(t_ui_box *box, int *onClick, uchar *sideGrab)
{
    uint            i;
    uint            btnDim[2];
    int             btnPos[2];

    if (!box || !onClick)
        return (0);
    i = 8;
    while (i-- > 0) /** Test each side **/
    {
        ui_getBoxSide(box, i, btnDim, btnPos);
        ///if (isInZone(relClick, btnDim, btnPos))
        if (isInZone(onClick, btnDim, btnPos))
        {
            if (sideGrab)
                *sideGrab = (uchar)i; /// Side Handle
            return (1);
        }
    }
    if (sideGrab)
        *sideGrab = 8; /// Default: No Grab
    return (0);
}
