#include "export.h"

/**
  * print_c.c : Export data as C code.
**/

static char         *_parser(char *format)
{
    return (NULL); /// Deadbeef.
}

static uint         _inc_nextVal(char *format)
{
    return (1); /// Deadbeef.
}

static int          _count_args(const char *format)
{
    return (0); /// Deadbeef.
}

void            print_c(int fd, const char *format, void *pointer, ...)
{
    va_list         ptr;
    char            *string;
    char            chunk[STRING_SIZE];

    string = (char *)format;
    chunk[0] = '\0';
    strcat(chunk, "/**\n  * Not implemented yet. (Todo.)\n**/\n");
    write(fd, (const void *)chunk, strlen(chunk));
    return ;
    /*if (_count_args(format) <= 0)
        return ;
    ///while ((string = _parser(string[_next_value(string)], )) != NULL)
    va_start(ptr, pointer);
    while ((string = _parser(string[_inc_nextVal(string)], )) != NULL)
    {
        ;
    }
    va_end(ptr);*/
}
