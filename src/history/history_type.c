#include "history.h"

int                     history_typeSelection(uchar type)
{
    if (type == HISTORY_RELINK_SELECTION
        || type == HISTORY_DESELECT_ALL
        || type == HISTORY_SELECT
        || type == HISTORY_SELECT_UNIQUE
        || type == HISTORY_DESELECT)
        return (1);
    return (0);
}

int              history_isAsync(uchar type)
{
    if (type == HISTORY_SET_VALUE
        || type == HISTORY_RESIZE
        || type == HISTORY_ROTATE
        || type == HISTORY_SCALE
        || type == HISTORY_TRANSFORM
        || type == HISTORY_DESELECT_ALL
        || type == HISTORY_SELECT_UNIQUE
        || type == HISTORY_DESELECT)
        return (1);
    return (0);
}

/*
int              history_typeSync(uchar type)
{
    if (type == HISTORY_RELINK_SELECTION
        || type == HISTORY_SELECT_UNIQUE) /// Test
        return (1);
    return (0);
}
*/
