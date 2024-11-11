#include "frame.h"

void                draw_hud_screen(SDL_Surface *dst, t_mega* mega, struct s_tool tool)
{
    if (!dst)
        return ;
    clean_surface(dst);
    DEBUG ///
    /************** Infos Screen ****************/
    vertices_project(dst, mega->camera, mega->stcl->option.occlusion);
    DEBUG ///
    vertices_highlight(dst, mega->camera);
    DEBUG ///
    if (mega->selectStack)
        highlight_selection(dst, mega->camera, mega->viewport->w, mega->viewport->h, mega->selectStack, mega->stcl->option.occlusion);
    DEBUG ///
    if (tool.hud.active != 0)
        hud_refresh(dst, mega, &tool);
    DEBUG ///
    if (mega->selectStack && tool.hud.active == 1 && tool.type == TOOLTYPE_HUD_LENGTH)
        square(dst, tool.hud.org.coord[0] - 4, tool.hud.org.coord[1] - 4, 8, 8, (uchar *)_blue_crystal);
    DEBUG ///
    ///charset_print(dst, mega->ui->font.charset, 0, mega->viewport->h - 17, mega->tool[mega->currentTool].name);
    charset_print(dst, mega->ui->font.charset, 0, mega->viewport->h - 17, mega->tool[mega->currentTool].name);
    DEBUG ///
    /************** Infos Screen ****************/
}