#include "export.h"

static int           obj_new(char *filename)
{
    char            str[STRING_SIZE];
    int             fd;
    int             i;

    DEBUG ///
    if (!filename)
        return (-1);
    i = 0;
    /** Grab FileDescriptor **/
    while ((fd = open(filename, O_CREAT|O_WRONLY)) == -1 && ++i < 1000) //7-8-9
    {
        DEBUG ///
        str[0] = '\0';
        DEBUG ///
        if (!itoa(i, (char *)str, 10))
            break;
        DEBUG ///
        strcat(str, ".obj");
        DEBUG ///
        filename[11] = '\0';
        DEBUG ///
        strcat(filename, str);
        DEBUG ///
    }
    DEBUG ///
    if (fd == -1 || i >= 1000)
    {
        if (fd == -1)
            printf("Error: Can't create output\n(try with administrator privileges)\n");
        else
        {
            printf("Error: OBJ folder full, can't create output.\n(try cleaning the OBJ folder)\n");
            close(fd);
        }
        return (-1);
    }
    DEBUG ///
    return (fd);
}

static void        clamp_floatVal(char *val, uint n_precis)
{
    char        *ptr;
    uchar       dot;
    uint        digit;

    if (!(ptr = val))
        return ;
    dot = 0;
    digit = 0;
    while (*ptr)
    {
        if (dot == 1)
            digit++;
        if (*ptr == '.' && dot == 0)
            dot = 1;
        if (digit == n_precis)
        {
            *ptr = '\0';
            return ;
        }
        ptr++;
    }
}

static void        obj_writeHeader(int fd, const char *modelName)
{
    char        header[] = "# Wavefront OBJ file: ";
    char        header_[] = "\n# \no ";

    write(fd, header, sizeof(char) * strlen(header));
    write(fd, modelName, sizeof(char) * strlen(modelName));
    write(fd, (void *)header_, sizeof(char) * strlen(header_));
    write(fd, modelName, sizeof(char) * strlen(modelName));
    write(fd, &header_[0], sizeof(char));
}

static void        obj_writeGroup(int fd, const char *groupName)
{
    char        grp[] = "\ng Default\n";

    if (!groupName)
    {
        write(fd, &grp[1], sizeof(char) * strlen(&grp[1]));
        return ;
    }
    write(fd, &grp[1], sizeof(char) * 2);
    write(fd, groupName, sizeof(char) * strlen(groupName));
    write(1, &grp[0], sizeof(char));
}

static void        obj_writeVec(int fd, double *v, uint *compression)
{
    char        vecComp[STRING_SIZE];
    char        vrt[] = "v \n";
    uint        nDg;

    nDg = 8;
    if (compression && (nDg = 8 - *compression) > 8)
        nDg = 8;
    write(fd, vrt, sizeof(char) * 2);

    dtoa(vecComp, v[0]);
    clamp_floatVal(vecComp, nDg);
    write(fd, vecComp, strlen(vecComp));
    write(fd, &vrt[1], sizeof(char));

    dtoa(vecComp, v[1]);
    clamp_floatVal(vecComp, nDg);
    write(fd, vecComp, strlen(vecComp));
    write(fd, &vrt[1], sizeof(char));

    dtoa(vecComp, v[2]);
    clamp_floatVal(vecComp, nDg);
    write(fd, vecComp, strlen(vecComp));
    write(fd, &vrt[2], sizeof(char));
}

static void        obj_writeVertices(int fd, double *v, uint nv, const char *modelName)
{
    uint        i;
    uint        nPt;
    uint        vSz;

    if (!v || nv == 0)
        return ;
    obj_writeGroup(fd, NULL);
    nPt = (uint)*v + 1;
    vSz = (uint)*(v + 1);
    v += vSz;
    DEBUG ///
    printf("np :::: %u\n", nPt);
    i = 0;
    while (++i < nPt)
    {
        obj_writeVec(fd, v, NULL);
        v += vSz;
    }
    return ;
}

static void        obj_writeVertIndex(int fd, int f, int right_particle)
{
    char        faceBuf[STRING_SIZE];
    char        vrt[] = " //";

    itoa(f, faceBuf, 10);
    write(fd, faceBuf, strlen(faceBuf));
    write(fd, &vrt[1], sizeof(char) * 2);
    faceBuf[0] = '\0';
    itoa(right_particle, faceBuf, 10);
    write(fd, faceBuf, strlen(faceBuf));
    write(fd, &vrt[0], sizeof(char));
}

static void        obj_writeFaces(int fd, int *f, int nf, const char *modelName)
{
    char        sym[] = "\nf /";
    int        i;
    uint        j;

    if (!f || nf == 0)
        return ;
    obj_writeGroup(fd, NULL);
    i = 1;
    while (i <= nf)
    {
        /*i++;
        if (i >= nf)
            break;*/
        ///if (i % f[0] == 0)
        write(fd, sym, sizeof(char) * 3);
        j = 0;
        while (++j < f[0] + 1)
        {
            obj_writeVertIndex(fd, f[j], i);
        }
        i++;
        ///i += j - 1;
        f += j;
        if (*f == 0 /*|| i >= nf*/)
        ///if (*f != 4 /*|| i >= nf*/)
            return ;
    }
    return ;
}

void        export_obj(t_cam *c, uint modelHandle, const char *filename)
{
    char            strFile[STRING_SIZE];
    char            path[STRING_SIZE];
    int             fd;
    t_model         *mod;
    t_camdata       *dat;

    DEBUG ///
    if (!filename)
        return ;
    path[0] = '\0';
    strncat(path, OBJ_BASE_DIR, STRING_SIZE); /// Windows.
    strncat(path, filename, STRING_SIZE - (strlen(filename) + strlen(path))); /// Windows.
    if (getValidFileName(strFile, path, "obj")) /* Error */
        return ;
    dat = c->data;
    mod = &dat->model[modelHandle];
    if ((fd = obj_new(strFile)) == -1)
        return ;

    obj_writeHeader(fd, "scene");
    obj_writeVertices(fd, mod->v, mod->nv, "scene");
    obj_writeFaces(fd, mod->f, mod->nf, "scene");
    close(fd);
}

void        OLDexport_obj(t_cam *c) /// PICKED UP FROM EXPORT_DXF
{
    int         fd;
    char        filename[] = "DXF/output_0.obj";
    int         i;
    int         n;
    char        str[STRING_SIZE];
    char        *nstr;
    t_list      *listing;
    t_list      *listing_p;
    double      *data;
    double      vertice[4];

    //data += 4;
    /**
    nv = (int)data[0];
    //data = &data[3];
    data = &data[4];
    **/
    str[0] = '\0';
    listing = putlist(NULL, " 0\n");
    listing_p = putlist(listing, "SECTION\n");
    strcat((char *)str, " ");
    listing_p = putlist(listing_p, str);
    nstr = listing_p->str;
    listing_p = putlist(listing_p, "ENTITIES\n");
    listing_p = putlist(listing_p, " 0\n");

    ///printf("NV = [%d]\n", nv);///
    //memset((void *)str, STRING_SIZE, sizeof(char));
    i = -1;
    n = 1;
    /*
    while (++i < nv)
    {
        vertice[0] = data[i * 4];
        vertice[1] = data[(i * 4) + 1];
        vertice[2] = data[(i * 4) + 2];
        vertice[3] = data[(i * 4) + 3];
        if (vertice[3] > 0)
        {
            n++;
            listing_p = putlist(listing_p, "POINT\n");
            listing_p = putlist(listing_p, " 10\n");
            ///dtoa((char *)str, (double)(i % data->x)); // x
            dtoa((char *)str, vertice[0]); // x

            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Red X --> Y

            listing_p = putlist(listing_p, " 20\n");
            ///dtoa((char *)str, (double)(i / data->x)); // y
            dtoa((char *)str, vertice[1]); // y

            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Green Y --> X
            listing_p = putlist(listing_p, " 30\n");

            ///dtoa((char *)str, (double)*(data->ptr + i) * conf->f); // z
            dtoa((char *)str, vertice[2]); // z

            str[5] = '\0';
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z
            listing_p = putlist(listing_p, " 0\n"); // Zero
        }
    }*/
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
            printf("Error: Can't create output.obj\n(try with administrator privileges)\n");
        else
            printf("Error: OBJ folder full, can't create output.obj.\n(try cleaning the OBJ folder)\n");
        close(fd);
        free_list(listing);
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
