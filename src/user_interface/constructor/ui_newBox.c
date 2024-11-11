#include "user_interface.h"

struct s_ui_function         set_default_function(void)
{
    struct s_ui_function        ft;

    ft.idx[0] = NULL;
    ft.idx[1] = NULL;
    ft.idx[2] = NULL;
    ft.idx[3] = NULL;
    return (ft);
}

struct s_box_item            set_default_box_item(void)
{
    struct s_box_item           item;

    item.blockSize = 0;
    item.dataSize = 0;
    item.dim[0] = 0;
    item.dim[1] = 0;
    item.pos[0] = 0;
    item.pos[1] = -1;
    item.ptr = NULL;
    item.type = UI_ITEMTYPE_EMPTY;
    item.status.active = -1;
    item.status.factor = 0.0;
    item.status.param[0] = 0;
    item.status.param[1] = 0;
    item.status.param[2] = 0;
    item.status.param[3] = 0;
    item.ft = set_default_function();
    return (item);
}

t_box_content         *set_default_box_content(void)
{
    uint                            i;
    t_box_content                   *b_content;

    if (!(b_content = (t_box_content *)ALLOC(sizeof(struct s_box_content))))
        return (NULL);
    b_content->color[0] = _gray_gray[0];
    b_content->color[1] = _gray_gray[1];
    b_content->color[2] = _gray_gray[2];
    b_content->color[3] = 255;
    b_content->type = 0;
    b_content->n_item = 0;
    i = -1;
    while (++i < 16)
        b_content->item[i] = set_default_box_item();
    return (b_content);
}

int              set_default_box(t_ui_box *box)
{
    if (!box)
        return (1);
    box->active = 0;
    box->content = NULL;
    box->dim[0] = 0;
    box->dim[1] = 0;
    box->pos[0] = 0;
    box->pos[1] = 0;
    box->envDim[0] = 0;
    box->envDim[1] = 0;
    /*box->z_index = 255;*/
    if (!(box->content = set_default_box_content()))
        return (1);
    box->viewport = NULL;
    box->title[0] = '\0';
    box->font = NULL;
    return (0);
}

static uchar       ui_countActiveItem(t_ui_box *box)
{
    t_box_content       *content;
    uchar               counter;
    uchar               k;

    if (!box)
        return (0);
    counter = 0;
    if (!(content = box->content))
        return (0);
    k = -1;
    while (++k < UI_BOX_CONTENT_MAX_ITEM)
        if (content->item[k].status.active == 1)
            counter++;
    return (counter);
}

int             ui_newBox(t_mega *mega, t_ui_box *box, uint index)
{
    struct s_ui_function        func;
    uint                        dim[2];
    uint                        width;

    if (!mega || !box || index < 0)
        return (1);
    /*box->pos[0] = 0;
    box->pos[1] = 0;
    box->dim[0] = (uint)mega->screen->w;
    box->dim[1] = (uint)mega->screen->h;*/
    box->pos[0] = 15;
    box->pos[1] = 15;
    box->dim[0] = 500;
    box->dim[1] = 300;
    box->envDim[0] = box->dim[0] - (2 * UI_BORDER_WIDTH);
    strcpy(box->title, UI_BOX_DEFAULT_TITLE);
    box->font = &mega->ui->font;
    box->horizontal_bar = ui_defaultScrollBar(0);
    box->vertical_bar = ui_defaultScrollBar(1);
    box->active = 0;
    switch (index)
    {
        case 0: /** Help **/
        {
            if (!box->content)
                break;
            /// FOREGROUND ///
            /*i = -1;
            while (++i < UI_BOX_COUNT)
                if (mega->ui->box[i].z_index != 255)
                    mega->ui->box[i].z_index++;*/
            /// FOREGROUND ///
            char            helpText_F1[] = "F1: Aide";
            char            helpText_F2[] = "F2: A-Propos";
            char            helpText_F3[] = "F3: Camera";
            char            helpText_numPad[] = "Pav-num: Direction camera";
            char            helpText_arrows[] = "Fleches/Pg-Up/Pg-Down: Position camera";
            char            helpText_mouse[] = "Souris (gauche): Selection\nSouris (droit): Point de vue\nSouris (molette): Distance focale";
            char            helpText[] = "Calcul gravure";
            //char            helpText[] = "\tA propos: Lorem Ipsumus\nLe Lorem Ipsum est simplement du faux texte employé dans la composition et la mise en page avant impression. Le Lorem Ipsum est le faux texte standard de l'imprimerie depuis les années 1500, quand un imprimeur anonyme assembla ensemble des morceaux de texte pour réaliser un livre spécimen de polices de texte. Il n'a pas fait que survivre cinq siècles, mais s'est aussi adapté à la bureautique informatique, sans que son contenu n'en soit modifié. Il a été popularisé dans les années 1960 grâce à la vente de feuilles Letraset contenant des passages du Lorem Ipsum, et, plus récemment, par son inclusion dans des applications de mise en page de texte, comme Aldus PageMaker.";
            //char            helpText[] = "Nunc blandit, urna id rhoncus gravida, mi lacus iaculis diam, quis placerat ante velit ut erat. Aenean massa lorem, consequat nec dolor sit amet, rutrum tincidunt erat. Fusce congue tempus risus, id imperdiet lectus dapibus ut. Proin mattis interdum ante accumsan faucibus. Cras a condimentum turpis. Nunc lectus nisl, feugiat at auctor non, bibendum quis quam. Ut interdum, turpis eget molestie suscipit, erat sem pharetra leo, eu maximus ipsum sem in dui. Suspendisse eleifend venenatis ante, sed semper sapien iaculis nec. Donec in augue rutrum, tincidunt tellus at, imperdiet sem. Vestibulum ac vestibulum erat. Morbi metus enim, posuere at elit in, dapibus sollicitudin eros. Praesent tincidunt sapien risus, tempus consectetur libero aliquam ut. Nam lectus nibh, mollis ut arcu id, viverra porta velit. Donec accumsan augue nunc. Sed eu eros volutpat, laoreet leo eget, scelerisque sem. Curabitur ultrices iaculis erat, a pretium ligula tempus ac. Curabitur ultricies cursus quam id congue. Donec cursus dui felis, id ornare ipsum euismod nec. Phasellus facilisis sagittis dui et bibendum. Suspendisse consectetur lacinia justo sit amet consectetur. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Interdum et malesuada fames ac ante ipsum primis in faucibus. In feugiat tristique suscipit. Sed et ipsum auctor, aliquet libero sed, facilisis metus. Suspendisse lacinia tempus ante, vitae vulputate ex vestibulum sed. Phasellus lacinia et risus vel ullamcorper. Phasellus quis eleifend diam. Duis ex dolor, dapibus id facilisis ac, sagittis vel dolor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. In nec pharetra lorem, consectetur gravida neque. Nullam aliquam sollicitudin feugiat. Phasellus sagittis tellus egestas sem placerat tristique. Sed nunc lectus, pellentesque sit amet commodo vel, sagittis vitae quam. Praesent fermentum dolor non lacinia bibendum. Nulla et nunc nec justo lobortis volutpat et et diam. Integer sagittis purus quis nisl vestibulum, nec iaculis magna fringilla.";
            char            helpText2[] = "Export DXF";
            char            helpText3[] = "Export OBJ";
            char            helpText4[] = "Import OBJ";
            char            helpText5[] = "Sup. Model";
            char            helpText6[] = "Quitter";

            if (!(box->viewport = new_surface32(box->dim[0], box->dim[1])))
                return (1);
            set_alpha(box->viewport, SDL_ALPHA_TRANSPARENT); /** Clear UI **/
            strcpy(box->title, "Aide");
            box->dim[0] = 640;
            box->dim[1] = 400;
            box->content->type = BOX_CONTENT_DISPLAY;
            box->content->item[0] = ui_newItemPicture(mega, box, mega->ui->assets.azerty, NULL);
            box->content->item[1] = ui_newItemText(mega, box, helpText_F1, NULL);
            box->content->item[2] = ui_newItemText(mega, box, helpText_F2, NULL);
            box->content->item[3] = ui_newItemText(mega, box, helpText_F3, NULL);
            box->content->item[4] = ui_newItemText(mega, box, helpText_numPad, NULL);
            box->content->item[5] = ui_newItemText(mega, box, helpText_arrows, NULL);
            box->content->item[6] = ui_newItemText(mega, box, helpText_mouse, NULL);
            box->content->item[7] = ui_newItemText(mega, box, helpText, NULL);
            ///box->content->item[1] = ui_newItemText(mega, box, helpText2, NULL);
            /*box->content->item[1] = ui_newItemText(mega, box, helpText2, NULL);
            box->content->item[2] = ui_newItemText(mega, box, helpText2, NULL);
            box->content->item[3] = ui_newItemText(mega, box, helpText2, NULL);*/
            /// Keep.
            dim[0] = 128;
            dim[1] = 64;
            box->content->item[8] = ui_newItemSimpleButton(mega->ui->assets.fall, "Fall", ui_functionFall, NULL, dim);
            box->content->item[9] = ui_newItemText(mega, box, helpText2, NULL);
            box->content->item[10] = ui_newItemSimpleButton(mega->ui->assets.save, "Sauvegarder", ui_functionExportDXF, NULL, dim);

            /// TEST .obj
            box->content->item[11] = ui_newItemText(mega, box, helpText3, NULL);
            box->content->item[12] = ui_newItemSimpleButton(mega->ui->assets.save, "Sauvegarder Scene", ui_functionExportOBJ, NULL, dim);

            box->content->item[13] = ui_newItemText(mega, box, helpText4, NULL);
            box->content->item[14] = ui_newItemSimpleButton(mega->ui->assets.save, "Importer Scene", ui_functionImportOBJ, NULL, dim);
            ///void        export_obj(t_cam *c, uint modelHandle);
            /// TEST .obj


            box->content->item[15] = ui_newItemText(mega, box, helpText5, NULL);
            box->content->item[16] = ui_newItemSimpleButton(mega->ui->assets.cross, "Release model", ui_functionReleaseModel, NULL, dim);

            dim[0] = 64;
            dim[1] = 64;
            box->content->item[17] = ui_newItemText(mega, box, helpText6, NULL);
            box->content->item[18] = ui_newItemSimpleButton(mega->ui->assets.bye, "Bye", ui_functionBye, NULL, dim);
            /** /// Debug Loop.
                uint kDebug;
                kDebug = 6;
                while (++kDebug < UI_BOX_CONTENT_MAX_ITEM - 1)
                    box->content->item[kDebug] = ui_newItemSimpleButton(mega->ui->assets.bye, "Bye", ui_functionBye, NULL, dim);
                box->content->item[kDebug] = ui_newItemText(mega, box, helpText3, NULL);
            */
            break;
        }
        case 1: /** About **/
        {
            if (!box->content)
                break;
            box->dim[0] = 570;
            box->dim[1] = 200;
            /// FOREGROUND ///
            /*i = -1;
            while (++i < UI_BOX_COUNT)
                if (mega->ui->box[i].z_index != 255)
                    mega->ui->box[i].z_index++;*/
            /// FOREGROUND ///
            char            aboutText[] = "Developpeur: ttrossea\n";
            strcpy(box->title, "A-Propos");
            box->content->type = BOX_CONTENT_DISPLAY;
            box->content->item[0] = ui_newItemPicture(mega, box, mega->ui->assets.nagscreen, NULL);
            box->content->item[1] = ui_newItemText(mega, box, aboutText, NULL);
            break;
        }
        case 2: /** Camera **/
        {
            if (!box->content)
                break;
            /// FOREGROUND ///
            /*i = -1;
            while (++i < UI_BOX_COUNT)
                if (mega->ui->box[i].z_index != 255)
                    mega->ui->box[i].z_index++;*/
            /// FOREGROUND ///
            strcpy(box->title, "Camera");
            box->content->type = BOX_CONTENT_DISPLAY;

            func = set_default_function();
            func.idx[0] = ui_functionInput;
            /*
            func.idx[0] = mega->input_manager[];///
            func.idx[1] = mega->input_manager[];///
            */
            /** box->content->item[2] = ui_newItem_numericChooser(mega, box, 5, NULL, (void *)&mega->currentTool, UI_DATATYPE_INT); **/
            ///box->content->item[2] = ui_newItem_numericChooser(mega, box, 5, NULL, (void *)&mega->stcl->option.display_cloud, UI_DATATYPE_UINT);
            box->content->item[0] = ui_newItemText(mega, box, "Distance Focal", NULL);
            box->content->item[1] = ui_newItem_numericChooser(mega, box, 4, NULL, (void *)&mega->camera->focal_distance, 0.01, UI_DATATYPE_DOUBLE, func);
            box->content->item[2] = ui_newItemText(mega, box, "Facteur d'agrandissement image", NULL);
            box->content->item[3] = ui_newItem_numericChooser(mega, box, 4, NULL, (void *)&mega->stcl->option.scale_factor, 0.01,  UI_DATATYPE_DOUBLE, func);
            box->content->item[4] = ui_newItemText(mega, box, "Resolution / x", NULL);
            box->content->item[5] = ui_newItem_numericChooser(mega, box, 4, NULL, (void *)&mega->stcl->option.mod_definition, 1, UI_DATATYPE_UINT, func);
            box->content->item[6] = ui_newItemText(mega, box, "Position camera (xyz)", NULL);

            ///box->content->item[1] = ui_newItem_numericChooser(mega, box, 4, NULL, (void *)&mega->camera->focal_distance, 0.5, UI_DATATYPE_DOUBLE, func);
            box->content->item[7] = ui_newItem_numericChooser(mega, box, 4, NULL, (void *)&mega->camera->o[0], 0.01, UI_DATATYPE_DOUBLE, func);
            box->content->item[8] = ui_newItem_numericChooser(mega, box, 4, NULL, (void *)&mega->camera->o[1], 0.01, UI_DATATYPE_DOUBLE, func);
            box->content->item[9] = ui_newItem_numericChooser(mega, box, 4, NULL, (void *)&mega->camera->o[2], 0.01, UI_DATATYPE_DOUBLE, func);

            /**
                box->content->item[5] = ui_newItem_numericChooser(mega, box, 16, NULL, (void *)&mega->camera->o[0], 0.01, UI_DATATYPE_DOUBLE, func);
                box->content->item[6] = ui_newItem_numericChooser(mega, box, 16, NULL, (void *)&mega->camera->o[1], 0.01, UI_DATATYPE_DOUBLE, func);
                box->content->item[7] = ui_newItem_numericChooser(mega, box, 16, NULL, (void *)&mega->camera->o[2], 0.01, UI_DATATYPE_DOUBLE, func);
            */
            /**
            box->content->item[5] = ui_newItem_numericChooser(mega, box, 16, NULL, (void *)&mega->camera->o[0], 0.01, UI_DATATYPE_DOUBLE, func);
            box->content->item[6] = ui_newItem_numericChooser(mega, box, 16, NULL, (void *)&mega->camera->o[1], 0.01, UI_DATATYPE_DOUBLE, func);
            box->content->item[7] = ui_newItem_numericChooser(mega, box, 16, NULL, (void *)&mega->camera->o[2], 0.01, UI_DATATYPE_DOUBLE, func);
            */
            break;
        }
    }
    box->content->n_item = ui_countActiveItem(box);
    ui_getBoxEnvDim(mega->ui, box);
    return (0);
}
