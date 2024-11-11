#include "HeightMap.h"

t_list          *putlist(t_list *l, const char *str)
{
    t_list      *p;

    if (!l)
    {
        if (!(p = (t_list *)malloc(sizeof(struct s_list))))
            return (NULL);
        l = p;
        l->next = NULL;
    }
    while (l->next)
        l = l->next;
    if (!(p = (t_list *)malloc(sizeof(struct s_list))))
        return (NULL);
    l->next = p;
    p->next = NULL;
    strcpy((char *)p->str, str);
    return (p);
}

void            free_list(t_list *l)
{
    t_list          *p;

    if (!(p = l))
        return ;
    while (p)
    {
        l = p;
        p = l->next;
        free(l);
    }
}
