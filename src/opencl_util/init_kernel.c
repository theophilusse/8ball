#include "opencl_util.h"

static int        set_kernel_args_cloud_fall(t_opencl *cl)
{
    cl_int            err;

    /* Create kernel arguments */
    err = clSetKernelArg(cl->kernel_cloud_fall, 0, sizeof(cl_mem), &cl->input_picture);
    if(err < 0) {
      printf("Couldn't create kernel cloud_fall 1st argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel_cloud_fall, 1, sizeof(cl_mem), &cl->input_triangle); /** Arg Models **/
    if(err < 0) {
      printf("Couldn't create kernel cloud_fall 2nd argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel_cloud_fall, 2, sizeof(cl_mem), &cl->input_cloud);
    if(err < 0) {
      printf("Couldn't create kernel cloud_fall 3rd argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel_cloud_fall, 3, sizeof(cl_mem), &cl->input_option);
    if(err < 0) {
      printf("Couldn't create kernel cloud_fall 4th argument : [%d]\n", err);
      return (1);
    }
    return (0);
}

int               init_kernel_cloud_fall(t_opencl *cl)
{
    int            err;

    /* Create a kernel */
    cl->kernel_cloud_fall = clCreateKernel(cl->program_cloud_fall, KERNEL_FUNC_CLOUD_FALL, &err);
    if(err < 0) {
      printf("Couldn't create kernel_cloud_fall [%d]\n", err);
      return (1);
    }
    return (set_kernel_args_cloud_fall(cl));
}

static int        set_kernel_args(t_opencl *cl)
{
    cl_int            err;

    /* Create kernel arguments */
    err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->input_camera);
    ///err = clSetKernelArg(cl->kernel, 0, sizeof(void *), &cl->input_camera);
    if(err < 0) {
      printf("Couldn't create kernel 1st argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->input_lights);
    if(err < 0) {
      printf("Couldn't create kernel 2nd argument : [%d]\n", err);
      return (1);
    }
    ///err |= clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->input_models);
    ///err |= clSetKernelArg(cl->kernel, 3, sizeof(cl_mem) /*cl->local_size * sizeof(float)*/, &cl->input_picture);
    err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->input_picture);
    if(err < 0) {
      printf("Couldn't create kernel 3rd argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->output_zbuffer);
    if(err < 0) {
      printf("Couldn't create kernel 4th argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->input_triangle); /** Arg Models **/
    if(err < 0) {
      printf("Couldn't create kernel 5th argument : [%d]\n", err);
      return (1);
    }
    /**
    err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->input_model); /// Arg Models
    if(err < 0) {
      printf("Couldn't create kernel 5th argument : [%d]\n", err);
      return (1);
    }
    **/
    err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), &cl->output_pixels);
    if(err < 0) {
      printf("Couldn't create kernel 6th argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->output_surface);
    if(err < 0) {
      printf("Couldn't create kernel 7th argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel, 7, sizeof(cl_mem), &cl->output_cloud);
    if(err < 0) {
      printf("Couldn't create kernel 7th argument : [%d]\n", err);
      return (1);
    }
    err = clSetKernelArg(cl->kernel, 8, sizeof(cl_mem), &cl->input_option);
    if(err < 0) {
      printf("Couldn't create kernel 8th argument : [%d]\n", err);
      return (1);
    }
    return (0);
}

int               init_kernel(t_opencl *cl)
{
    int            err;

    /* Create a kernel */
    cl->kernel = clCreateKernel(cl->program, KERNEL_FUNC, &err);
    if(err < 0) {
      printf("Couldn't create a kernel\n");
      return (1);
    }
    return (set_kernel_args(cl));
}
