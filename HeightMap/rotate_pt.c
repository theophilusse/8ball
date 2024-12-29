#include "HeightMap.h"

void rotate_pt(double **M, double **O, double angle)
{
    double xM, yM, x, y;
    double       o[2];
    double       m[2];

    if (!M || !O)
        return ;
    angle *= PI / 180;
    o[0] = (*O)[0];
    o[1] = (*O)[1];
    m[0] = (*M)[0];
    m[1] = (*M)[1];
    xM = m[0] - o[0];
    yM = m[1] - o[1];
    x = xM * cos(angle) + yM * sin(angle) + o[0];
    y = - xM * sin(angle) + yM * cos(angle) + o[1];
    (*M)[0] = x;
    (*M)[1] = y;
    /* return ({x:Math.round (x), y:Math.round (y)}); */
}
