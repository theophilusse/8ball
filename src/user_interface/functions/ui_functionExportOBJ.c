#include "user_interface.h"

static int      validPath(char *str)
{
    if (!str || !*str)
        return (0);
    while (*str)
    {
        ///if (*str == '\\' || (*str > '9' && *str < '0') || (*str >  && ))
        if (*str == '\\' || *str == '[' || *str == ']' || *str == '(' || *str == ')' || *str == '{' || *str == '}' || *str == '/' ||
            *str == ':' || *str == '|' || *str == '?' || *str == '*' || *str == '\"' || *str == '<' || *str == '>')
            return (0);
        str++;
    }
    return (1);
}

int             ui_functionExportOBJ(void *pMega, int flag)
{
    char                    fileName[STRING_SIZE];
    struct s_ftData_zone    zone;
    uint                    tabNext;
    t_mega          *mega;
    uint            hMod;

    if (!(mega = (t_mega *)pMega))
        return (1);
    printf("Exporting OBJ %s.\n", fileName);
    fileName[0] = '\0';
    hMod = 0;
    zone = zone_upLeftCorner();
    ui_ask_form(zone, "Model a exporter: %uNom du fichier: %s", &hMod, &fileName);
    if (hMod < MAX_MODEL && mega->camera->data->model[hMod].active == 1)
    {
        printf("Exporting : [Model#%u]->[%s.obj]\n", hMod, fileName); ///
        if (validPath(fileName))
            export_obj(mega->camera, hMod, fileName);
        else
            export_obj(mega->camera, hMod, "scene");
    }
    return (0);

    charset_print(mega->screen, mega->ui->font.charset, 0, zone.pos[1], "Model index:");
    zone.pos[0] += 16 * strlen("Model index:");
    ui_functionInput((void *)&hMod, UI_DATATYPE_UINT, &zone, (void *)&tabNext);
    if (hMod < MAX_MODEL)
    {
        /**while (mega->camera->data->model[hMod].active == 1)**/
        if (mega->camera->data->model[hMod].active == 1)
        {
            zone.pos[0] += 16 * strlen("File Name:");
            zone.pos[1] += 16;
            zone.maxDim[1] += 16;
            charset_print(mega->screen, mega->ui->font.charset, 0, zone.pos[1], "File Name:");
            ui_functionInput((void *)&fileName, UI_DATATYPE_STRING, &zone, (void *)&tabNext);
            if (validPath(fileName))
                export_obj(mega->camera, hMod, fileName);
            else
                export_obj(mega->camera, hMod, "scene");
        }
    }
    return (0);
}
