#include "user_interface.h"

///void            valToStr(item->ptr, (char *)valuePreview, dataType);
void            strToVal(char *in, void *out, uchar dataType)
{
    if (!in || !out)
        return ;
    switch (dataType)
    {
        case UI_DATATYPE_INT:
        {
            int_set(in, out);
            break;
        }
        case UI_DATATYPE_UINT:
        {
            uint_set(in, out);
            break;
        }
        case UI_DATATYPE_FLOAT:
        {
            float_set(in, out);
            break;
        }
        case UI_DATATYPE_DOUBLE:
        {
            double_set(in, out);
            break;
        }
        case UI_DATATYPE_STRING:
        {
            string_set(in, out);
            break;
        }
        default : break;
    }
}
