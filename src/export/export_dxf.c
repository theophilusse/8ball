#include "export.h"

static void            static_cut_exposant(char *str)
{
    if (!str)
        return ;
    while (*str)
        if (*(str++) == 'e')
        {
            *(str - 1) = '\0';
            return ;
        }
}

static int              dxf_write(int fd, t_list *begin)
{
    if (fd == -1)
        return (1);
    while (begin)
    {
        write(fd, begin->str, strlen(begin->str));
        begin = begin->next;
    }
    return (0);
}

static void              dxf_write_header_section(int fd, double *extmax)
{
    char            str[STRING_SIZE];
    t_list          *begin;
    t_list          *listing_p;

    str[0] = '\0';
    ///*listing = putlist(NULL, "0\n");
    begin = putlist(NULL, "0\n");
    listing_p = putlist(begin, "SECTION\n");
    listing_p = putlist(listing_p, "2\n");
    listing_p = putlist(listing_p, "HEADER\n");

    listing_p = putlist(listing_p, "9\n");
    listing_p = putlist(listing_p, "$EXTMIN\n");
    listing_p = putlist(listing_p, "10\n");
            dtoa((char *)str, extmax[0] * -1); // x
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z
    listing_p = putlist(listing_p, "20\n");
            dtoa((char *)str, extmax[1] * -1); // y
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z
    listing_p = putlist(listing_p, "30\n");
            dtoa((char *)str, extmax[2] * -1); // z
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z

    listing_p = putlist(listing_p, "0\n");
    listing_p = putlist(listing_p, "$EXTMAX\n");
    listing_p = putlist(listing_p, "10\n");
            dtoa((char *)str, extmax[0]); // z
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z
    listing_p = putlist(listing_p, "20\n");
            dtoa((char *)str, extmax[1]); // z
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z
    listing_p = putlist(listing_p, "30\n");
            dtoa((char *)str, extmax[2]); // z
            strcat((char *)str, "\n");
            listing_p = putlist(listing_p, str); // Blue Z
    listing_p = putlist(listing_p, "0\n");
    putlist(listing_p, "ENDSEC\n");
    //
    dxf_write(fd, begin);
    free_list(begin);
    //
}

static t_list           *dxf_put_point(t_list *listing_p, double *vertice, int verticeIndex)
{
    double      zindex;
    char        str[STRING_SIZE];
    t_list      *list;
    t_list      *begin;

    /**
        if (!listing_p)
        {
            begin = putlist(NULL, "0\n");
            listing_p = begin;
        }
        else
    **/
    begin = putlist(listing_p, "0\n"); /** TEST . **/

    list = putlist(begin, "POINT\n");
    list = putlist(list, "8\n");
    list = putlist(list, "VWX\n");

    list = putlist(list, "5\n");
    itoa(verticeIndex, (char *)str, 10); // Vertice Index
    ///static_cut_exposant((char *)str);
    strcat((char *)str, "\n");
    list = putlist(list, str); // Vertice Index

    list = putlist(list, "10\n");
    ///dtoa((char *)str, (vertice[0] - vHyp) + vSub[0] ); // x // U->
    dtoa((char *)str, vertice[0] ); // x
    strcat((char *)str, "\n");
    ///static_cut_exposant((char *)str);
    list = putlist(list, str); // Red X

    list = putlist(list, "20\n");
    ///dtoa((char *)str, (vertice[1] - vHyp) + vSub[1] ); // y // V->
    dtoa((char *)str, vertice[1]); // y
    strcat((char *)str, "\n");
    ///static_cut_exposant((char *)str);
    list = putlist(list, str); // Green Y

    list = putlist(list, "30\n");
    //zindex = vertice[3] / 50;
    ///zindex = vertice[3];
    ///dtoa((char *)str, vertice[2]); // z
    ///dtoa((char *)str, vertice[2] + sqrt(zindex)); // z
    ///dtoa((char *)str, vertice[2] + zindex); // z
    dtoa((char *)str, vertice[2]); // z
    ///str[5] = '\0';
    strcat((char *)str, "\n");
    ///static_cut_exposant((char *)str);
    list = putlist(list, str); // Blue Z
    return (begin);
}

static double           *static_getNextPixel(double *pFrom, int width, int height, uint x, uint y)
{
    uint            j;
    uint            adr;

    if (x + 1 >= width || y >= height || !pFrom)
        return (NULL);
    j = 1;
    while (j + x < width)
    {
        adr = j * 4;
        if (pFrom[adr + 3] != 0)
            break;
        j++;
    }
    if (j + x >= width)
        return (NULL);
    return (pFrom + adr);
}

static double           *static_getDownPixel(double *pFrom, int width, int height, uint x, uint y)
{
    uint            j;
    uint            adr;

    if (x >= width || y + 1 >= height || !pFrom)
        return (NULL);
    j = 1;
    while (j + y < height)
    {
        adr = (width * j) * 4;
        if (pFrom[adr + 3] != 0)
            break;
        j++;
    }
    if (j + y >= height)
        return (NULL);
    return (pFrom + adr);
}

static double           *static_getDownRightPixel(double *pFrom, int width, int height, uint x, uint y)
{
    uint            j;
    uint            adr;

    if (x + 1 >= width || y + 1 >= height || !pFrom)
        return (NULL);
    j = 1;
    while (j + y < height && j + x < width)
    {
        adr = ((width * j) + j) * 4;
        if (pFrom[adr + 3] != 0)
            break;
        j++;
    }
    if (j + x >= width || j + y >= height)
        return (NULL);
    return (pFrom + adr);
}

static int             static_getQuad(uchar index, double *a, double *b, double *c, double *d, double *midle_pt)
{
    double maximumCloudCompression = 0.01;
    double length;
    double  u[4];
    double  v[4];

    if (index >= 4 || !a || !b || !c || !c)
        return (1);
    /** Get UV coord **/

    sub_v3(b, a, u); /// A->B
    div_v3_by(u, 2, u);
    length = length3(u);
    if (length <= maximumCloudCompression) /** Plank **/
        return (1);

    sub_v3(c, a, v); /// A->C
    div_v3_by(v, 2, v);
    length = length3(v);
    if (length <= maximumCloudCompression) /** Plank **/
        return (1);
    if (index == 0)
    {
        /** Horizontal coord along A->B **/
        sub_v3(b, a, u);
        div_v3_by(u, 2, u);
        length = length3(u);
        if (length <= maximumCloudCompression) /** Plank **/
            return (1);
        /** Vertical coord along A->C **/
        sub_v3(c, a, v);
        div_v3_by(v, 2, v);
        length = length3(v);
        if (length <= maximumCloudCompression) /** Plank **/
            return (1);

        add_v3(a, u, b); /// B
        add_v3(a, v, c); /// C
        copy_v3(midle_pt, d); /// D
        return (0);
    }
    if (index == 1)
    {
        /** Horizontal coord along A->B **/
        sub_v3(b, a, u); /// A->B
        div_v3_by(u, 2, u);
        length = length3(u);
        if (length <= maximumCloudCompression) /** Plank **/
        return (1);
        add_v3(a, u, a); /// A

        /** Vertical coord along B->D **/
        sub_v3(d, b, v);
        div_v3_by(v, 2, v);
        length = length3(v);
        if (length <= maximumCloudCompression) /** Plank **/
            return (1);
        add_v3(b, v, d); /// D
        copy_v3(midle_pt, c); /// C
        return (0);
    }
    if (index == 2)
    {
        /** Vertical coord along A->C **/
        sub_v3(c, a, v);
        div_v3_by(v, 2, v);
        length = length3(v);
        if (length <= maximumCloudCompression) /** Plank **/
            return (1);
        add_v3(a, v, a); /// A
        copy_v3(midle_pt, b); /// B

        /** Horizontal coord along C->D **/
        sub_v3(d, c, u);
        div_v3_by(u, 2, u);
        length = length3(u);
        if (length <= maximumCloudCompression) /** Plank **/
            return (1);
        add_v3(c, u, d); /// D
        return (0);
    }
    if (index == 3)
    {
        copy_v3(midle_pt, a); /// A

        /** Vertical coord along D->B **/
        sub_v3(b, d, v);
        div_v3_by(v, 2, v);
        length = length3(v);
        if (length <= maximumCloudCompression) /** Plank **/
            return (1);
        add_v3(d, v, b); /// B

        /** Horizontal coord along D->C **/
        sub_v3(c, d, u);
        div_v3_by(u, 2, u);
        length = length3(u);
        if (length <= maximumCloudCompression) /** Plank **/
            return (1);
        add_v3(d, u, c); /// C
        return (0);
    }
    return (1);
}

static void             static_getDownRightSubparticle(double *a, double *d, double *sub)
{
    double      h[4];

    if (!a || !d || !sub)
        return ;
    h[3] = a[3];
    sub_v3(d, a, h);
    sub[0] = (h[0] / 2) + a[0];
    sub[1] = (h[1] / 2) + a[1];
    sub[2] = (h[2] / 2) + a[2];
    /*sub[3] = (h[3] / 2) + a[3];*/
}

static int static_recursiveQuadTree(int k, int kMax, double *a, double *b, double *c, double *d, int *verticeIndex, t_list **listing_p)
{
    t_list *swapList;
    uchar branchIndex;
    double mid_pt[4];
    double _a[4];
    double _b[4];
    double _c[4];
    double _d[4];
    double _n[4]; /// Normal

    if (!verticeIndex || !listing_p)
        return (1);
    ///if (k == 0)
    if (k == 0)
    {
        //DEBUG ///
        /** onFirstIteration: Put Reference Pixel particle **/
        ///*listing_p = dxf_put_point(*listing_p, a, *verticeIndex);
        /**swapList = dxf_put_point(*listing_p, a, *verticeIndex);**/
        swapList = dxf_put_point(*listing_p, a, *verticeIndex);
        if (!*listing_p)
            *listing_p = swapList;
        *verticeIndex = *verticeIndex + 1;
        ///return (1); /** DEBUG **/
    }
    if (kMax != -1 && k >= kMax)
        return (1);
    static_getDownRightSubparticle(a, d, mid_pt);

    copy_v3(a, _a);
    copy_v3(b, _b);
    copy_v3(c, _c);
    copy_v3(d, _d);
    if (static_getQuad(0, _a, _b, _c, _d, mid_pt))
        return (1);
    ///printf("k:[%d] VerticeIndex %d\n", k, *verticeIndex); /// Test. Debug.
    /** Draw Corner _| **/
    dxf_put_point(*listing_p, _b, *verticeIndex); /// A (Middle Up)
    *verticeIndex = *verticeIndex + 1;
    /// dxf_put_point(*listing_p, mid_pt, *verticeIndex); /// B (Middle)
    dxf_put_point(*listing_p, _d, *verticeIndex); /// B (Middle)
    *verticeIndex = *verticeIndex + 1;
    dxf_put_point(*listing_p, _c, *verticeIndex); /// C (Middle Left)
    *verticeIndex = *verticeIndex + 1;

    branchIndex = 0; /// Original KEEP
    ///branchIndex = 2;
    ///while (++branchIndex < 4) /// Original. KEEP
    while (branchIndex < 4) /// Debug.
    {
        ///DEBUG ///
        if (branchIndex != 0)
        {
            copy_v3(a, _a);
            copy_v3(b, _b);
            copy_v3(c, _c);
            copy_v3(d, _d);
            /** Get Next subQuad **/
            if (static_getQuad(branchIndex, _a, _b, _c, _d, mid_pt))
            {
                ///DEBUG ///
                return (1);
            }
        }

        /** Draw Next branch **/
        ///if (branchIndex != 2) /// Test Debug.
            static_recursiveQuadTree(k + 1, kMax, _a, _b, _c, _d, verticeIndex, listing_p);
        //}
        branchIndex++;
    }
    return (1); /** All branch written **/
}

static t_list           *dxf_set_point(t_list **p_begin_list, double *vertice, int width, int height, uint x, uint y, int *verticeIndex, uchar pixVal)
{
    double      subParticle[3];
    double      step;
    double      vHyp; /// Used in deadcode.

    if (!p_begin_list)
        return (NULL);
    ///*
        /**
        listing_p = dxf_put_point(listing_p, vertice, *verticeIndex);
        vertice[3] -= 1;
        *verticeIndex++;
        return (listing_p);
        **/
    ///*/

    double      A[4];
    double      B[4];
    double      C[4];
    double      D[4];
    double      *ptr;

    if (!vertice)
        return (*p_begin_list);
    A[0] = vertice[0];
    A[1] = vertice[1];
    A[2] = vertice[2];
    A[3] = vertice[3];
    if (!(ptr = static_getNextPixel(vertice, width, height, x, y)))
        return (*p_begin_list);
    B[0] = ptr[0];
    B[1] = ptr[1];
    B[2] = ptr[2];
    B[3] = ptr[3];
    if (!(ptr = static_getDownPixel(vertice, width, height, x, y)))
        return (*p_begin_list);
    C[0] = ptr[0];
    C[1] = ptr[1];
    C[2] = ptr[2];
    C[3] = ptr[3];
    if (!(ptr = static_getDownRightPixel(vertice, width, height, x, y)))
        return (*p_begin_list);
    D[0] = ptr[0];
    D[1] = ptr[1];
    D[2] = ptr[2];
    D[3] = ptr[3];
    ///printf("Draw Pixel[%u][%u] - verticeIndex[%d]\n", x, y, *verticeIndex);///
    ///int _macro_dxfMaxIter_ = 2;
    /*
    _n = ;
    _nBis = ;
    */

    //
    t_list      *swapList;
    A[3] = (A[3] + B[3] + C[3]) / 3;
    swapList = dxf_put_point(*p_begin_list, A, *verticeIndex);
    if (!*p_begin_list)
        *p_begin_list = swapList;
    *verticeIndex = *verticeIndex + 1;
    //

    ///pixelAvg = (uchar)(((float)(int)pix[0] + (int)pix[1] + (int)pix[2]) / 3);
    ///pixelValue = (int)(pixelAvg / (255 / _macro_dxfMaxIter_);
    ///pixelValue = (int)(pixelAvg / (255 / _macro_dxfMaxIter_));
    ///static_recursiveQuadTree(0, 2, A, B, C, D, verticeIndex, p_begin_list);
    /**
        static_recursiveQuadTree(0, (223 / 4) / pixVal, A, B, C, D, verticeIndex, p_begin_list);
    */
    return (*p_begin_list);
}

static int           dxf_open(char *filename)
{
    char            str[STRING_SIZE];
    int             fd;
    int             i;

    if (!filename)
        return (-1);
    i = 0;
    /** Grab FileDescriptor **/
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
        {
            printf("Error: DXF folder full, can't create output.dxf.\n(try cleaning the DXF folder)\n");
            close(fd);
        }
        return (-1);
    }
    return (fd);
}

static void              dxf_write_points_section(t_mega *mega, int fd, double *data, int nv, double scale)
{
    double      vertice[4];
    double      vSub[2];
    double      subPitch;
    int        i;
    int        dxfVerticeIndex; /// verticeIndex
    Uint8      *key;
    float       fUnit;
    float       fPercent[2];
    t_list      *listing_p;
    t_list      *begin;
    t_list      *nextNode;

    /*if (!listing_p)
        return (NULL);*/
    charset_print_noAlpha(mega->screen, mega->ui->font.charset, 0, mega->viewport->h - 26, "DXF: Exporting... [Press 's' to abort]");
    begin = putlist(NULL, "0\n");
    listing_p = putlist(begin, "SECTION\n");
    listing_p = putlist(listing_p, "2\n");
    listing_p = putlist(listing_p, "ENTITIES\n");
    //memset((void *)str, STRING_SIZE, sizeof(char));
    ///***/// /* Write Header */
        dxf_write(fd, begin);
        free_list(begin);
        listing_p = NULL;
        begin = NULL;
        nextNode = begin;
    ///***///

    ///***DEBUG***///
    /**
        double _va[4];
        double _vb[4];
        double _vc[4];
        double _vd[4];
        _va[0] = 0;
        _va[1] = 0;
        _va[2] = 0;
        _va[3] = 1;
        _vb[0] = 1;
        _vb[1] = 0;
        _vb[2] = 0;
        _vb[3] = 1;
        _vc[0] = 0;
        _vc[1] = 1;
        _vc[2] = 0;
        _vc[3] = 1;
        _vd[0] = 1;
        _vd[1] = 1;
        _vd[2] = 0;
        _vd[3] = 1;
        dxfVerticeIndex = 1;
        static_recursiveQuadTree(0, 0, _va, _vb, _vc, _vd, &dxfVerticeIndex, &begin, pixelValue);
        putlist(begin, "0\n");
        putlist(begin, "ENDSEC\n");
        dxf_write(fd, begin);
        free_list(begin);
        return ;*/
    ///***DEBUG***///

    i = -1;
    dxfVerticeIndex = 1;
    fUnit = 1.0 / nv;
    fPercent[1] = 0;
    ///scale = 1 * scale;

    uint     pictureWidth;
    uint     pictureHeight;
    uint     x;
    uint     y;
    x = 0;
    y = 0;
    SDL_Surface *img;
    img = mega->picture;
    pictureWidth = img->w;
    pictureHeight = img->h;

    uchar       *pix;
    uchar        pixVal;

    while (++i < nv)
    {
        if (x >= img->w)///
        {
            x = 0;
            y++;
        }
        if ((pix = (uchar *)getpixel_addr(img, x, y)))
        {
            pixVal = (uchar)(((float)pix[0] + (float)pix[1] + (float)pix[2]) / 3);
            /*
                vertice[0] = data[i * 4];
                vertice[1] = data[(i * 4) + 1];
                vertice[2] = data[(i * 4) + 2];
                vertice[3] = data[(i * 4) + 3];
            */
            ///vertice[3] = 1;
            ///if (conf->height <= (double)*(data->ptr + i) * conf->f)
            ///if (/*1 ||*/ vertice[3] != 0)
            ///if (/*1 ||*/ /**data[(i * 4) + 3] != 0 &&*/ pixVal >= 32) /** If Pixel isActive **/
            if (/*1 ||*/ data[(i * 4) + 3] != 0 && pixVal >= 32) /** If Pixel isActive **/
            {
                /**
                    if (!listing_p)
                    {
                        begin = putlist(NULL, "0\n");
                        listing_p = begin;
                    }
                    else
                        listing_p = putlist(listing_p, "0\n");
                **/
                ///if (!listing_p)
                dxf_set_point(&begin, &data[i * 4], pictureWidth, pictureHeight, x, y, &dxfVerticeIndex, pixVal);
                /*listing_p = dxf_set_point(&nextNode, &data[i * 4], pictureWidth, pictureHeight, mega->picture, x, y, &dxfVerticeIndex);
                if (listing_p)
                    nextNode = listing_p;*/

                /*else
                    listing_p = dxf_set_point(listing_p, &data[i * 4], pictureWidth, pictureHeight, x, y, &n);*/
                ///printf("Next LISTING POINTER %p\n", next_listing_p);
            }
        }
        ///if (i % 8 == 0 || i + 1 >= nv)
        if ((i != 0 && i % 8 == 0) || i + 1 >= nv)
        {
            fPercent[0] =(float)fPercent[1];
            fPercent[1] =(float)(i * fUnit);
            loading_bar(mega->screen, fPercent[0], fPercent[1]);
            SDL_Flip(mega->screen);
            ///
            dxf_write(fd, begin);
            free_list(begin);
            listing_p = NULL;
            begin = NULL;
            nextNode = begin;
            /*close(fd);
            if ((fd = dxf_open(filename, 1)) == -1)
                return ;*/
        }
        //
        SDL_PumpEvents();
        key = SDL_GetKeyState(NULL);
        if (key[SDLK_s])
        {
            BEEP_WARNING
            free_list(begin);
            return ;
        }
        //
        x++;
    }
    begin = putlist(NULL, "0\n");
    listing_p = putlist(begin, "ENDSEC\n");
    dxf_write(fd, begin);
    free_list(begin);
    /*close(fd);*/
    /**
        if (dxf_write(fd, listing_p))
            return (NULL);
        free_list(listing_p);
        listing_p = NULL;
    **/
}

void             dxf_write_eof(int fd)
{
    t_list      *listing_p;

    listing_p = putlist(NULL, "0\n");
    putlist(listing_p, "EOFF\n");
    dxf_write(fd, listing_p);
    free_list(listing_p);
}

static int           dxf_save_list(char *filename, t_list *begin)
{
    char            str[STRING_SIZE];
    t_list          *listing_p;
    int             fd;
    int             i;

    if (!filename || !begin)
        return (1);
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
        close(fd);
        free_list(begin);
        return (1);
    }
    listing_p = begin;
    while (begin)
    {
        //printf("%s", begin->str);
        write(fd, begin->str, strlen(begin->str));
        begin = begin->next;
    }
    free_list(listing_p);
    close(fd);
    return (0);
}

static double              pictureScale(t_option *opt)
{
    if (!opt)
        return (0);
    return (1 * opt->scale_factor);
}

void        export_cloud_to_dxf(t_mega *mega, int nv)
{
    char        filename[STRING_SIZE] = "DXF/output_0.dxf";
    int         fd;
    double      boundingBox[3];
    double      scale;
    double      *data;
    t_opencl    *cl;

    if (!mega || !(cl = mega->stcl) || !(data = (double *)cl->cloud_buf) || nv <= 0)
    {
        printf("Error: data missing.\n");
        return ;
    }
    boundingBox[0] = 35.9466;
    boundingBox[1] = 35.4125;
    boundingBox[2] = 24.997;
    if ((scale = pictureScale(&cl->option)) == 0)
    {
        printf("Error: picture scale missing\n");
        return ;
    }
    if ((fd = dxf_open(filename)) == -1)
        return ;
    dxf_write_header_section(fd, boundingBox);
    dxf_write_points_section(mega, fd, data, nv, scale);
    dxf_write_eof(fd);
    close(fd);
    /*
    else
    {
        if (dxf_save_list(filename, listing))
            printf("Error: can't save DXF file.\n");
    }
    */
    BEEP_WARNING
}

//void        export_dxf(t_grid *data, t_conf *conf)
void        OLD_export_cloud_to_dxf(t_opencl *cl, int nv)
{
    int         fd;
    char        filename[] = "DXF/output_0.dxf";
    int         i;
    int         n;
    char        str[STRING_SIZE];
    char        *nstr;
    t_list      *listing;
    t_list      *listing_p;
    double      *data;
    double      vertice[4];

    if (!cl || !(data = (double *)cl->cloud_buf) || nv <= 0)
    {
        printf("Error: data missing.\n");
        return ;
    }
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

    printf("NV = [%d]\n", nv);///
    //memset((void *)str, STRING_SIZE, sizeof(char));
    i = -1;
    n = 1;
    while (++i < nv)
    {
        vertice[0] = data[i * 4];
        vertice[1] = data[(i * 4) + 1];
        vertice[2] = data[(i * 4) + 2];
        vertice[3] = data[(i * 4) + 3];
        /*
        vertice[0] = data[i * 4];
        vertice[1] = data[i * 4];
        vertice[2] = data[i * 4];
        */
        /*
        vertice[0] = data[(i * 4) + 3];
        vertice[1] = data[(i * 4) + 3];
        vertice[2] = data[(i * 4) + 3];*/
        ///vertice[3] = 1;
        ///if (conf->height <= (double)*(data->ptr + i) * conf->f)
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
