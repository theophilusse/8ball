#include "import.h"

/**
typedef struct s_wobj
{


    double      *vrt;
    double      *nrm;
    double      *fce;
}

struct s_wobj            import_obj()
{


}**/

static int          isFloat(char c)
{
    if ((c >= '0' && c <= '9') || c == '-')
        return (1);
    return (0);
}

static int          isInt(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static char                 *obj_parser_triggerChar(char *ptr, const char *trigger)
{
    uint        idx;

    if (!ptr || !trigger)
        return (NULL);
    if (*ptr == '\n' || /// Unix
        (*ptr == '\r' && *(ptr + 1) != '\n' && *(ptr + 1) != '\r') || /// MacOS
        (*ptr == '\r' && *(ptr + 1) == '\n') ) /// Windows
    {
        idx = 1;
        if (*ptr != '\n')
        {
            if (*ptr == '\r' && *(ptr + 1) != '\n' && *(ptr + 1) != '\r') /// MacOS
                idx = 1;
            if (*ptr == '\r' && *(ptr + 1) == '\n' && *(ptr + 2) != '\r') /// Windows
                idx = 2;
        }
        if (*(ptr + idx) == trigger[0] && *(ptr + idx + 1) == trigger[1] )/*&&
            (trigger[2] == '\0' || (trigger[2] == *(ptr + idx + 2))))*/
            return ((char *)(ptr + idx + strlen(trigger)));
    }
    return (NULL);
}

static uint                 obj_parseCount(char *buf, size_t bSz, const char *type)
{
    uint            count;
    uint            i;

    count = 0;
    if (!buf || bSz == 0)
        return (0);
    i = -1;
    while (++i < bSz)
    {
        if (obj_parser_triggerChar(buf, type))
            count++;
        buf++;
    }
    return (count);
}

static char        *obj_nextValue(char *ptr)
{
    if (!ptr)
        return (NULL);
    while (*ptr && *ptr != ' ' && *ptr != '\n' && *ptr != '\r')
        ptr++;
    if (*ptr != ' ')
        return (NULL);
    if (*ptr == ' ' && isFloat(*(ptr + 1)))
        return (ptr + 1);
    return (NULL);
}

static char        *obj_nextFaceComponent(char *ptr)
{
    if (!ptr)
        return (NULL);
    while (*ptr && *ptr != ' ' && *ptr != '\n' && *ptr != '\r')
        ptr++;
    if (*ptr != ' ')
        return (NULL);
    if (*ptr == ' ' && isInt(*(ptr + 1)))
        return (ptr + 1);
    return (NULL);
}

static uint                 obj_parseCells(char *buf, size_t bSz, const char *type)
{
    char            *ptr;
    uint            count;
    uint            i;

    if (!buf || bSz == 0)
        return (0);
    count = 1;
    i = -1;
    while (++i < bSz)
    {
        if ((ptr = obj_parser_triggerChar(buf, type)) &&
            (count++) > 0)
            while (ptr)
            {
                ptr = obj_nextFaceComponent(ptr);
                count++;
            }
        buf++;
    }
    return (count);
}

static double               *obj_getVertices(char *buf, size_t bSz)
{
    double          *vRet;
    double          *vPtr;
    char            *ptr;
    uint            i;
    uint            j;

    if (!buf ||
        !(vRet = (double *)ALLOC(sizeof(double) * \
        ((obj_parseCount(buf, bSz, "v ") + 1) * 3))))
        return (NULL);

    vRet[1] = 3;
    vRet[2] = 0;
    i = -1;
    j = (uint)vRet[1];
    vPtr = &vRet[(uint)vRet[1]];
    while (++i < bSz && *buf)
    {
        if ((ptr = obj_parser_triggerChar(buf, "v ")))
            while (ptr)
            {
                *vPtr = atof((const char *)ptr);
                ptr = obj_nextValue(ptr);
                vPtr++;
                j++;
            }
        buf++;
    }
    vRet[0] = (double)(j - (uint)vRet[1]) / vRet[1];
    printf("Loaded [%u vertices]\n", (uint)vRet[0]);
    return (vRet);
}

static int                  *obj_getFaces(char *buf, size_t bSz)
{
    int             *pf;
    int             *fRet;
    char            *ptr;
    uint            iter;
    uint            i;
    uint            j;

    if (!buf)
        return (NULL);
    uint fbSz = obj_parseCells(buf, bSz, "f ") + 1;
    if (!(fRet = (int *)ALLOC(sizeof(int) * fbSz))) /** STATIC QUADS **/
        return (NULL);
    i = -1;
    j = 0;
    while (++i < bSz)
    {
        if ((ptr = obj_parser_triggerChar(buf, "f ")))
        {
            iter = 0;
            pf = &fRet[j];
            j++;
            while (ptr)
            {
                fRet[j] = atoi((const char *)ptr);
                ptr = obj_nextFaceComponent(ptr);
                j++;
                iter++;
            }
            *pf = iter;
        }
        buf++;
    }
    fRet[j] = 0;
    return (fRet);
}

static double               *obj_getNormals(char *buf, size_t bSz)
{
    double          *vRet;
    double          *vPtr;
    char            *ptr;
    uint            i;
    uint            j;

    if (!(vRet = (double *)ALLOC(sizeof(double) * 3)))
        return (NULL);
    vRet[0] = 0;
    vRet[1] = 3;
    vRet[2] = 0;
    return (vRet); /// Tmp No Normals.

    if (!buf ||
        !(vRet = (double *)ALLOC(sizeof(double) * \
        ((obj_parseCount(buf, bSz, "vn ") + 1) * 3))))
        return (NULL);

    vRet[1] = 3;
    vRet[2] = 0;
    i = -1;
    j = (uint)vRet[1];
    vPtr = &vRet[(uint)vRet[1]];
    while (++i < bSz && *buf)
    {
        if ((ptr = obj_parser_triggerChar(buf, "vn ")))
            while (ptr)
            {
                *vPtr = atof((const char *)ptr);
                ptr = obj_nextValue(ptr);
                vPtr++;
                j++;
            }
        buf++;
    }
    vRet[0] = (double)(j - (uint)vRet[1]) / vRet[1];
    printf("Loaded [%u normals]\n", (uint)vRet[0]);
    return (vRet);
}

static struct s_objMesh      obj_parse(t_mega *mega, char *objBuf, size_t bSz, int *errFlg)
{
    struct s_objMesh           obj;

    obj.f = NULL;
    obj.n = NULL;
    obj.v = NULL;
    if (!errFlg)
        return (obj);
    *errFlg = 1;
    if (!mega || !objBuf || bSz == 0)
        return (obj);
    if (!(obj.v = obj_getVertices(objBuf, bSz))) /// BUG LA DEDANS ... Toujours (pas teste)??
        return (obj);
    if (!(obj.f = obj_getFaces(objBuf, bSz))) /// BUG?
    {
        FREE(obj.v);
        obj.v = NULL;
        return (obj);
    }
    if (!(obj.n = obj_getNormals(objBuf, bSz)))
    {
        FREE(obj.v);
        FREE(obj.f);
        obj.v = NULL;
        obj.f = NULL;
        return (obj);
    }
    *errFlg = 0;
    return (obj);
}

/** put in datatypes **/
int        obj_import(t_mega *mega, const char *fileName)
{
    struct s_objMesh      oMesh;
    char                fname[STRING_SIZE];
    int         fd;
    char        *fDat;
    uint        fSz;

    fname[0] = '\0';
    strcat(fname, fileName);
    strcat(fname, ".obj");
    if ((fd = fs_read(fname)) == -1)
        return (1);
    if (!(fDat = fd_readClose(fd, &fSz)))
        return (1);
    fd = -1;
    oMesh = obj_parse(mega, fDat, fSz, &fd);
    if (fd)
    {
        printf("Error while parsing OBJ\n"); ///
        return (1);
    }
    push_model(mega->camera->data, (uchar *)_blue_crystal, oMesh.v, oMesh.n, oMesh.f, NULL, NULL, NULL); /// Bust
    mega->stcl->sig_refresh_model = 1;
    printf("%s : Successfully Imported\n", fname);
    return (0);
}
