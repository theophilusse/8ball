#include "user_interface.h"

int             ui_functionReleaseModel(void *pMega, int flg)
{
    struct s_ftData_zone    zone;
	t_mega		            *mega;
	uint                    modelHandle;
	char                    charBuf[STRING_SIZE];
	uint                    tabNext;

	DEBUG ///
	if (!(mega = (t_mega *)pMega))
		return (1);
    zone = zone_upLeftCorner();
    ///ui_functionInput((void *)&modelHandle, UI_DATATYPE_UINT, &zone, (void *)&tabNext);
    /** int      ui_ask_form(struct s_ftData_zone zone, const char *form, ...); **/
    ///if (ui_ask_form(zone, "Wich model? : %s", (char *)charBuf))
    if (ui_ask_form(zone, "Quel model? : %u", &modelHandle))
    {
        DEBUG ///
        printf("Error! ui_ask_form\n");
        return (1);
    }
    DEBUG ///
	release_model(mega->camera->data, modelHandle);

	/********** TODO **************/
        /* MD5 sum */
        //history_delete(md5);
	/********** TODO **************/

	DEBUG ///
	gpu_modelRefresh(mega->stcl, mega->camera->data);
    DEBUG ///
    return (0);
}
