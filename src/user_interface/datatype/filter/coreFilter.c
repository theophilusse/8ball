#include "user_interface.h"

void            *coreFilter(void *a, void *b, uchar datatype, uchar call)
{
    if (datatype >= TOTAL_DATATYPE_COUNT || call >= TOTAL_FILTER_COUNT)
        return (NULL);
    ///filterTable[datatype][call](a, b, );
    return ((void *)(filterTable[TOTAL_DATATYPE_COUNT][TOTAL_FILTER_COUNT]));
}
