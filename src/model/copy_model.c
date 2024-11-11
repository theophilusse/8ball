#include "model.h"

int                 copy_model(double *vrt, double *nv, int *fce, double *ovrt, double *onv, int *ofce)
{
    int         i;
    int         j;

    if (!vrt || !nv || !fce || !ovrt || !onv || !ofce)
        return (1);
    i = vrt[1] - 1;
    ovrt[0] = vrt[0];
    ovrt[1] = vrt[1];
    j = (int)(ovrt[0] * ovrt[1]) + vrt[1];
    while (++i < j) // Boucle des points
        ovrt[i] = vrt[i];
    ///n_face(int *fce)
    i = nv[1] - 1;
    onv[0] = nv[0];
    onv[1] = nv[1];
    j = (int)(onv[0] * onv[1]) + nv[1];
    while (++i < j) // Boucle des normales
        onv[i] = nv[i];

    i = -1;
    while (fce[++i] != 0) // Boucle des Faces
        ofce[i] = fce[i];
    return (0);
}