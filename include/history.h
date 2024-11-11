#ifndef HISTORY_H
#define HISTORY_H

    #include "8ball.h"

    #define HISTORY_IDLE                0
    #define HISTORY_RELINK_SELECTION    1
    #define HISTORY_DESELECT_ALL        2
    #define HISTORY_DESELECT            3
    #define HISTORY_SELECT_UNIQUE       4
    #define HISTORY_SELECT              5
    int                     history_typeSelection(uchar type);

    #define HISTORY_TRANSFORM           6
    #define HISTORY_SCALE               7
    #define HISTORY_ROTATE              8
    #define HISTORY_RESIZE              9

    #define HISTORY_SET_VALUE           10

    int              history_isAsync(uchar type);
    //int              history_typeSync(uchar type);

    void                history_display(t_history *timeMachine);
    struct s_history_param             set_default_history_params(void);
    void                               history_clear(t_history *timeMachine);
    t_history                          *history_new(void);
    t_history                          *history_add(t_history *timeMachine, struct s_history_param userEvent);
    t_history                          *history_undo(t_mega *mega, t_history *timeMachine);
    t_history                          *history_redo(t_mega *mega, t_history *timeMachine);
    t_history                       *history_removeNode(t_history *node);
    void                            history_updateDeletion(uint model_handle);

    void history_selectionRelink(t_mega *mega, t_history *timeMachine, int flg);
    void history_toolTransform(t_mega *mega, double *vec, uint undo);
    void history_toolScale(t_mega *mega, t_history *timeMachine, uint undo);
    void history_toolRotate(t_mega *mega, t_history *timeMachine, uint undo);
    void history_toolResize(t_mega *mega, t_history *timeMachine, uint undo);
    void             history_setVal(t_mega *mega, t_history *timeMachine, uint undo);

    /** Destructor **/
    void            release_history(t_history **timeMachine);

#endif // HISTORY_H
