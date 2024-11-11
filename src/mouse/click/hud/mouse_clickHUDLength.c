#include "mouse.h"

int                 mouse_clickHUDLength(t_hud *hud, int *clickCoord)
{
    double              vec[2];
    t_hud_length        *length;

    if (!clickCoord || !hud)
        return (1);
    length = ((t_hud_length *)hud->data.buf);
    vec[0] = (double)clickCoord[0] - hud->org.coord[0];
    vec[1] = (double)clickCoord[1] - hud->org.coord[1];
    length->onClick = length2(vec);
    length->factor = 0;
    return (0);
}
