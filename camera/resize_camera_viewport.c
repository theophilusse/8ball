#include "camera.h"

/**
 ** resize_camera_viewport :
 ** Clean then rebuild both camera and OpenCL projection.
 ** Takes a camera and opencl pointer and the new uint X and Y resolution values.
 ** Return 1 if failed, 0 if success.
 **
**/
int             resize_camera_viewport(t_cam *c, t_opencl *cl, uint x, uint y)
{
    t_camdata       *d;
    uint            i;
    uint            j;
    cl_int          err;

    if (!c || !cl || x <= 0 || y <= 0)
        return (1);
    c->vw = x;
    c->vh = y;
    camera_aspect_ratio(c);
    if (!(d = c->data))
        return (1);
    if (cl->output_zbuffer)
        clReleaseMemObject(cl->output_zbuffer); // 5
    if (cl->output_pixels)
        clReleaseMemObject(cl->output_pixels); // 6
    if (d->backbuffer)
        SDL_FreeSurface(d->backbuffer);
    d->backbuffer = NULL;
    if (d->zbuffer)
        FREE(d->zbuffer);
    d->zbuffer = NULL;
    i = -1;
    j = (y * x) * 4;
    if (!(d->zbuffer = (double *)ALLOC(sizeof(double) * j)))
        return (1);
    i = -1;
    while (++i < j)
        d->zbuffer[i] = DBL_MAX;
    /** d->backbuffer = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, x, y, 32, rmask, gmask, bmask, amask); **/
    d->backbuffer = new_surface32(x, y);

    /** OpenCL Buffers **/
    cl->zbuffer_bufsz = (x * y) * (sizeof(double) * 4);
    cl->output_zbuffer = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
            CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR,
         cl->zbuffer_bufsz, c->data->zbuffer, &err);
    if (err < 0)
    {
        printf("Couldn't create zbuffer : [%s]\n", get_cl_error(err));
        /// TODO
        ///return (1);
    }

    cl->pixels_bufsz = c->data->backbuffer->w * c->data->backbuffer->h * (c->data->backbuffer->pitch / c->data->backbuffer->w);
    cl->output_pixels = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
            CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR,
         cl->pixels_bufsz, c->data->backbuffer->pixels, &err);
    if (err < 0)
    {
        printf("Couldn't create backbuffer : [%s]\n", get_cl_error(err));
        clReleaseMemObject(cl->output_zbuffer);
        /// TODO
        ///return (1);
    }
    err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), &cl->output_pixels);
    if(err < 0) {
      printf("Couldn't create kernel 6th argument : [%s]\n", get_cl_error(err));
      /// TODO
      ///return (1);
    }
    err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->output_zbuffer);
    if(err < 0) {
      printf("Couldn't create kernel 4th argument : [%s]\n", get_cl_error(err));
      /// TODO
      ///return (1);
    }
    return (0);
}
