#ifndef FRAME_H
    #define FRAME_H

    #include "8ball.h"

    void           vertices_project(SDL_Surface *viewport, t_cam *camera, uint occlusion); /// Need to be modified
    void           vertices_highlight(SDL_Surface *viewport, t_cam *camera /*, int *currentObject*/); /// Need to be modified
    void           highlight_selection(SDL_Surface *viewport, t_cam *camera, int w, int h, t_select_node *selectStack, uint occlusion);
    void           draw_hud_screen(SDL_Surface *dst, t_mega* mega, struct s_tool tool);
    void           draw_axis(SDL_Surface *s, uchar *color, double *axis, int w, int h, int x, int y, int size, SDL_Surface **tileset, char *name);

    void           hud_refresh(SDL_Surface *dst, t_mega *mega, t_tool *tool);
    void           draw_hud_screen(SDL_Surface *dst, t_mega* mega, struct s_tool tool);

    int            frame(t_mega *mega, int flg, int save_work_viewport);

    void           draw_model_stack(t_cam *c);
    void           print_debug(SDL_Surface *s, t_cam *c, SDL_Surface **charset, SDL_Surface **charset_bis, int x, int y);
    void           draw_f(t_cam *camera, double *zbuffer, int w, int h, uchar *rgb, t_model *model);/// Obsolete

#endif // FRAME_H


