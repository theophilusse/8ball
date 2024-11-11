#include "user_interface.h"

/*
    typedef struct s_ui_box
    {
        uchar       active;
        uchar       z_index;
        uint        dim[2];
        int         pos[2];
        t_box_content   *content;
        char        title[UI_BOX_TITLE_STRLEN]; /// UI_BOX_TITLE_STRLEN
    }               t_ui_box;
    typedef struct s_userInterface
    {
        uchar       active;
        struct s_morpho            morpho;
        struct s_ui_box            box[UI_BOX_COUNT]; /// UI_BOX_COUNT
    }              t_userInterface;
*/

uchar                *ui_listActive(t_userInterface *ui, uchar printList)
{
    static uchar            *table[UI_BOX_COUNT];
    uint                    i;

    if (!ui)
        return (NULL);
    i = -1;
    if (printList == 1)
        while (++i < UI_BOX_COUNT)
            printf("[%s]:%u\n", ui->box[i].title, (table[i] = ui->box[i].active));
    else
        while (++i < UI_BOX_COUNT)
            table[i] = ui->box[i].active;
    return ((uchar *)table);
}

uchar                *ui_listZindex(t_userInterface *ui, uchar printList, uchar *table)
{
    uint                    i;

    if (!ui)
        return (NULL);
    i = -1;
    if (printList == 1)
        while (++i < UI_BOX_COUNT)
            ///printf("[%s]:%u\n", ui->box[i].title, (table[i] = ui->box[i].z_index));
            printf("[%s]:%u\n", ui->box[i].title, (table[i] = (uchar)i));
    else
        while (++i < UI_BOX_COUNT)
            ///table[i] = ui->box[i].z_index;
            table[i] = i;
    return ((uchar *)table);
}
