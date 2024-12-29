#include "toolset.h"

static int          isSelected(t_select_node *pSelection, double *ptr)
{
    t_select_node       *pNode;

    if (!ptr || !(pNode = pSelection))
        return (0);
    while (pNode)
    {
        if (pNode->vrt.ptr == ptr)
            return (1);
        pNode = pNode->next;
    }
    return (0);
}

int             tool_select(void *pmega, int flg)
{
    t_mega          *mega;
    SDLMod      mod;
    t_tool           *tool;
    //struct s_tool           toolSelect;
    struct s_mouse          mouse;
    struct s_select_vertice select;
    struct s_history_param      historyEvent;
    int                     select_err;
    //t_select_node           *pCopy;

    if (!(mega = (t_mega *)pmega))
        return (1);
    //pCopy = NULL;
    tool = &mega->tool[mega->currentTool];
    //toolSelect = mega->tool[TOOLSET_SELECT];
    mod = SDL_GetModState();
    if (tool->hud.active == 2 || (!(mod & KMOD_LCTRL) && tool->hud.active == 2) || //(!(mod & KMOD_LCTRL) && tool.hud.active == 2) ||
        tool->type == TOOLTYPE_HUD_LENGTH ) /// Priority given to HUD
        return (0);
    mouse = mega->mouse;

    mouse_clickSelect(mega->camera, tool, mouse.mousePos, mega->viewport, &select);
    /**if (!(mouse_clickSelect(mega->camera, &tool, mouse.mousePos, mega->viewport, &select)))
        return (0);**/
    historyEvent = set_default_history_params();
    if (!select.ptr) /// Missclick
    {
        if (tool->hud.active != 2 && mega->selectStack) /// If selection, deselect all
        {
            tool->hud.active = 0;
            if (mega->timeMachine) /// Save state
            {
                /// DeselectAll
                historyEvent.type = HISTORY_DESELECT_ALL;
                historyEvent.selection = copy_selection(mega->selectStack);
                flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = NULL;
                mega->timeMachine = history_add(mega->timeMachine, historyEvent);
                selection_center(mega->selectStack, &tool->hud.org);
            }
        }
        return (0);
    }
    else /// Click
    {
        if ((mod & KMOD_LCTRL)) /// Select PUT (CTRL Pressed)
        {
            if (isSelected(mega->selectStack, select.ptr))
            {
                /// DESELECT (REMOVE UNIQUE FROM LIST) (CTRL DOWN)
                historyEvent.type = HISTORY_DESELECT;
                historyEvent.vrt = select;
                historyEvent.selection = NULL;
                ///flush_selection(mega->selectStack, NULL, 1, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = selection_deselectPtr(mega->selectStack, select.ptr);
            }
            else
            {
                /// SELECT PUT
                historyEvent.type = HISTORY_SELECT;
                historyEvent.vrt = select;
                historyEvent.selection = NULL;
                if (!(mega->selectStack = push_selection(select, mega->selectStack)))
                {
                    if (historyEvent.selection)
                        flush_selection(historyEvent.selection, NULL, 0, NULL);
                    historyEvent.selection = NULL;
                    return (1); /// Error PUT
                }
            }
        }
        else
        {
            /// TEST
            /*if (isSelected(mega->selectStack, select.ptr))
            {
                /// DESELECT UNIQUE (CTRL UP)
                historyEvent.type = HISTORY_DESELECT;
                historyEvent.vrt = select;
                historyEvent.selection = NULL;
                mega->selectStack = selection_deselectPtr(mega->selectStack, select.ptr); /// Test
                ///flush_selection(mega->selectStack, NULL, 1, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = NULL;
            }
            else
            {*/
                /// Select UNIQUE
                historyEvent.type = HISTORY_SELECT_UNIQUE; ////////// BUG
                historyEvent.vrt = select;
                historyEvent.selection = mega->selectStack ? copy_selection(mega->selectStack) : NULL;
                flush_selection(mega->selectStack, NULL, 1, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = NULL;
                mega->selectStack = push_selection(select, mega->selectStack);
                /*
                if (!(mega->selectStack = push_selection(select, mega->selectStack)))
                {
                    DEBUG ///
                    if (historyEvent.selection)
                        flush_selection(historyEvent.selection, NULL, 0, NULL);
                    historyEvent.selection = NULL;
                    return (1); /// Error PUT
                }*/
            //}
        }
    }
    printf("Select: HISTORY_EVENT === %u\n", historyEvent.type); /// Debug
    mega->timeMachine = history_add(mega->timeMachine, historyEvent);
    selection_center(mega->selectStack, &tool->hud.org);
    return (0);
}
