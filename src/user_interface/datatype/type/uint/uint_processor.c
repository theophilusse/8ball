#include "user_interface.h"

/// TODO
void        uint_processor(void *pVar, void *val, uchar instruction, void (*postProcessing)(void *, void *, uchar))
{
    void        (*instructionSet[3])(void *pVar, void *val, void (*ruleValue)(void *, void *, uchar));

    if (!pVar)
        return ;
    instructionSet[NATO_ALFA] = (void (*)(void *, void *, void (*)(void *, void *, uchar)))uint_copy;
    instructionSet[NATO_BRAVO] = (void (*)(void *, void *, void (*)(void *, void *, uchar)))uint_add;
    instructionSet[NATO_CHARLIE] = (void (*)(void *, void *, void (*)(void *, void *, uchar)))uint_get;
    return ;
}
