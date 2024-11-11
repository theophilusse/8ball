#include "toolset.h"

void                        selection_resetCache(t_select_node *selection, double *org)
{
    while (selection)
    {
        if (selection->vrt.ptr)
        {
            copy_v3(selection->vrt.ptr, selection->mem.base);
            if (org)
            {
                ///DEBUG ///
                /*selection->select.cache[0] = selection->select.base[0] - org[0];
                selection->select.cache[1] = selection->select.base[1] - org[1];
                selection->select.cache[2] = selection->select.base[2] - org[2];*/
                selection->mem.cache[0] = selection->vrt.ptr[0] - org[0];
                selection->mem.cache[1] = selection->vrt.ptr[1] - org[1];
                selection->mem.cache[2] = selection->vrt.ptr[2] - org[2];
            }
            else
            {
                ///DEBUG ///
                selection->mem.cache[0] = 0;
                selection->mem.cache[1] = 0;
                selection->mem.cache[2] = 0;
            }
        }
        selection = selection->next;
    }
}

t_select_node         *selection_deselectPtr(t_select_node *selectionStack, double *ptr)
{
    t_select_node            *begin;
    t_select_node            *dump;
    t_select_node            *prev;

    if (!(begin = selectionStack))
        return (NULL);
    if (ptr == begin->vrt.ptr)
    {
        begin = begin->next;
        FREE(selectionStack);
        ///selectionStack = begin;
        return (begin);
    }
    // Test
    prev = selectionStack;
    selectionStack = selectionStack->next;
    // Test
    while (selectionStack && ptr != selectionStack->vrt.ptr)
    {
        prev = selectionStack;
        selectionStack = selectionStack->next;
    }
    if ((dump = selectionStack))
    {
        prev->next = selectionStack->next;
        FREE(dump);
    }
    return (begin);
}

int                   selection_isSelected(double *vrt, t_select_node *selection)
{
    if (!vrt || !selection)
        return (0);
    while (selection)
    {
        if (selection->vrt.ptr == vrt)
            return (1);
        selection = selection->next;
    }
    return (0);
}

t_select_node         *selection_deselectIndex(t_select_node *selectionStack, uint nodeIndex)
{
    t_select_node            *begin;
    t_select_node            *dump;
    uint                    i;

    if (!(begin = selectionStack))
        return (NULL);
    if (nodeIndex == 0)
    {
        begin = begin->next;
        FREE(selectionStack);
        return (begin);
    }
    i = 0;
    while (++i < nodeIndex && selectionStack)
        selectionStack = selectionStack->next;
    /*** if (!nodeStack)
        return (begin); ***/
    if ((dump = selectionStack->next))
    {
        selectionStack->next = dump->next;
        FREE(dump);
    }
    return (begin);
}

t_select_node        *copy_selection(t_select_node *selectionStack)
{
    t_select_node       *alc;
    t_select_node       *pCopy;
    t_select_node       *ret;

    ret = NULL;
    if (selectionStack)
    {
        if (!(ret = (t_select_node *)ALLOC(sizeof(struct s_select_node))))
            return (NULL);
        *ret = *selectionStack;
        ret->next = NULL;
        selectionStack = selectionStack->next;
        pCopy = ret;
    }
    while (selectionStack)
    {
        if (!(alc = (t_select_node *)ALLOC(sizeof(struct s_select_node))))
        {
            flush_selection(ret, NULL, 0, NULL);
            return (NULL);
        }
        *alc = *selectionStack;
        alc->next = NULL;
        pCopy->next = alc;
        pCopy = pCopy->next;
        selectionStack = selectionStack->next;
    }
    return (ret);
}

void                flush_selection(t_select_node *selectionStack, t_history **timeMachine, int flg, void *morpho_part)
{
    struct s_history_param      eventFlush;
    t_select_node               *dump;

    if (timeMachine && *timeMachine) /// CTRLZ
    {
        eventFlush = set_default_history_params();
        eventFlush.type = HISTORY_RELINK_SELECTION;
        eventFlush.selection = copy_selection(selectionStack);
        *timeMachine = history_add(*timeMachine, eventFlush);
    }
    while (selectionStack)
    {
        dump = selectionStack;
        selectionStack = selectionStack->next;
        dump->next = NULL;
        /** MEMORY LEAK **/
        ///FREE(dump); /** BUG **/
    }
    /*if (flg == 1) /// Test JAJA
        morpho_setAllActive((t_morpho_group *)morpho_part, 0);*/
}

t_select_node        *push_selection(struct s_select_vertice vrt, t_select_node *selectionStack)
{
    t_select_node           *selectNode;
    t_select_node           *begin;
    uint                    i;

    if (!vrt.ptr) // Test
        return (NULL);
    if (!(selectNode = selectionStack))
    {
        if (!(selectNode = (t_select_node *)ALLOC(sizeof(struct s_select_node))))
            return (NULL);
        begin = selectNode;
    }
    else
    {
        i = 0;
        begin = selectionStack;
        while (i != -1)
        {
            if (selectNode->vrt.ptr == vrt.ptr) /** If vertice is already selected, deselect it and increment the timeMachine**/
            {
                /*
                if (timeMachine && *timeMachine)
                {
                    hParam = set_default_history_params();
                    hParam.type = HISTORY_DESELECT;
                    hParam.vrt = selectNode->vrt;
                    hParam._d_u = (uint)i;
                    *timeMachine = history_add(*timeMachine, hParam);
                }
                */
                /** Vertice already selected : Action Deselect **/
                /*
                    BEEP /// DEBUG ///
                    DEBUG
                    printf("Comp [%p]:[%p] index[%u]\n", selectNode->vrt.ptr, vrt.ptr, i);///
                */
                ///return (selection_deselectIndex(begin, i));
                return (selection_deselectPtr(begin, vrt.ptr));
            }
            i++;
            if (selectNode->next)
                selectNode = selectNode->next;
            else
                i = -1;
        }
        if (!(selectNode->next = (t_select_node *)ALLOC(sizeof(struct s_select_node))))
        {
            flush_selection(selectionStack, NULL, 0, NULL);
            return (NULL);
        }
        selectNode = selectNode->next;
    }
    selectNode->index.model = (uint)vrt.model;
    selectNode->vrt = vrt;
    selectNode->mem.base[0] = vrt.ptr[0];
    selectNode->mem.base[1] = vrt.ptr[1];
    selectNode->mem.base[2] = vrt.ptr[2];
    selectNode->mem.cache[0] = 0;
    selectNode->mem.cache[1] = 0;
    selectNode->mem.cache[2] = 0;
    selectNode->next = NULL;
    return (begin);
}

t_select_node            *selectAllVertice(t_cam *c, char *isActive, t_select_node *toCopy, void *morpho_part)
{
    t_select_node               *ret;
    t_camdata                   *data;
    struct s_model              model;
    struct s_proj               *proj;
    struct s_select_vertice     vselect;
    int                         i;
    int                         j;
    int                         nv;
    uint                        vecsize;
    double                      *vrt;

    ret = NULL;
    if (!c || !(data = c->data))
        return (NULL);
    i = -1;
    while (++i < MAX_MODEL && data->model[i].active != 0)
    {
        model = data->model[i];
        if (!(vrt = model.v) || (nv = (model.nv / (int)(vrt[1]))) <= 0)
            return (ret);
        vecsize = model.v[1];
        j = 0;
        if ((proj = model.proj))
            while (++j < nv)
            {
                vselect.ptr = &vrt[j * vecsize];
                vselect.model = (char)i;
                ret = push_selection(vselect, ret);
                proj++;
            }
        if (isActive)
            *isActive = 1;
    }
    morpho_setAllActive((t_morpho_group *)morpho_part, 1);
    return (ret);
}

void            add_selected(double *v, t_select_node *selectStack, int preview, t_history **timeMachine)
{
    struct s_history_param      historyEvent;

    if (!v)
        return ;
    if (preview == 1) /// Preview (drag) v = move
    {
        while (selectStack)
        {
            if (selectStack->vrt.ptr)
            {
                ///add_v3(selectStack->select.base, v, selectStack->select.vertice);
                ///add_v3(selectStack->select.vertice, v, selectStack->select.vertice);
                //add_v3(selectStack->select.base, v, selectStack->select.cache);
                //copy_v3(selectStack->select.cache, selectStack->select.vertice);
                add_v3(selectStack->mem.cache, v, selectStack->mem.cache);
                add_v3(selectStack->mem.cache, selectStack->mem.base, selectStack->vrt.ptr);
            }
            selectStack = selectStack->next;
        }
        return ;
    }
    historyEvent = set_default_history_params();
    while (selectStack)
    {
        if (selectStack->vrt.ptr)
        {
            add_v3(selectStack->mem.cache, v, selectStack->mem.cache);
            add_v3(selectStack->mem.cache, selectStack->mem.base, selectStack->mem.base);
            copy_v3(selectStack->mem.base, selectStack->vrt.ptr);
            if (!selectStack->next && timeMachine)
                copy_v3(selectStack->mem.cache, (double *)historyEvent.vec);
            selectStack->mem.cache[0] = 0;
            selectStack->mem.cache[1] = 0;
            selectStack->mem.cache[2] = 0;
            //add_v3(selectStack->select.base, v, selectStack->select.vertice);
        }
        selectStack = selectStack->next;
    }
    if (timeMachine)
    {
        historyEvent.type = HISTORY_TRANSFORM;
        *timeMachine = history_add(*timeMachine, historyEvent);
    }
}

double          selection_measureAdj(double *org, double *axis, t_select_node *selectStack)
{
    double          anti_axis[3];
    double          ax0[3];
    double          ax1[3];
    double          ap0[3];
    double          ap1[3];
    double          ap2[3];

    double          hyp[3];
    double          hyp_len;
    double          ac;
    double          vec[3];
    double          pt_plane[3];
    double          max_adj_len;

    max_adj_len = 0;
    if (!org || !axis || !selectStack)
        return (0);
    inv_v3(axis, anti_axis);
    unit3(axis, ap0, NULL);
    unit3(anti_axis, ap1, NULL);
    while (selectStack)
    {
        if (selectStack->vrt.ptr)
        {
            /* Thales */
            /** Hyp **/
            sub_v3(selectStack->mem.base, org, hyp);
            hyp_len = length3(hyp);

            /** Angle **/
            unit3(hyp, ap2, NULL);
            copy_v3(ap0, ax0);
            copy_v3(ap1, ax1);
            if (dot_prod3(ap0, ap2) < DBL_EPSILON)
                copy_v3(ax1, ax0);
            ac = deg_to_rad(90 - get_angle_d3(ap2, ax0));
            selectStack->payload = sin(ac) * hyp_len; /// Imp.

            if (selectStack->payload > max_adj_len)
                max_adj_len = selectStack->payload; ///

        }
        selectStack = selectStack->next;
    }
    //**//
    return (max_adj_len);
}

///void            mtp_selected(double *org, double *v, t_select_node *selectStack)
void            mtp_selected(double v, double *axis, double *org, double max_dist, t_select_node *selectStack, int preview, t_history **timeMachine)
{
    double          hyp[3];
    double          vec[3];
    struct s_history_param      historyEvent;

    if (!v || !org || !axis || !selectStack)
        return ;
    while (selectStack)
    {
        if (selectStack->vrt.ptr)
        {
            sub_v3(selectStack->mem.base, org, hyp);

            /** Scaling **/
            hyp[0] += hyp[0] * ((v - 1) * axis[0]);
            hyp[1] += hyp[1] * ((v - 1) * axis[1]);
            hyp[2] += hyp[2] * ((v - 1) * axis[2]);

            add_v3(hyp, org, vec);
            /** Scaling **/

            /** Dump **/
            if (preview)
                copy_v3(vec, selectStack->vrt.ptr);
            else
            {
                copy_v3(vec, selectStack->mem.base);
                copy_v3(selectStack->mem.base, selectStack->vrt.ptr);

                selectStack->mem.cache[0] = 0;
                selectStack->mem.cache[1] = 0;
                selectStack->mem.cache[2] = 0;
            }
        }
        selectStack = selectStack->next;
    }
    if (timeMachine && preview == 0)
    {
        historyEvent = set_default_history_params();
        historyEvent.type = HISTORY_SCALE;
        historyEvent._f32 = (float)max_dist;
        historyEvent._f64 = v;
        copy_v3(axis, historyEvent.vec);
        *timeMachine = history_add(*timeMachine, historyEvent);
    }
}

void            rotate_selected(double v, double *axis, double *org, t_select_node *selectStack, int preview, t_history **timeMachine)
{
    double          drag_vec[3];
    struct s_history_param      historyEvent;

    if (!v || !axis)
        return ;
    while (selectStack)
    {
        if (selectStack->vrt.ptr)
        {
            if (preview)
            {
                copy_v3(selectStack->mem.cache, drag_vec);
                rot_vec3(axis, deg_to_rad(v), drag_vec);
                add_v3(drag_vec, org, selectStack->vrt.ptr);
            }
            else
            {
                copy_v3(selectStack->mem.cache, drag_vec);
                rot_vec3(axis, deg_to_rad(v), drag_vec);
                add_v3(drag_vec, org, selectStack->mem.base);
                copy_v3(selectStack->mem.base, selectStack->vrt.ptr);
                selectStack->mem.cache[0] = selectStack->mem.base[0] - org[0];
                selectStack->mem.cache[1] = selectStack->mem.base[1] - org[1];
                selectStack->mem.cache[2] = selectStack->mem.base[2] - org[2];
            }
            /*if (preview)
            {
                mtp_v3_by(selectStack->mem.cache, v, drag_vec);
                add_v3(drag_vec, org, selectStack->mem.vertice);
            }
            else
            {
                mtp_v3_by(selectStack->mem.cache, v, drag_vec);
                add_v3(drag_vec, org, selectStack->mem.base);
                copy_v3(selectStack->mem.base, selectStack->mem.vertice);
                selectStack->mem.cache[0] = selectStack->mem.base[0] - org[0];
                selectStack->mem.cache[1] = selectStack->mem.base[1] - org[1];
                selectStack->mem.cache[2] = selectStack->mem.base[2] - org[2];
            }*/
        }
        selectStack = selectStack->next;
    }
    if (preview == 0 && timeMachine)
    {
        historyEvent = set_default_history_params();
        historyEvent.type = HISTORY_ROTATE;
        copy_v3(axis, historyEvent.vec);
        historyEvent._f64 = v;
        *timeMachine = history_add(*timeMachine, historyEvent);
    }
}

void            resize_selected(double v, double *org, t_select_node *selectStack, int preview, t_history **timeMachine)
{
    double          drag_vec[3];
    struct s_history_param      historyEvent;

    while (selectStack)
    {
        if (selectStack->vrt.ptr)
        {
            if (preview)
            {

                selectStack->mem.cache[0] = selectStack->mem.base[0] - org[0];
                selectStack->mem.cache[1] = selectStack->mem.base[1] - org[1];
                selectStack->mem.cache[2] = selectStack->mem.base[2] - org[2];
                //DEBUG ///
                mtp_v3_by(selectStack->mem.cache, v, drag_vec);
                add_v3(drag_vec, org, selectStack->vrt.ptr);
            }
            else
            {
                //DEBUG ///
                mtp_v3_by(selectStack->mem.cache, v, drag_vec);
                add_v3(drag_vec, org, selectStack->mem.base);
                copy_v3(selectStack->mem.base, selectStack->vrt.ptr);
                selectStack->mem.cache[0] = selectStack->mem.base[0] - org[0];
                selectStack->mem.cache[1] = selectStack->mem.base[1] - org[1];
                selectStack->mem.cache[2] = selectStack->mem.base[2] - org[2];
            }
        }
        selectStack = selectStack->next;
    }
    if (preview == 0 && timeMachine)
    {
        historyEvent = set_default_history_params();
        historyEvent.type = HISTORY_RESIZE;
        historyEvent._f64 = v;
        *timeMachine = history_add(*timeMachine, historyEvent);
    }
}
