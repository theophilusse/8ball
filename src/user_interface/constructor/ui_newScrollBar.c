#include "user_interface.h"

struct s_ui_scrollbar       ui_defaultScrollBar(uchar axis)
{
    struct s_ui_scrollbar       bar;

    bar.axis = axis;
    bar.fPercent = 0; /// Keep.
    ///bar.fPercent = 0.5; /// Test.
    bar.shift = 0;
    bar.length = 0;
    return (bar);
};

struct s_ui_scrollbar       ui_newScrollBar(uchar axis)
{
    struct s_ui_scrollbar       bar;

    bar = ui_defaultScrollBar(axis);
    return (bar);
};
