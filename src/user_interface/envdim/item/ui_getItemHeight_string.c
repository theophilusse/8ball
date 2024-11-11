#include "user_interface.h"

int             ui_getItemHeight_string(t_ui_box *box, t_box_item *item, int currentVerticalPos)
{
    int             lineWidth = UI_BORDER_WIDTH;
    int             twoLineWidth = lineWidth * 2;
    int             ret;
    uint            vrtPos;

    if (!box || !item || !box->font)
        return (currentVerticalPos);
    vrtPos = currentVerticalPos;
    currentVerticalPos += (uint)charset_getOffsetHeight(box, box->font,
                        item->pos[0] + lineWidth,
                        (int)item->pos[1],
                        ///(uint)(box->dim[0] - ((twoLineWidth + 16) + item->pos[0])),
                        (uint)(box->dim[0] - ((twoLineWidth + 32) + item->pos[0])),
                        SDL_TRUE, (char *)item->ptr);
    ///currentVerticalPos += 32;
    ///item->dim[1] = currentVerticalPos - item->pos[1];/// Test.
    item->dim[1] = currentVerticalPos - vrtPos;/// Test.
    ///return (currentVerticalPos);
    return (currentVerticalPos + 16);
}
