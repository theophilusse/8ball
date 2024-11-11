#include "history.h"

static void           history_slectionCheckMorpho(t_mega *mega)
{
    uint                  i;
    uint                   morphoParts_comp[MORPHO_PARTS_NUM];
    uint                   morphoParts[MORPHO_PARTS_NUM];
    t_morpho_group         *mPart;
    t_select_node          *sNode;

    if (!mega)
        return ;
    if ((sNode = mega->selectStack) && sNode->index.model >= 0 && /** Valid input **/
        mega->camera && mega->camera->data && mega->camera->data->model[sNode->index.model].v && /** Pointers **/
        (uint)(mega->camera->data->model[sNode->index.model].v[1]) == 4) /** 4bytes per vertices **/
    {
        i = -1;
        while (++i < MORPHO_PARTS_NUM)
            morphoParts[i] = 0;
        i = -1;
        while (++i < MORPHO_PARTS_NUM)
            morphoParts_comp[i] = 0;
        i = -1;
        while (++i < (uint)(mega->camera->data->model[sNode->index.model].v[0]))
        {
            if ((uint)(mega->camera->data->model[ sNode->index.model ].v[(4 * (i+1)) + 3]) < MORPHO_PARTS_NUM)
                morphoParts_comp[ (uint)(mega->camera->data->model[sNode->index.model].v[(4 * (i+1)) + 3]) ] += 1; /** Count **/
        }
        while (sNode) /** For each node **/
        {
            if (sNode->index.model >= 0
                && mega->camera->data->model[sNode->index.model].v
                && (uint)(mega->camera->data->model[sNode->index.model].v[1]) == 4
                && (uint)(sNode->vrt.ptr[4]) >= 0 && (uint)(sNode->vrt.ptr[3]) <= 64)
                morphoParts[(uint)sNode->vrt.ptr[3]]++; /** Save Associated Group **/
            sNode = sNode->next;
        }
        mPart = &mega->ui->morpho.part[0];
        i = -1;
        while (++i < MORPHO_PARTS_NUM)
        {
            mPart->active = ( morphoParts_comp[i] == morphoParts[i] ? 1 : 0); /// TODO
            mPart++;
        }
    }
}

void history_selectionRelink(t_mega *mega, t_history *timeMachine, int flg)
{
    if (!mega || !timeMachine)
        return ;
    ///BEEP_WARNING
    mega->selectStack = copy_selection(timeMachine->param.selection);
    if (flg == 1)
        history_slectionCheckMorpho(mega);
}
