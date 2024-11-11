#include "user_interface.h"

static t_sceneNode      *scn_parse(t_mega *mega, char *objBuf, size_t bSz, int *errFlg)
{
    DEBUG ///
    return (NULL);
    /*
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
    */
}

/** put in datatypes **/
static int        scn_import(t_mega *mega)
{
    struct s_objMesh      oMesh;
    t_sceneNode      *root;
    int         fd;
    char        *fDat;
    size_t      fSz;

    if ((fd = fs_read("import.scn")) == -1)
        return (1);
    if (!(fDat = fd_readClose(fd, &fSz)))
        return (1);
    fd = -1;
    if (!(root = scn_parse(mega, fDat, fSz, &fd)))
    {
        printf("Error while parsing OBJ\n"); ///
        return (1);
    }
    mega->stcl->sig_refresh_model = 1;
    printf("%s : Successfully Imported\n", "import.scn");
    return (0);
}

int             ui_functionImportSCN(void *pMega, int flag)
{
    t_mega      *mega;

    if (!(mega = (t_mega *)pMega))
        return (1);
    scn_import(mega);
    return (0);
}
