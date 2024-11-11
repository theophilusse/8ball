#include "user_interface.h"

void            coreInstruction(void *a, void *b, uchar datatype, uchar call)
{
    if (datatype >= TOTAL_DATATYPE_COUNT || call >= TOTAL_INSTRUCTION_COUNT)
        return ;
    instructionTable[datatype][call](a, b);
}
