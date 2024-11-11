#ifndef MORPHO_H
#define MORPHO_H

    #include "8ball.h"

/// OLD
/****
typedef struct s_morpho_node
{
    struct s_morpho_node *parent;
    struct s_morpho_node *child[8];
    uint            groupId;
    uint            pos[2];
    SDL_Surface     *surface;
    char            name[32];
}               t_morpho_node;

typedef struct s_moprho
{
    SDL_Surface     *surface;
    t_morpho_node   *root;
}               t_morpho;
****/
/// OLD

    #define PATH_MORPHO             "rc/morpho/parts/"
    #define PATH_MORPHO_00          "rc/morpho/parts/base_morpho_00.bmp"

    void            morpho_setAllActive(t_morpho_group *part, uchar active);

#endif // MORPHO_H
