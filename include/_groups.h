#ifndef GROUPS_H
#define GROUPS_H

    typedef struct s_group
    {
        uchar          color[4];
        uint           n_vertice;
        uint           n_borderVertice;
        void            *morpho_node;
        float           normalVector[3];
    }

#endif
