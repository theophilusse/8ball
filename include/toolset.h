#ifndef TOOLSET_H
    #define TOOLSET_H

    #include "8ball.h"

    #define TOOLTYPE_NONE               0
    #define TOOLTYPE_PROJECTIVE         1
    #define TOOLTYPE_HUD_LENGTH         2
    #define TOOLTYPE_HUD_ARROW          3
    #define TOOLTYPE_HUD_ANGLE          4

    #define MAX_CALLSTACK_CACHE         25
    /// CTRL-Z

    #define N_TOOL_END                      6
    #define N_TOOL_START                    2
    #define TOOLSET_NONE                0
    #define TOOLSET_SELECT              1
    #define TOOLSET_TRANSFORM           2
    #define TOOLSET_SCALE               3
    #define TOOLSET_RESIZE              4
    #define TOOLSET_ROTATE              5

    static struct s_tool             (*build_tool[TOOLSET_SIZE])(t_mega *, int *); /// tool constructor
    ///int             (*toolset[TOOLSET_SIZE])(t_mega *, int); /// Verify syntax array[]
    int                   selection_isSelected(double *vrt, t_select_node *selection);
    t_select_node         *selection_deselectIndex(t_select_node *selectionStack, uint nodeIndex);
    t_select_node         *selection_deselectPtr(t_select_node *selectionStack, double *ptr);
    t_select_node        *copy_selection(t_select_node *selectionStack);
    t_select_node        *push_selection(struct s_select_vertice vrt, t_select_node *selectionStack);
    void                        selection_resetCache(t_select_node *selection, double *org);
    void                        flush_selection(t_select_node *selectionStack, t_history **timeMachine, int flg, void *morpho_part);
    t_select_node            *selectAllVertice(t_cam *c, char *isActive, t_select_node *toCopy, void *morpho_part);
    double          selection_measureAdj(double *org, double *axis, t_select_node *selectStack);

    void            add_selected(double *v, t_select_node *selectStack, int preview, t_history **timeMachine);
    ///void            mtp_selected(double *v, t_select_node *selectStack);
    void            mtp_selected(double v, double *axis, double *org, double max_dist, t_select_node *selectStack, int preview, t_history **timeMachine);

    ///void            resize_selected(double v, double *axis, double mouseRelDot, double mouseAbsDot, double *org, t_select_node *selectStack, int preview);
    void            resize_selected(double v, double *org, t_select_node *selectStack, int preview, t_history **timeMachine);

    void            rotate_selected(double v, double *axis, double *org, t_select_node *selectStack, int preview, t_history **timeMachine);

    int             tool_init(t_mega *mega, int flg);
    int             tool_idle(void *mega, int flg);
    int             tool_select(void *pmega, int flg);
    int             tool_transform(void *mega, int flg);
    int             tool_scale(void *mega, int flg);
    int             tool_resize(void *mega, int flg);
    int             tool_rotate(void *mega, int flg);

    struct s_tool   tool_buildIdle(t_mega *mega, int *err);
    struct s_tool   tool_buildSelect(t_mega *mega, int *err);
    struct s_tool   tool_buildTransform(t_mega *mega, int *err);
    struct s_tool   tool_buildScale(t_mega *mega, int *err);
    struct s_tool   tool_buildResize(t_mega *mega, int *err);
    struct s_tool   tool_buildRotate(t_mega *mega, int *err);

#endif // TOOLSET_H
