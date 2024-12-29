#include "user_interface.h"

/*** DONT USE : see ui_swapPos.c ***/
void                    ui_foregroundAll(t_userInterface *ui, uchar handle) /** Used When Box Is Swapped Away **/
{
    //uint            i;
    t_ui_box        *box;

    if (!ui || handle > UI_BOX_COUNT || !(box = &ui->box[0]))
        return ;
    //i = -1;
    /*
    while (++i < UI_BOX_COUNT)
        if (box[i].z_index != 255) /// Foreach visible box
            box[i].z_index--; /// Decrease Z-Index
            */
    ui->sigRefresh = 1; /** Refresh UI **/
}

/*** DONT USE : see ui_swapPos.c ***/
void                    ui_foreground(t_userInterface *ui, uchar handle, uchar active)
{
    uint            i;
    t_ui_box        *box;
    struct s_ui_box swpBox;
    struct s_ui_box bufBox[UI_BOX_COUNT];

    printf("HANDLE : %d\n", handle); //
    if (!ui || handle >= UI_BOX_COUNT || !(box = &ui->box[0]))
        return ;
    DEBUG //
    ///box[handle].active = box[handle].active == 1 ? 0 : 1;
    ///box[handle].z_index = 0;
    /** Stack POP. **/
    swpBox = ui->box[handle];
    /*if (setActive == 1)
        swpBox.active = swpBox.active == 1 ? 0 : 1;
        */
    DEBUG //
    if (swpBox.active == 0 && active == 1)
        ui->boxCount++;
    DEBUG //
    swpBox.active = active;
    DEBUG //
    /*swpBox.z_index = 1;*/
    //return ; // DEBUG
    //box[0] = swpBox;
    //ui->box[0].active = 1;
    ///memcpy((void *)(&box[0]), &swpBox, sizeof(struct s_ui_box));
    if (handle > 0)
    {
        DEBUG //
        memcpy((void *)(bufBox) , (void *)(&box[0]) , (size_t)(sizeof(struct s_ui_box) * handle));
        DEBUG //
        memcpy((void *)(&box[1]) , (void *)(bufBox) , (size_t)(sizeof(struct s_ui_box) * handle));
        DEBUG //
    }
    DEBUG //
    printf("Box @ %p\n", box); // DEBUG
    /*typedef struct s_ui_box
    {
        uchar       active;

        uint        dim[2];
        uint        envDim[2];
        int         pos[2];
        t_box_content           *content;
        SDL_Surface             *viewport;
        t_ui_font               *font;
        struct s_ui_scrollbar    horizontal_bar;
        struct s_ui_scrollbar    vertical_bar;
        char        title[UI_BOX_TITLE_STRLEN]; /// UI_BOX_TITLE_STRLEN
    }               t_ui_box;*/
    printf("UI @ %p\n", ui);
    printf("box active = %u\n", box[0].active);// DEBUG
    printf("UI_BOX_COUNT: %d\n", UI_BOX_COUNT);
    printf("box: @ %p\n", box);
    //ui->box[0].active = 1; // DEBUG
    printf("ui->box[0]: title [%s]\n", ui->box[0].title);
    //memcpy(&ui->box[0], &swpBox, sizeof(struct s_ui_box));
    //return ;
    ///box[0] = swpBox; // TODO DEBUG CRASH
    //return ;

    /*old_handle = handle;*/
    ui->sigRefresh = 1;
    return ;
    /*
    i = -1;
    while (++i < UI_BOX_COUNT)
        if (box[i].z_index != 255)
            box[i].z_index++;
    box[handle].z_index = 0;
    ui->sigRefresh = 1;
    */
}
