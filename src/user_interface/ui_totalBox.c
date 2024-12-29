#include "user_interface.h"

uint 			ui_totalBox(t_userInterface *ui)
{
	uint 		count;
	uint 		i;

	if (!ui)
		return (0);
	count = 0;
	i = 0;
	while (i < UI_BOX_COUNT && strcmp(ui->box[i].title, UI_BOX_DEFAULT_TITLE) == 0)
    {
        i++;
        count++;
    }
	return (count - 1);
}
