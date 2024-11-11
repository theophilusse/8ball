#include "user_interface.h"

/// TODO
void        uint_processor(void *pVar, void *val, uchar instruction, void (*postProcessing)(void *, void *, uchar))
{
    void        (*instructionSet[3])(void *pVar, void *val, void (*ruleValue)(void *, void *, uchar));

    if (!pVar)
        return ;
    instructionSet[NATO_ALFA] = uint_copy;
    instructionSet[NATO_BRAVO] = uint_add;
    instructionSet[NATO_CHARLIE] = uint_get;
    return ;
}
