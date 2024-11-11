#include "user_interface.h"

///void            valToStr(item->ptr, (char *)valuePreview, dataType);
void            valToStr(void *in, char *out, uchar dataType)
{
    if (!in || !out)
        return ;
    switch (dataType)
    {
        case UI_DATATYPE_INT:
        {
            int_get(in, out);
            break;
        }
        case UI_DATATYPE_UINT:
        {
            uint_get(in, out);
            break;
        }
        case UI_DATATYPE_FLOAT:
        {
            float_get(in, out);
            break;
        }
        case UI_DATATYPE_DOUBLE:
        {
            double_get(in, out);
            break;
        }
        case UI_DATATYPE_STRING:
        {
            string_get(in, out);
            break;
        }
        default : break;
    }
}
