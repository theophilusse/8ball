#include "input_manager.h"

static void         increment_group_selection(t_select_node *vstack, int inc) /*Misc*/
{
    if (!vstack)
        return ;
    while (vstack)
    {
        if (vstack->vrt.ptr)
        {
            vstack->vrt.ptr[3] = vstack->vrt.ptr[3] + (double)inc;
            if (vstack->vrt.ptr[3] < 0)
                vstack->vrt.ptr[3] = 0;
        }
        vstack = vstack->next;
    }
}

int         user_keydown(t_mega *mega, int flg)
{
    static int                  dCoolDown = 0;
    static int                  static_blockInput[4] = { 0, 0, 0, 0, };
    struct s_history_param      historyEvent;
    t_tool                      *tool;
    SDLMod                      mod;
    /**
        Uint8                *keystate;
        int                 numkey;
    **/

    if (!mega)
        return (1);

    // exit if ESCAPE is pressed
    if (mega->event.key.keysym.sym == SDLK_ESCAPE)
    {
        /**
        print_segment(&mega->camera->data->model[0], 0);
        print_segment(&mega->camera->data->model[0], 1);
        print_segment(&mega->camera->data->model[0], 2);
        **/
        return (1);
    }

    /** History **/
    if ((flg == 1 || flg == 2) && (++dCoolDown >= 20 || mega->keyboardUp == 1)) /** Semi-Blocking **/
    {
        if (flg == 1) /** Check for key combination **/
        {
            printf("<Ctrl+Z> is pressed. [reverse_call_stack]\n");
            /** Undo **/
            mega->timeMachine = history_undo(mega, mega->timeMachine);
            mega->keyboardUp = 1;
        }
        if (flg == 2)
        {
            printf("<Ctrl+Maj+Z> is pressed. [redo_call_stack]\n");
            /** Redo **/
            mega->timeMachine = history_redo(mega, mega->timeMachine);
            mega->keyboardUp = 1;
        }
        dCoolDown = 0;
    }

    /*mega->input_manager[0](&mega, 0);*/
    if (mega->event.key.keysym.sym == SDLK_o) // Adjust Picture Scale ++
        mega->stcl->option.scale_factor += 0.001;
    if (mega->event.key.keysym.sym == SDLK_p) // Adjust Picture Scale --
        mega->stcl->option.scale_factor -= 0.001;

    camera_event(mega->camera, mega->event.key.keysym.sym);
    /** /// Refresh HUD perspective ; present in cameraDrag
    tool_projectRef(mega, mega->camera, &mega->toolRef);
    copy_v3(mega->toolRef.org, mega->hud_arrow.vertice);
    copy_v3(mega->toolRef.org, mega->hud_angle.vertice);
    **/

    /** Non blocking keys **/
    if (mega->keyboardUp == 0) /// Barier one input
        return (0);
    /** Blocking keys **/

    /** GPU Options **/
    if (mega->event.key.keysym.sym == SDLK_1) // Display Model Switch
        mega->input_manager[2](mega, 0);
    if (mega->event.key.keysym.sym == SDLK_2) // Display Cloud Switch
        mega->input_manager[3](mega, 0);

    uchar _h;
    if (mega->event.key.keysym.sym == SDLK_F1) // Edit mode Switch
    {
        printf("F1: Help\n");
        ui_getBoxHandle_byTitle(mega->ui, "Aide", &_h);
        ui_swapBox(mega->ui, _h, mega->ui->box[_h].active == 0 ? 1 : 0);
    }
    if (mega->event.key.keysym.sym == SDLK_F2) // Edit mode Switch
    {
        printf("F2: About\n");
        ui_getBoxHandle_byTitle(mega->ui, "A-Propos", &_h);
        /// CRASH
        ui_swapBox(mega->ui, _h, mega->ui->box[_h].active == 0 ? 1 : 0);
    }
    if (mega->event.key.keysym.sym == SDLK_F3) // Edit mode Switch
    {
        printf("F3: Camera\n");
        ui_getBoxHandle_byTitle(mega->ui, "Camera", &_h);
        printf("Camera handle %u\n", _h); /// 255 !!!!!!!!!!!!
        ui_swapBox(mega->ui, _h, mega->ui->box[_h].active == 0 ? 1 : 0);
    }
    if (mega->event.key.keysym.sym == SDLK_F9) // Edit mode Switch
    {
        printf("Exporting.\n");
        export_cloud_to_dxf(mega, mega->picture->w * mega->picture->h);//
        /*if (mega->picture->w <= 100 && mega->picture->h <= 100)
            export_cloud_to_dxf(mega->stcl, mega->picture->w * mega->picture->h);
        else
            export_cloud_to_dxf(mega->stcl, 100 * 100);*/
    }

    tool = &mega->tool[mega->currentTool];

    if (mega->event.key.keysym.sym == SDLK_8) // Edit mode Switch
    {
        printf("Switch occlusion ");
        mega->stcl->option.occlusion = mega->stcl->option.occlusion == 1 ? 0 : 1;
        if (mega->stcl->option.occlusion)
            printf("[ON]\n");
        else
            printf("[OFF]\n");
    }
    if (mega->event.key.keysym.sym == SDLK_9) // Edit mode Switch
    {
        printf("Switch Edit ");
        mega->stcl->option.edit_mode = mega->stcl->option.edit_mode == 1 ? 0 : 1;
        if (mega->stcl->option.edit_mode == 1)
        {
            /**mega->hud_arrow.active = 0;
            mega->toolRef.active = 0;*/
            /**if (tool.type == TOOLTYPE_HUD_ARROW)
                *((t_hud_arrow *)tool.hud.data.buf) = new_hud_arrows(mega->viewport, mega->camera, mega->viewport->w, mega->viewport->h, mega->selectStack, &tool.hud.org); // Test
            if (tool.type == TOOLTYPE_HUD_ANGLE)
                *((t_hud_angle *)tool.hud.data.buf) = new_hud_angle(mega->viewport, mega->camera, mega->viewport->w, mega->viewport->h, mega->selectStack, &tool.hud.org); // Test
            **/
            tool->hud.active = -1;
            printf("[ON]\n");
        }
        else
        {
            /**if (mega->tool[mega->tool].type == TOOLTYPE_HUD)
                mega->hud_arrow.active = 1;
            mega->toolRef.active = 1;*/
            tool->hud.active = 0;
            printf("[OFF]\n");
        }
    }
    if (mega->event.key.keysym.sym == SDLK_0) // Display HUD Switch
    {
        printf("Switch HUD ");
        mega->stcl->option.display_log = mega->stcl->option.display_log == 1 ? 0 : 1;
        if (mega->stcl->option.display_log == 1)
            printf("[ON]\n");
        else
            printf("[OFF]\n");
    }
    if (mega->event.key.keysym.sym == SDLK_f && static_blockInput[0] == 0) // Display HUD Switch
    {
        static_blockInput[0] = 1;
        printf("user_computeCloud ");
        if (mega->input_manager[USER_COMPUTE_CLOUD](mega, 0))
            return (1);
    }
    else
        static_blockInput[0] = 0;
    if (mega->stcl->option.edit_mode == 1)
    {
        if (mega->event.key.keysym.sym == SDLK_t && mega->mouse.mouseButtonUp == 1) /// T <- Switch tool
        {
            /*** mega->tool = mega->tool == TOOLSET_TRANSFORM ? TOOLSET_SCALE : TOOLSET_TRANSFORM; ***/
            ///mega->tool++;
            if (mega->input_manager[USER_MOUSE_BUTTON_UP](mega, 0))
                return (1);
            mega->mouse.mouseButtonUp = 1; /// Test
            mega->currentTool++;
            if (mega->currentTool == N_TOOL_END)
                mega->currentTool = N_TOOL_START;
            tool = &mega->tool[mega->currentTool];
            // Marker
            if (mega->selectStack)
                tool->hud.active = 1;// Test
            else
                tool->hud.active = 0;
            if (tool->proceed((void *)mega, 0)) // Test
                return (1);
            printf("User Tool : [%d][%s]\n", mega->currentTool, tool->name);
            /*if (mega->input_manager[USER_COMPUTE_CLOUD](mega, 0))
                return (1);*/
        }
        if (mega->event.key.keysym.sym == SDLK_q) /// A <- AZERTY
        {
            if (mega->selectStack)
            {
                ///flush_selection(mega->selectStack, &mega->timeMachine, 1, (void *)&mega->ui->morpho.part[0]);
                flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                mega->selectStack = NULL;
                tool->hud.active = 0;
                if (mega->timeMachine) /// CTRLZ : Save state
                {
                    /// DeselectAll : Test.
                    historyEvent = set_default_history_params();
                    historyEvent.type = HISTORY_DESELECT_ALL;
                    historyEvent.selection = copy_selection(mega->selectStack);
                    flush_selection(mega->selectStack, NULL, 0, (void *)&mega->ui->morpho.part[0]);
                    mega->selectStack = NULL;
                    mega->timeMachine = history_add(mega->timeMachine, historyEvent);
                    selection_center(mega->selectStack, &tool->hud.org);
                    /* /// Org.
                        historyEvent = set_default_history_params();
                        historyEvent.type = HISTORY_RELINK_SELECTION;
                        historyEvent.selection = NULL;
                        mega->timeMachine = history_add(mega->timeMachine, historyEvent);
                    */
                }
            }
            else
            {
                mega->selectStack = selectAllVertice(mega->camera, &tool->hud.active, mega->selectStack, (void *)&mega->ui->morpho.part[0]);
                // Marker
                ///hud_project(mega, mega->camera, &tool->hud, 1);
                if (tool->proceed((void *)mega, 0))
                    return (1);
                if (mega->timeMachine) /// CTRLZ : Save state
                {
                    /*historyEvent = set_default_history_params();
                    historyEvent.type = HISTORY_DESELECT_ALL;
                    historyEvent.selection = copy_selection(mega->selectStack);
                    mega->selectStack = NULL;
                    mega->timeMachine = history_add(mega->timeMachine, historyEvent);
                    selection_center(mega->selectStack, &tool->hud.org);*/

                    historyEvent = set_default_history_params();
                    historyEvent.type = HISTORY_RELINK_SELECTION;
                    historyEvent.selection = copy_selection(mega->selectStack);
                    mega->timeMachine = history_add(mega->timeMachine, historyEvent);
                }
            }
            /**
                history_display(mega->timeMachine); /// Debug
            */
        }
        if (mega->ui->active == 1)
        {
            if (mega->ui->morpho.active == 1)
            {
                if (mega->event.key.keysym.sym == SDLK_z) /// W <- QWERTY
                    increment_group_selection(mega->selectStack, 1);
                if (mega->event.key.keysym.sym == SDLK_x) /// X <- QWERTY
                    increment_group_selection(mega->selectStack, -1);
            }
            if (mega->event.key.keysym.sym == SDLK_TAB)
            {
                if (mega->ui->morpho.active == 0)
                    mega->ui->morpho.active = 1;
                else if (mega->ui->morpho.active == 1)
                    mega->ui->morpho.active = 0;
            }
        }
    }
    if (0 && mega->event.key.keysym.sym == SDLK_g) /// G <- AZERTY ! deadcode !
    {
        /*** EXPORT MODEL C FORMAT ***/
        print_segment(&mega->camera->data->model[0], 0);
        print_segment(&mega->camera->data->model[0], 1);
        print_segment(&mega->camera->data->model[0], 2);
    }
    /* printf("SYM:[%u]\n", mega->event.key.keysym.sym); /// Debug KeySym */
    return (0);
}
