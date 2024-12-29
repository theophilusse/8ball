#include "alphabet_tileset.h"

/**
 ** gprintf.c
 **
 ** Graphical Printf ;
 ** Display text in user interface context.
 **
 ** Usage:
 ** ;
 **
**/
/*
    void        gprintf(struct s_ftData_gTextData data, char *form, ...)
    {
        if (!form)
            return ;
    }
*/

/** Delete **/
///int      COMP_ui_ask_form(struct s_ftData_zone zone, const char *form, ...)
int        gprintf(struct s_ftData_gTextData data, char *form, ...)
{
    //t_mega                  *mega;
    va_list                 va;
    struct s_ftData_zone    zone;
    struct s_multitype      mt;
    struct s_ftData_parse   buf;
    //struct s_ui_font        font;
    uint                    len;
    char                    strBuf[STRING_SIZE];
    int                     basePos[2];
    uint                    tabNext;

    //mega = (t_mega *)global_mega;
    zone = data.dsp.zone;
    //font = data.font;
    buf.i = 0;
    buf.n = 0;
    while (form[buf.i] != '\0')
    {
        if (form[buf.i] == '%')
            buf.n++;
        buf.i++;
        if (buf.i >= STRING_SIZE)
            return (1);
    }
    if (buf.n == 0)
        return (1);
    va_start(va, form);
    buf.i = 0;
    buf.chunk[0] = (char *)&form[0];
    buf.chunk[1] = NULL;
    ///memcpy((void *)basePos, (const void *)zone.pos, sizeof(int) * 2);
    basePos[0] = zone.pos[0];
    basePos[1] = zone.pos[1];
    while (*buf.chunk[0] && buf.i < buf.n)
    {
        buf.sym[0] = *buf.chunk[0];
        buf.sym[1] = *(buf.chunk[0] + 1);
        if (buf.sym[0] == '%' && buf.sym[1] != '%')
        {
            if (buf.sym[1] == 's')
            {
                mt.ps = va_arg(va, char *);
                /** Replace :
                    ui_functionInput((void *)mt.ps, UI_DATATYPE_STRING, &zone, (void *)&tabNext);
                */
                ui_functionInput((void *)mt.ps, UI_DATATYPE_STRING, &zone, (void *)&tabNext);
            }
            if (buf.sym[1] == 'u')
            {
                mt.pu = va_arg(va, uint *);
                /** Replace :
                    ui_functionInput((void *)mt.pu, UI_DATATYPE_UINT, &zone, (void *)&tabNext);
                */
                ui_functionInput((void *)mt.pu, UI_DATATYPE_UINT, &zone, (void *)&tabNext);
            }
            if (buf.sym[1] == 'i')
            {
                mt.pi = va_arg(va, int *);
                /** Replace :
                    ui_functionInput((void *)mt.pi, UI_DATATYPE_INT, &zone, (void *)&tabNext);
                */
                ui_functionInput((void *)mt.pi, UI_DATATYPE_INT, &zone, (void *)&tabNext);
            }
            if (buf.sym[1] == 'd')
            {
                mt.pd = va_arg(va, double *);
                /** Replace :
                    ui_functionInput((void *)mt.pd, UI_DATATYPE_DOUBLE, &zone, (void *)&tabNext);
                */
                ui_functionInput((void *)mt.pd, UI_DATATYPE_DOUBLE, &zone, (void *)&tabNext);
            }
            if (buf.sym[1] == 'f')
            {
                mt.pf = va_arg(va, float *);
                /** Replace :
                    ui_functionInput((void *)mt.pf, UI_DATATYPE_FLOAT, &zone, (void *)&tabNext);
                */
                ui_functionInput((void *)mt.pf, UI_DATATYPE_FLOAT, &zone, (void *)&tabNext);
            }
            buf.i++;
            zone.maxDim[1] += 16;
            zone.pos[1] += 16;
            buf.chunk[0]++;
        }
        else
        {
            len = strlento(buf.chunk[0], '%');
            if (len > 0 && len < STRING_SIZE)
            {
                strncpy(strBuf, (const char *)buf.chunk[0], len * sizeof(char));
                strBuf[len] = '\0';
                printf("STRBUF[%s] n[%u]\n", strBuf, len); ///
                /** Replace :
                    charset_print(mega->screen, font.charset, 0, zone.pos[1], (const char *)strBuf);
                **/
                zone.pos[0] = basePos[0] + (16 * len);
                ///buf.chunk[0] += len != 0 ? len - 1 : 0;
                buf.chunk[0] += len != 0 ? len - 1 : 0;
            }
        }
        buf.chunk[0]++;
    }
    va_end(va);
    return (0);
}
