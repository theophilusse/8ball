#include "HeightMap.h"

/*

    typedef struct         s_button
    {
        uchar           color[4];
        int             active;
        int             state;
        char            ptrtype;
        void            *ptr;
        SDL_Surface     *s;
        SDL_Surface     *picto;
    }                      t_button;
    #define BUTTON_IDLE     0
    #define BUTTON_CLICK    1
    #define BUTTON_LOCK     2

    #define BUTTON_INACTIVE 0
    #define BUTTON_ACTIVE   1
*/

void        toolbar_input_processing(t_toolbar *bar, int *click, Uint8 button)
{
    int             i;
    t_button        *btn;

    if (!bar || !click )
        return ;
    if (button&SDL_BUTTON(1))
    {
        i = -1;
        while (++i < N_BUTTON)
            if ((btn = bar->btn[i]))
                if (click_surface(btn->s, (int *)click, &click[0], &click[1]))
                    break;
        if (i == N_BUTTON || !btn || btn->active == BUTTON_INACTIVE)
            return ;
        /*if (btn->state == 1)

        if (btn->state == 0)*/
        if (btn->ptrtype == 0 && btn->ft_ptr)
            btn->ft_ptr(btn->arg);
    }
}
