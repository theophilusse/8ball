#include "history.h"

void         history_updateDeletion(uint model_handle)
{
    t_mega          *mega;
    t_history       *h;

    t_select_node   *sel;
    t_select_node   *prv;
    t_select_node   *rem;
    //t_model *m;

    if (!(mega = (t_mega *)global_mega))
        return ;
    if (!(h = mega->timeMachine))
        return ;
    while (h)
    {
        if ((sel = h->param.selection) /* || h->param. */)
        {
            ///(h->param.selection->index.model == model_handle)
            prv = NULL;
            while (sel)
            {
                if (sel->index.model == model_handle)
                {
                    if (prv)
                    {
                        prv->next = sel->next;
                        rem = sel;
                        sel = prv;

                    }
                    else
                    {
                        rem = sel;
                        sel = sel->next;
                        h->param.selection = sel;
                    }
                }
                if (h->param.selection != sel)
                    prv = sel;
                else
                    prv = NULL;
                sel = sel->next;
                FREE(rem);
            }
            /// Relink
            /*if ((h = history_removeNode(h)))
                return ;*/
        }
        h = h->redo;
    }
    return ;
}