#include "history.h"

static void         print_historyType(uchar type)
{
    switch (type)
    {
        case HISTORY_IDLE: { printf("HISTORY_IDLE"); break; } /// 0
        case HISTORY_RELINK_SELECTION: { printf("HISTORY_RELINK_SELECTION"); break; } /// 1
        case HISTORY_DESELECT_ALL: { printf("HISTORY_DESELECT_ALL"); break; } /// 2
        case HISTORY_DESELECT: { printf("HISTORY_DESELECT"); break; } /// 3
        case HISTORY_SELECT_UNIQUE: { printf("HISTORY_SELECT_UNIQUE"); break; } /// 4
        case HISTORY_SELECT: { printf("HISTORY_SELECT"); break; } /// 5
        case HISTORY_SET_VALUE: { printf("HISTORY_SET_VALUE"); break; } /// 5
    }
}

void                history_display(t_history *timeMachine)
{
    uchar           dspType;
    char            dspPtr;
    uint            count;
    t_history       *node;

    if (!(node = timeMachine))
    {
        printf("No time Machine !\n");
        return ;
    }
    printf("\n");
    while (node->undo)
        node = node->undo;
    count = 0;
    while (node)
    {
        dspType = node->param.type;
        dspPtr = node->param.selection ? 'O' : 'X';
        if (node == timeMachine)
            printf(">(%u|%c:%p)<-", dspType, dspPtr, node);
        else
            printf("(%u|%c:%p)-", dspType, dspPtr, node);
        node = node->redo;
        count++;
    }
    printf("/\n");
    printf("History: [%u] entry\n", count);
}
