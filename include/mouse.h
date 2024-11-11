#ifndef MOUSE_H
    #define MOUSE_H

    #include "8ball.h"

    ///struct s_vertice_dist mouse_clickSelect(t_cam *c, int *coord, int *error);
    int                 mouse_clickHUD(t_tool *tool, int *coord);
    int                 mouse_clickHUDArrow(t_hud *hud, int *clickCoord);
    int                 mouse_clickHUDAngle(t_hud *hud, int *clickCoord);
    int                 mouse_clickHUDLength(t_hud *hud, int *clickCoord);

    int                 mouse_clickUI(t_ui_box *box, int *relClick);

    ///struct s_select_vertice mouse_clickSelect(t_cam *c, t_tool *tool, int *coord, int *error, SDL_Surface *viewport);
    int             mouse_clickSelect(t_cam *c, t_tool *tool, int *coord, SDL_Surface *viewport, t_select_vertice *vsel);

    int             mouse_motionArrow(void *pmega, int flg);
    int             mouse_motionAngle(void *pmega, int flg);
    int             mouse_motionLength(void *pmega, int flg);
#endif // MOUSE_H
