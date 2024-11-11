#include "user_interface.h"

static int         filterCharInput_sym(SDLKey b, uchar datatype)
{
    int             ok;

    ok = 0;
    switch (datatype)
    {
        case UI_DATATYPE_INT:
        {
            if ((b >= 0 && b <= 9) || b == SDLK_COLON) /** Numeric Only **/
                ok = 1;
            break;
        }
        case UI_DATATYPE_UINT:
        {
            if (b >= 0 && b <= 9) /** Numeric Only **/
                ok = 1;
            break;
        }
        case UI_DATATYPE_FLOAT:
        {
            if ((b >= 0 && b <= 9) || b == SDLK_KP_PERIOD || b == SDLK_KP_MINUS) /** Numeric Only **/
                ok = 1;
            break;
        }
        case UI_DATATYPE_DOUBLE:
        {
            if ((b >= 0 && b <= 9) || b == SDLK_KP_PERIOD || b == SDLK_KP_MINUS) /** Numeric Only **/
                ok = 1;
            break;
        }
        case UI_DATATYPE_STRING:
        {
            /** TEST **/
            ok = 1;
            break;
        }
    }
    return (ok);
}

static char         get_char_qwerty(Uint8 sym)
{
    SDLMod      mod;
    uchar       shift;

    shift = 0;
    mod = SDL_GetModState();
    if ( (mod & MOD_SHIFT) )
    {
        printf("Shift Pressed\n"); /// Debug.
        shift = 1;
    }
    switch (sym)
    {
        case SDLK_0: return (!shift ? '0' : ' '); break;
        case SDLK_1: return (!shift ? '1' : ' '); break;
        case SDLK_2: return (!shift ? '2' : ' '); break;
        case SDLK_3: return (!shift ? '3' : ' '); break;
        case SDLK_4: return (!shift ? '4' : ' '); break;
        case SDLK_5: return (!shift ? '5' : ' '); break;
        case SDLK_6: return (!shift ? '6' : '-'); break;
        case SDLK_7: return (!shift ? '7' : ' '); break;
        case SDLK_8: return (!shift ? '8' : '_'); break;
        case SDLK_9: return (!shift ? '9' : ' '); break;
        case SDLK_a: return (!shift ? 'a' : 'A'); break;
        case SDLK_b: return (!shift ? 'b' : 'B'); break;
        case SDLK_c: return (!shift ? 'c' : 'C'); break;
        case SDLK_d: return (!shift ? 'd' : 'D'); break;
        case SDLK_e: return (!shift ? 'e' : 'E'); break;
        case SDLK_f: return (!shift ? 'f' : 'F'); break;
        case SDLK_g: return (!shift ? 'g' : 'G'); break;
        case SDLK_h: return (!shift ? 'h' : 'H'); break;
        case SDLK_i: return (!shift ? 'i' : 'I'); break;
        case SDLK_j: return (!shift ? 'j' : 'J'); break;
        case SDLK_k: return (!shift ? 'k' : 'K'); break;
        case SDLK_l: return (!shift ? 'l' : 'L'); break;
        case SDLK_m: return (!shift ? 'm' : 'M'); break;
        case SDLK_n: return (!shift ? 'n' : 'N'); break;
        case SDLK_o: return (!shift ? 'o' : 'O'); break;
        case SDLK_p: return (!shift ? 'p' : 'P'); break;
        case SDLK_q: return (!shift ? 'q' : 'Q'); break;
        case SDLK_r: return (!shift ? 'r' : 'R'); break;
        case SDLK_s: return (!shift ? 's' : 'S'); break;
        case SDLK_t: return (!shift ? 't' : 'T'); break;
        case SDLK_u: return (!shift ? 'u' : 'U'); break;
        case SDLK_v: return (!shift ? 'v' : 'V'); break;
        case SDLK_w: return (!shift ? 'w' : 'W'); break;
        case SDLK_x: return (!shift ? 'x' : 'X'); break;
        case SDLK_y: return (!shift ? 'y' : 'y'); break;
        case SDLK_z: return (!shift ? 'z' : 'Z'); break;
        case SDLK_SPACE: return (' '); break;
        /*
            case SDLK_a: return ('a'); break;
            case SDLK_b: return ('b'); break;
            case SDLK_c: return ('c'); break;
            case SDLK_d: return ('d'); break;
            case SDLK_e: return ('e'); break;
            case SDLK_f: return ('f'); break;
            case SDLK_g: return ('g'); break;
            case SDLK_h: return ('h'); break;
            case SDLK_i: return ('i'); break;
            case SDLK_j: return ('j'); break;
            case SDLK_k: return ('k'); break;
            case SDLK_l: return ('l'); break;
            case SDLK_m: return ('m'); break;
            case SDLK_n: return ('n'); break;
            case SDLK_o: return ('o'); break;
            case SDLK_p: return ('p'); break;
            case SDLK_q: return ('q'); break;
            case SDLK_r: return ('r'); break;
            case SDLK_s: return ('s'); break;
            case SDLK_t: return ('t'); break;
            case SDLK_u: return ('u'); break;
            case SDLK_v: return ('v'); break;
            case SDLK_w: return ('w'); break;
            case SDLK_x: return ('x'); break;
            case SDLK_y: return ('y'); break;
            case SDLK_z: return ('z'); break;
        */
        default: return ('\0'); break;
    }
    return ('\0');
}

static char         get_char_azerty(Uint8 sym)
{
    SDLMod      mod;
    uchar       shift;

    shift = 0;
    mod = SDL_GetModState();
    if ( (mod & MOD_SHIFT) )
    {
        printf("Shift Pressed\n"); /// Debug.
        shift = 1;
    }
    switch (sym)
    {
        case SDLK_0: return (!shift ? '0' : ' '); break;
        case SDLK_1: return (!shift ? '1' : ' '); break;
        case SDLK_2: return (!shift ? '2' : ' '); break;
        case SDLK_3: return (!shift ? '3' : ' '); break;
        case SDLK_4: return (!shift ? '4' : ' '); break;
        case SDLK_5: return (!shift ? '5' : ' '); break;
        case SDLK_6: return (!shift ? '6' : '-'); break;
        case SDLK_7: return (!shift ? '7' : ' '); break;
        case SDLK_8: return (!shift ? '8' : '_'); break;
        case SDLK_9: return (!shift ? '9' : ' '); break;
        case SDLK_a: return (!shift ? 'a' : 'A'); break;
        case SDLK_b: return (!shift ? 'b' : 'B'); break;
        case SDLK_c: return (!shift ? 'c' : 'C'); break;
        case SDLK_d: return (!shift ? 'd' : 'D'); break;
        case SDLK_e: return (!shift ? 'e' : 'E'); break;
        case SDLK_f: return (!shift ? 'f' : 'F'); break;
        case SDLK_g: return (!shift ? 'g' : 'G'); break;
        case SDLK_h: return (!shift ? 'h' : 'H'); break;
        case SDLK_i: return (!shift ? 'i' : 'I'); break;
        case SDLK_j: return (!shift ? 'j' : 'J'); break;
        case SDLK_k: return (!shift ? 'k' : 'K'); break;
        case SDLK_l: return (!shift ? 'l' : 'L'); break;
        case SDLK_m: return (!shift ? 'm' : 'M'); break;
        case SDLK_n: return (!shift ? 'n' : 'N'); break;
        case SDLK_o: return (!shift ? 'o' : 'O'); break;
        case SDLK_p: return (!shift ? 'p' : 'P'); break;
        case SDLK_q: return (!shift ? 'q' : 'Q'); break;
        case SDLK_r: return (!shift ? 'r' : 'R'); break;
        case SDLK_s: return (!shift ? 's' : 'S'); break;
        case SDLK_t: return (!shift ? 't' : 'T'); break;
        case SDLK_u: return (!shift ? 'u' : 'U'); break;
        case SDLK_v: return (!shift ? 'v' : 'V'); break;
        case SDLK_w: return (!shift ? 'w' : 'W'); break;
        case SDLK_x: return (!shift ? 'x' : 'X'); break;
        case SDLK_y: return (!shift ? 'y' : 'y'); break;
        case SDLK_z: return (!shift ? 'z' : 'Z'); break;
        ///case SDLK_SPACE: return (' '); break;
        case SDLK_SPACE: return ('_'); break;
        /*
            case SDLK_a: return ('a'); break;
            case SDLK_b: return ('b'); break;
            case SDLK_c: return ('c'); break;
            case SDLK_d: return ('d'); break;
            case SDLK_e: return ('e'); break;
            case SDLK_f: return ('f'); break;
            case SDLK_g: return ('g'); break;
            case SDLK_h: return ('h'); break;
            case SDLK_i: return ('i'); break;
            case SDLK_j: return ('j'); break;
            case SDLK_k: return ('k'); break;
            case SDLK_l: return ('l'); break;
            case SDLK_m: return ('m'); break;
            case SDLK_n: return ('n'); break;
            case SDLK_o: return ('o'); break;
            case SDLK_p: return ('p'); break;
            case SDLK_q: return ('q'); break;
            case SDLK_r: return ('r'); break;
            case SDLK_s: return ('s'); break;
            case SDLK_t: return ('t'); break;
            case SDLK_u: return ('u'); break;
            case SDLK_v: return ('v'); break;
            case SDLK_w: return ('w'); break;
            case SDLK_x: return ('x'); break;
            case SDLK_y: return ('y'); break;
            case SDLK_z: return ('z'); break;
        */
        default: return ('\0'); break;
    }
    return ('\0');
}

static int         inputManager_getChar(char *c, uchar datatype)
{
    SDL_Event       event;
    SDLMod          mod;
    SDLKey          b;
    int             ok;
    /***
    ***/
    /*struct s_vertice_dist hud_select;*/

    /*int                 lctrl_down = 0;*/
    /***
    ***/

    if (!c)
        return (0);
    /// TEST UI
    mod = SDL_GetModState();
    // message processing loop
    SDL_PollEvent(&event);
    // check for messages
    ok = 0;
    switch (event.type)
    {
        // exit if the window is closed

        case SDL_QUIT:
            return (-1);
        case SDL_VIDEORESIZE:
        {
            if (user_resizeWindow(global_mega, 1))
                return (-1);
            ok = 0;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                return (-1);
            return (-2);
        }
        case SDL_MOUSEMOTION:
        {
            ok = 0;
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            ok = 0;
            break;
        }
        case SDL_KEYDOWN:
        {
            ///*c = event.key.keysym.sym;
            /*
            flg = 0;
            if ((mod & KMOD_LCTRL) && mega.event.key.keysym.sym == SDLK_w)
                flg = 1;
            */
            if (event.key.keysym.sym == SDLK_LEFT)
                return (3);
            if (event.key.keysym.sym == SDLK_RIGHT)
                return (4);
            if (event.key.keysym.sym == SDLK_BACKSPACE)
                return (2);
            if (event.key.keysym.sym == SDLK_TAB)
                return (-3);
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return (-2);
            if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER)
                return (-1);
            b = event.key.keysym.sym;
            ///printf("HaltDebug: %u\n", b);
            ///if (filterCharInput_sym(b, datatype)) /** Numeric Only **/
            ///if (filterCharInput_sym(event.key.keysym.sym, datatype)) /** Numeric Only **/
            ///{
                ///b = (char)event.key.keysym.sym;
                ///b = event.key.keysym.unicode;
            ok = 1;
            if (datatype != UI_DATATYPE_STRING)
            {
                if (b == SDLK_0 || b == SDLK_KP0)
                    *c = '0';
                else if (b == SDLK_1 || b == SDLK_KP1)
                    *c = '1';
                else if (b == SDLK_2 || b == SDLK_KP2)
                    *c = '2';
                else if (b == SDLK_3 || b == SDLK_KP3)
                    *c = '3';
                else if (b == SDLK_4 || b == SDLK_KP4)
                    *c = '4';
                else if (b == SDLK_5 || b == SDLK_KP5)
                    *c = '5';
                else if (b == SDLK_6 || b == SDLK_KP6)
                    *c = '6';
                else if (b == SDLK_7 || b == SDLK_KP7)
                    *c = '7';
                else if (b == SDLK_8 || b == SDLK_KP8)
                    *c = '8';
                else if (b == SDLK_9 || b == SDLK_KP9)
                    *c = '9';
                else if (b == SDLK_MINUS || b == SDLK_KP_MINUS)
                {
                    if (datatype != UI_DATATYPE_UINT)
                        *c = '-';
                    else
                        return (0);

                }
                else if (b == SDLK_PERIOD || b == SDLK_KP_PERIOD)
                    *c = '.';
                else
                    ok = 0;
            }
            else
            {
                ok = 1;
                *c = get_char_azerty(b); /// Test.
                ///*c = get_char_azerty(event.key.keysym.scancode); /// Test.
                ///*c = event.key.keysym.sym;
                ///*c = event.key.keysym.unicode;
            }
            break;
        }
        case SDL_KEYUP:
        {
            ok = 0;
            break;
        }
    } // end switch
    return (ok);
}

static void     draw_numericChooser_value(t_mega *mega, uchar alpha, t_ui_box *box, t_box_item *item)
{
    char                        currentValue[STRING_SIZE];
    struct s_ftData_zone        zone;

    if (!mega || !box || !item)
        return ;
    zone.pos[0] = (item->pos[0] + 16) + box->pos[0];
    zone.pos[1] = item->pos[1] + box->pos[1];
    zone.dim[0] = item->dim[0] - 32;
    zone.dim[1] = 16;
    zone.maxDim[0] = box->pos[0] + (int)box->dim[0] - (UI_BORDER_WIDTH + 16);
    zone.maxDim[1] = box->pos[1] + (int)box->dim[1] - 1;
    zone.minDim[0] = box->pos[0] + 1;
    zone.minDim[1] = box->pos[1] + 23;
    valToStr(item->ptr, currentValue, item->status.param[2]);
    if (alpha)
        charset_printStopWidth(mega->screen, mega->ui->font.charset, zone.pos[0], zone.pos[1], zone.dim[0], currentValue);
    else
        charset_printStopWidth_noAlpha(mega->screen, mega->ui->font.charset, zone.pos[0], zone.pos[1], zone.dim[0], currentValue);
    SDL_Flip(mega->screen);
}

/** shell_fget **/
///void        ui_functionInput(void *data, uchar datatype, int *pos, uint *dim, int *maxDim, int *minDim)
void        ui_functionInput(void *data, uchar datatype, t_ftData_zone *zone, void *tabNext)
{
    ///int *pos, uint *dim, int *maxDim, int *minDim
    t_mega *mega;
    char        baseString[STRING_SIZE];
    char        inputString[STRING_SIZE];
    uint        index;
    int         code;
    char        c;
    ///Uint8        c;

    if (!(mega = (t_mega *)global_mega))
        return ;
    if (!data)
        return ;
    index = 0;

    memset(inputString, 0, sizeof(char) * STRING_SIZE);
    memset(baseString, 0, sizeof(char) * STRING_SIZE);
    /**
        valToStr(data, baseString, datatype);
        printf("Base String : %s\n", baseString);
        charset_printStopWidth_noAlpha(mega->screen, mega->ui->font_bis.charset, zone->pos[0], zone->pos[1], zone->dim[0], baseString);
    */
    square_dim_noAlpha(mega->screen, zone->pos[0], zone->pos[1], zone->dim[0], zone->dim[1], (uchar *)_deep_violet, zone->maxDim, zone->minDim); ///
    SDL_Flip(mega->screen);

    while ((code = inputManager_getChar(&c, datatype)) >= 0)
        if (code > 0)
        {
            if (code == 1)
            {
                inputString[index] = c;
                if (++index >= STRING_SIZE)
                    return ;
            }
            if (code == 2)
            {
                inputString[index] = '\0';
                if (index > 0)
                    index--;
                square_dim(mega->screen, zone->pos[0], zone->pos[1], 16, 16, (uchar *)_red, zone->maxDim, zone->minDim);
            }
            if (code == 3 && index > 0)
                index--;
            if (code == 4 && inputString[index + 1] != '\0')
                index++;
            square_dim_noAlpha(mega->screen, zone->pos[0], zone->pos[1], zone->dim[0], zone->dim[1], (uchar *)_deep_violet, zone->maxDim, zone->minDim); /// Refresh
            strToVal(inputString, data, datatype);
            ///ui_main((t_mega *)global_mega, ((t_mega *)global_mega)->ui);
            ///frame(*((t_mega *)global_mega), 0, 0); /// Test
            printf("InputSTRING [%s]\n", inputString);///
            ///charset_printStopWidth(mega->screen, mega->ui->font.charset, zone.pos[0], zone.pos[1], zone.dim[0], inputString);
            /*
            charset_printStopWidth(mega->viewport, mega->ui->font.charset, zone.pos[0], zone.pos[1], zone.dim[0], inputString);
            SDL_Flip(mega->viewport);
            */
            charset_printStopWidth_noAlpha(mega->screen, mega->ui->font.charset, zone->pos[0], zone->pos[1], zone->dim[0], inputString);
            SDL_Flip(mega->screen);
        }
    if (code == -2 || inputString[0] == '\0')/// && code != -3))
        strToVal(baseString, data, datatype);
        /// Todo.
    else
    {
        struct s_history_param      historyEvent;

        historyEvent = set_default_history_params();
        historyEvent.type = HISTORY_SET_VALUE;
        historyEvent.ptr = data;
        memcpy(historyEvent.buf, baseString, STRING_SIZE * sizeof(char));
        historyEvent._c_u = datatype;
        switch (datatype)
        {
            case UI_DATATYPE_INT: historyEvent._d_s = *((int *)data); break;
            case UI_DATATYPE_UINT: historyEvent._d_u = *((uint *)data); break;
            case UI_DATATYPE_FLOAT: historyEvent._f32 = *((float *)data); break;
            case UI_DATATYPE_DOUBLE: historyEvent._f64 = *((double *)data); break;
            case UI_DATATYPE_STRING: historyEvent.ptr = (void *)((char *)data); break;
        }
        mega->timeMachine = history_add(mega->timeMachine, historyEvent);
        if (code == -3)
            *((uchar *)tabNext) = 1;
    }
    ///
    return ;
}
