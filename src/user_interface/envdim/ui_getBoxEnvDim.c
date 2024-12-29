#include "user_interface.h"

static uint         get_total_height_render(t_userInterface *ui, t_ui_box *box)
{
    uint            k;
    //uint            w;
    //uint            h;
    uint            maxChar;
    uint            titleLen;
    int             point[18];
    int currentVerticalPos;
    uint             lineWidth = UI_BORDER_WIDTH;
    //uint             twoLineWidth;
    t_box_item      *item;

    if (!ui || !box || !box->content)
        return (0);
    //w = (uint)box->dim[0];
    //h = (uint)box->dim[1];
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
    ///currentVerticalPos = lineWidth + 16; /// Original.
    currentVerticalPos = 16;
    switch (box->content->type)
    {
        case BOX_CONTENT_DISPLAY:
        {
            k = -1;
            while (++k < UI_BOX_CONTENT_MAX_ITEM  && k < box->content->n_item)
            {
                //int        pos[2];
                //uint        _w;
                item = &box->content->item[k];
                if (item->status.active == 0)
                    continue;
                ///if (item->pos[1] == -1) // Static Position. (bad)
                ///item->pos[1] = currentVerticalPos; /// Responsive.
                ///item->pos[1] = currentVerticalPos - point[1]; ///+ 16; /// Responsive.
                item->pos[1] = currentVerticalPos - point[1]; /// Responsive.
                //pos[0] = point[0] + item->pos[0] + lineWidth;
                //pos[1] = (int)item->pos[1] + (int)box->pos[1];
                //_w = box->dim[0] - (twoLineWidth + item->pos[0]);
                switch (item->type)
                {
                    case UI_ITEMTYPE_STRING:
                    {
                        currentVerticalPos = ui_getItemHeight_string(box, item, currentVerticalPos);
                        break;
                    }
                    case UI_ITEMTYPE_SIMPLE_BUTTON:
                    {
                        currentVerticalPos = ui_getItemHeight_simpleButton(item, currentVerticalPos);
                        break;
                    }
                    /*case UI_ITEMTYPE_PICTURE:
                    {
                        currentVerticalPos += item->dim[1];
                        break;
                    }*/
                    case UI_ITEMTYPE_NUMERICCHOOSER:
                    {
                        /// Default behavior
                        currentVerticalPos = ui_getItemHeight_numericChooser(item, currentVerticalPos);
                        break;
                    }
                    default :
                    {
                        currentVerticalPos += item->dim[1];
                        break;
                    }
                }
                /** Todo **/
                /// Refresh environement dimension for scrollar ui_newBox -> ui_getBoxEnvDim.c
                ///box->envDim[1] = currentVerticalPos + 16; /// Refresh Environement Dimension for scrollbar.
                /*ui_displayItem(mega, item);*/
            }
            break;
        }
        default : { break; }
    }
    ///currentVerticalPos += 64;
    ///currentVerticalPos += 32; /// Keep.
    ///currentVerticalPos += 48; /// Test.
    ///return (currentVerticalPos);
    return (currentVerticalPos);
}

uint        ui_getBoxEnvWidth(t_ui_box *box)
{
    t_box_item      *item;
    t_box_content   *content;
    //uint            maxDim;
    uchar           i;
    uint            ret;

    if (!box)
        return (0);
    ret = box->dim[0] - (16 + (2 * UI_BORDER_WIDTH));
    if (!(content = box->content))
        return (ret);
    item = &content->item[0];
    //maxDim = 0;
    i = -1;
    while (++i < UI_BOX_CONTENT_MAX_ITEM && i < box->content->n_item)
    {
        if (item->status.active != 0)
            if (item->type == UI_ITEMTYPE_PICTURE)
                if (item->dim[0] + (uint)item->pos[0] > ret)
                {
                    ret = item->dim[0] + (uint)item->pos[0] + (16 + (2 * UI_BORDER_WIDTH));
                    ///return (item->dim[0] - );
                }

        item++;
    }
    return (ret);
    ///return (box->dim[0] - (UI_BORDER_WIDTH * 2));
}

uint        ui_getBoxEnvHeight(t_userInterface *ui, t_ui_box *box)
{
    return (get_total_height_render(ui, box));
}

void        ui_getBoxEnvDim(t_userInterface *ui, t_ui_box *box)
{
    if (!box || !ui)
        return ;
    ///box->envDim[0] = box->dim[0];
    box->envDim[0] = ui_getBoxEnvWidth(box);
    box->envDim[1] = ui_getBoxEnvHeight(ui, box);
}
