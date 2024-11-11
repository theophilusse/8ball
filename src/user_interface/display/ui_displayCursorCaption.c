#include "user_interface.h"

/**
 ** Dsp. Caption
**/
void 		ui_displayCursorCaption(t_mega *mega, SDL_Surface *viewport)
{
	uint        len;

	if (!mega || !viewport)
        return ;
    if (mega->global->mouseCaption[0] != '\0')
    {
        if ((len = strlen(mega->global->mouseCaption)) >= (viewport->w / 16))
            len = (uint)(viewport->w / 16) - 1;
        if (len >= STRING_SIZE)
            len = STRING_SIZE - 1;
        mega->global->mouseCaption[len] = '\0';
        //len <<= 4;
        len *= 16;
        charset_print(viewport, mega->ui->font_bis.charset, mega->mouse.mousePos[0] + 18, mega->mouse.mousePos[1] + 18, mega->global->mouseCaption);
    }
}
