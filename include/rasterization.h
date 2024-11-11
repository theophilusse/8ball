#ifndef RASTERIZATION_H
    #define RASTERIZATION_H

    #include "8ball.h"


    void        fillBottomFlatTriangle(SDL_Surface *s, uchar *rgb, int *v1, int *v2, int *v3);
    void        fillTopFlatTriangle(SDL_Surface *s, uchar *rgb, int *v1, int *v2, int *v3);
    void            draw_triangle(SDL_Surface *surface, uchar *rgb, int *v1, int *v2, int *v3);

    int        OLDvector_to_pixel(t_cam *c, double *input_vector, int w, int h, int *x, int *y, double *out3);
    int        vector_to_pixel(t_cam *c, double *input_vector, uint dimW, uint dimH, int *screen_pixel); /// GOOD

    int intersect3D_RayTriangle( struct s_ray R, struct s_triangle T, double* I , double *Dist ); /// CLOUD CPU
    ///int       rayTriangleIntersect(double *orig, double *dir, double *v0, double *v1, double *v2, double *t_);
    int rayTriangleIntersect(double *orig, double *dir, double *v0, double *v1, double *v2, double *t, double *u, double *v);
    int rayTriangleIntersect_commented(double *orig, double *dir, double *v0, double *v1, double *v2, double *t, double *u, double *v);

    void            get_v3(double *vertices, int i, double *out, double *pos, double *rotate, double *scale);
    void            reverse_vec(struct s_point in, t_point *out);
#endif // RASTERIZATION_H
