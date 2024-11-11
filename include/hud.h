#ifndef HUD_H
    #define HUD_H

    #include "8ball.h"

    struct s_hud_arrow          hud_newArrow(t_hud *hud, t_select_node *selectionStack);
    struct s_hud_angle          hud_newAngle(void);
    struct s_hud_length         hud_newLength(struct s_mouse mouse, t_tool *tool);

    struct s_axis           hud_initAxis(void);
    struct s_persp          hud_initPersp(void);
    struct s_hud            hud_init(void);

    void                        hud_draw(SDL_Surface *viewport, t_cam *camera, t_tool *tool, int *mousePos);
    void                        hud_drawArrow(SDL_Surface *viewport, struct s_hud_arrow arrow, t_tool *tool);
    void                        hud_drawAngle(SDL_Surface *viewport, struct s_hud_angle angle, t_tool *tool);
    void                        hud_drawLength(SDL_Surface *viewport, struct s_hud_length length, t_tool *tool, int *mousePos);

    int                         selection_center(t_select_node *selectStack, t_ref *center);
    int                         hud_project(t_cam *c, t_hud *hud, int RefProject);
#endif // HUD_H
