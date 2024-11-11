#include "input_manager.h"

static uint                    selection_getStackLength(t_select_node *selectStack)
{
    uint        ret;

    ret = 0;
    while (selectStack)
    {
        ret++;
        selectStack = selectStack->next;
    }
    return (ret);
}

static void             morpho_deselectGroup(t_select_node **selectStack, uint groupIndex)
{
    t_select_node   *node;
    t_select_node   *tracer;
    t_select_node   *refuse;

    if (!selectStack)
        return ;
    if (!(node = *selectStack))
        return ;

    /*** BEGIN - IS GROUP ***/
    if (node->vrt.ptr && (uint)node->vrt.ptr[3] == groupIndex)
    {
        if ((tracer = node->next)) /*** IF IS NOT UNIQUE ***/
        {
            if (tracer->vrt.ptr && (uint)tracer->vrt.ptr[3] == groupIndex) /*** FIND ENDING ***/
            {
                while (tracer && tracer->vrt.ptr && (uint)tracer->vrt.ptr[3] == groupIndex)
                    tracer = tracer->next;
                node = tracer;
                tracer = *selectStack;
                while (tracer != node)
                {
                    refuse = tracer;
                    tracer = tracer->next;
                    FREE(refuse);
                }
            }
        }
        else /*** IF IS UNIQUE ***/
        {
            /** ONLY ONE VERTICE **/
            *selectStack = NULL;
            FREE(node);
            return ;
        }
        tracer = NULL;
        *selectStack = node;
    }
    while (node)
    {

        tracer = node->next;
        if (tracer)
        {
            while (tracer && tracer->vrt.ptr && (uint)tracer->vrt.ptr[3] == groupIndex)
            {
                refuse = tracer;
                tracer = tracer->next;
                FREE(refuse);
            }
        }
        else
            return ;
        node->next = tracer;
        node = tracer;
    }
    return ;
}

static void             morpho_selectGroup(t_select_node **selectStack, uint i, double *v)
{
    t_select_node       *select;
    t_select_node       *vstack;
    uint                index;
    uint                adr;

    if (!v || !selectStack || v[1] < 4)
        return ;
    index = 0;
    while (++index < (uint)v[0])
    {
        adr = index * v[1];
        if ((uint)v[adr + 3] == i)
        {
            if (!(select = (t_select_node *)ALLOC(sizeof(struct s_select_node))))
                return ;
            select->payload = 0;
            select->index.model = 0; /// ?
            select->index.n = 0; /// ?
            select->vrt.model = 0; /// ?

            select->vrt.ptr = &v[adr];
            select->next = NULL;

            select->vrt.coord[0] = 500; /// Debug
            select->vrt.coord[1] = 500; ///  Debug
            copy_v3(select->vrt.ptr, select->mem.base); /// Test
            copy_v3(select->vrt.ptr, select->mem.cache); /// Test
            if (!(vstack = *selectStack))
                *selectStack = select;
            else
            {
                while (vstack->next)
                    vstack = vstack->next;
                vstack->next = select;
            }
        }
    }
}

int         user_morphoClick(t_mega *mega, int flg)
{
    t_tool                  *tool;
    t_morpho                *morpho;
    t_morpho_group          *part;
    uint            i;
    uint             cx;
    uint             cy;
    uchar           *pix;

    if (!mega || !mega->ui)
        return (1);
    if (mega->ui->morpho.active == -1)
        return (0);
    morpho = &mega->ui->morpho;
    cx = (uint)mega->mouse.onClick[0] - (uint)mega->ui->morpho.pos[0];
    cy = (uint)mega->mouse.onClick[1] - (uint)mega->ui->morpho.pos[1];
    i = -1;
    while (++i < MORPHO_PARTS_NUM)
    {
        part = &morpho->part[i];
        if (part->surf)
        {
            if (!(pix = (uchar *)getpixel_addr(part->surf, (int)cx, (int)cy)))
            {
                printf("ERROR\n");
                return (1);
            }
            if (*(pix + 3) != 0) /*** ADD GROUP TO SELECTION***/
                break;
        }
        else
        {
            if (cx >= part->pos[0] && cy >= part->pos[1] &&
                cx < part->pos[0] + part->dim[0] && cy < part->pos[1] + part->dim[1])
                break;
        }
    }
    if (i == MORPHO_PARTS_NUM)
        return (0);
    if (i == MORPHO_PARTS_NUM - 1)
        return ((int)(morpho->active = 0));
    else
        part->active = part->active == 0 ? 1 : 0;
    tool = &mega->tool[mega->currentTool];
    if (part->active == 0)
    {
        /*** GROUP: DESELECT (VERTICE[Z] == I) ***/
        morpho_deselectGroup(&mega->selectStack, i);
        selection_center(mega->selectStack, &tool->hud.org); //

        if (tool->proceed((void *)mega, 0))
            return (1);
        /// CENTER + HUD
    }
    else
    {
        /*** GROUP: SELECT (VERTICE[Z] == I) ***/
        morpho_selectGroup(&mega->selectStack, i, mega->camera->data->model[0].v);
        selection_center(mega->selectStack, &tool->hud.org); //
        tool->hud.active = 1;
        if (tool->proceed((void *)mega, 0))
            return (1);
        /// CENTER + HUD
    }
    tool->hud.active = (mega->selectStack) ? 1 : 0;
    return (0);
}
