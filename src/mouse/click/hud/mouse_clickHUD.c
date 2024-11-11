#include "mouse.h"

/**
 ** mouse_clickHUD
 ** desc: Set tool->select_index to the right axis.
 ** input: tool + mouse coord on screen.
 ** return: 1 if clicked on HUD, 0 if missed.
**/
int                 mouse_clickHUD(t_tool *tool, int *coord)
{
    SDLMod          mod;
    int             hudClickMissed;

    if (!tool || !coord || tool->hud.active == 0)
        return (0);
    printf("tool active = %d\n", (int)tool->hud.active); ///
    hudClickMissed = 1;
    mod = SDL_GetModState();
    if (!(mod & KMOD_LCTRL)) ///|| (tool && tool->hud.active == 1) )
    {
        switch (tool->type)
        {
            case TOOLTYPE_HUD_ARROW:
            {
                hudClickMissed = mouse_clickHUDArrow(&tool->hud, coord);
                break;
            }
            case TOOLTYPE_HUD_ANGLE:
            {
                hudClickMissed = mouse_clickHUDAngle(&tool->hud, coord);
                break;
            }
            case TOOLTYPE_HUD_LENGTH:
            {
                hudClickMissed = mouse_clickHUDLength(&tool->hud, coord);
                break;
            }
        }
    }
    if (hudClickMissed)
        tool->hud.active = 1;
    else
        tool->hud.active = 2;
    printf("select_index %d\n", tool->hud.select_index);///
    /**
        RANDOM CRASH FROM HERE
    **/
    return (hudClickMissed == 1 ? 0 : 1);
}
