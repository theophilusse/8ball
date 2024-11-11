#include "user_interface.h"

struct s_ui_font        ui_defaultFont(void)
{
    struct s_ui_font        font;

    font.fgColor[0] = _gray_gray[0];
    font.fgColor[1] = _gray_gray[1];
    font.fgColor[2] = _gray_gray[2];
    font.fgColor[3] = _gray_gray[3];
    font.bgColor[0] = _orange[0];
    font.bgColor[1] = _orange[1];
    font.bgColor[2] = _orange[2];
    font.bgColor[3] = _orange[3];
    font.fgColor_bis[0] = _blue_night[0];
    font.fgColor_bis[1] = _blue_night[1];
    font.fgColor_bis[2] = _blue_night[2];
    font.fgColor_bis[3] = _blue_night[3];
    font.bgColor_bis[0] = _blue_crystal[0];
    font.bgColor_bis[1] = _blue_crystal[1];
    font.bgColor_bis[2] = _blue_crystal[2];
    font.bgColor_bis[3] = _blue_crystal[3];
    font.dim = 16;
    ///font.charset = load_charset(font.fgColor, font.bgColor);
    font.charset = NULL;
    return (font);
};

struct s_ui_font        ui_newFont(uchar *fg_color, uchar *bg_color, float fSz)
{
    struct s_ui_font        font;

    font = ui_defaultFont();
    if (fg_color)
    {
        font.fgColor[0] = fg_color[0];
        font.fgColor[1] = fg_color[1];
        font.fgColor[2] = fg_color[2];
        font.fgColor[3] = fg_color[3];
    }
    if (bg_color)
    {
        font.bgColor[0] = bg_color[0];
        font.bgColor[1] = bg_color[1];
        font.bgColor[2] = bg_color[2];
        font.bgColor[3] = bg_color[3];
    }
    font.charset = load_charset(font.bgColor, font.fgColor);
    return (font);
}
