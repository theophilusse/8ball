#include  "ft_gpu.h"

int                gpu_modelRefresh(t_opencl *cl, t_camdata *data)
{
    cl_int      err;

    if (cl->triangle_buf)
        FREE(cl->triangle_buf);
    if (push_triangle_opencl(cl, data))
        return (1);
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_triangle,
            CL_TRUE, 0, cl->triangle_bufsz, cl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1 [er:%d]\n", err);
        return (1);
    }
    return (0);
    if (cl->sig_refresh_model)
    {
        /// Test Re-Alloc gpu model buffer
        if (cl->triangle_buf)
            FREE(cl->triangle_buf);
        if (push_triangle_opencl(cl, data))
            return (1);

        clReleaseMemObject(cl->input_triangle);
        cl->input_triangle = clCreateBuffer(cl->context, CL_MEM_READ_ONLY /*|
         CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR*/, cl->triangle_bufsz, cl->triangle_buf, &err);
        if (err != CL_SUCCESS)
        {
            printf("Couldn't create model buffer\n");
            return (1);
        }
        if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_triangle,
                CL_TRUE, 0, cl->triangle_bufsz, cl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
        {
            printf("Couldn't write buffer 1 [er:%d]\n", err);
            return (1);
        }
        cl->sig_refresh_model = 0;
    }
    else
    {
        if (cl->triangle_buf)
            FREE(cl->triangle_buf);
        if (push_triangle_opencl(cl, data))
            return (1);
        if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_triangle,
                CL_TRUE, 0, cl->triangle_bufsz, cl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
        {
            printf("Couldn't write buffer 1 [er:%d]\n", err);
            return (1);
        }
    }
    return (0);
}
