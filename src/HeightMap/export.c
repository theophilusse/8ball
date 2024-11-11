#include "HeightMap.h"

void        export_dxf(t_grid *data, t_conf *conf)
{
    int         fd;
    char        filename[] = "DXF/output_0.dxf";
    int         i;
    int         n;
    char        str[STRING_SIZE];
    char        *nstr;
    t_list      *listing;
    t_list      *listing_p;

    str[0] = '\0';
    listing = putlist(NULL, " 0\n");
    listing_p = putlist(listing, "SECTION\n");
    strcat((char *)str, " ");
    listing_p = putlist(listing_p, str);
    nstr = listing_p->str;
    listing_p = putlist(listing_p, "ENTITIES\n");
    listing_p = putlist(listing_p, " 0\n");

    //memset((void *)str, STRING_SIZE, sizeof(char));
    i = -1;
    n = 1;
    while (++i < (int)data->sz)
        if (conf->height <= (double)*(data->ptr + i) * conf->f)
        {
            n++;
            listing_p = putlist(listing_p, "POINT\n");
            listing_p = putlist(listing_p, " 10\n");
            dtoa((char *)str, (double)(i % data->x)); // x
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Red X --> Y

            listing_p = putlist(listing_p, " 20\n");
            dtoa((char *)str, (double)(i / data->x)); // y
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Green Y --> X
            listing_p = putlist(listing_p, " 30\n");

            dtoa((char *)str, (double)*(data->ptr + i) * conf->f); // z
            str[5] = '\0';
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z
            listing_p = putlist(listing_p, " 0\n"); // Zero
        }
    listing_p = putlist(listing_p, "ENDSEC\n");
    listing_p = putlist(listing_p, "0\n");
    listing_p = putlist(listing_p, "EOF\n");

    itoa(n, nstr, 10);
    strcat((char *)nstr, "\n");
    // free loaded bitmap

    i = 0;
    while ((fd = open(filename, O_CREAT|O_WRONLY)) == -1 && ++i < 1000) //7-8-9
    {
        str[0] = '\0';
        if (!itoa(i, (char *)str, 10))
            break;
        strcat(str, ".dxf");
        filename[11] = '\0';
        strcat(filename, str);
    }
    if (fd == -1 || i >= 1000)
    {
        if (fd == -1)
            printf("Error: Can't create output.dxf\n(try with administrator privileges)\n");
        else
            printf("Error: DXF folder full, can't create output.dxf.\n(try cleaning the DXF folder)\n");
        return ;
    }
    listing_p = listing;
    while (listing)
    {
        //printf("%s", listing->str);
        write(fd, listing->str, strlen(listing->str));
        listing = listing->next;
    }
    free_list(listing_p);
    close(fd);
}
