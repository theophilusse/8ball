#include "opencl_util.h"

/**
 ** release_opencl :
 ** Stop OpenCL at any time.
 **
**/
void release_opencl(struct s_opencl cl)
{
    /* Stop Execution */
    ///clFinish(cl.queue);
    clFlush(cl.queue);

    /* Deallocate kernels */
    if (cl.kernel)
        clReleaseKernel(cl.kernel);
    if (cl.kernel_cloud_fall)
        clReleaseKernel(cl.kernel_cloud_fall);

    /* Deallocate RAM buf */
    DEBUG /// Bug quelque part
    if (cl.picture_buf)
        FREE(cl.picture_buf);
    DEBUG
    if (cl.cloud_buf)
        FREE(cl.cloud_buf);
    DEBUG
    if (cl.triangle_buf)
        FREE(cl.triangle_buf);
    DEBUG
    if (cl.model_buf)
        FREE(cl.model_buf);

    /* Deallocate GPU Objects */
    DEBUG ///
    if (cl.input_triangle)
        clReleaseMemObject(cl.input_triangle); // X
    DEBUG ///
    if (cl.input_model)
        clReleaseMemObject(cl.input_model); // 1
    DEBUG ///
    if (cl.input_camera)
        clReleaseMemObject(cl.input_camera); // 2
    DEBUG ///
    if (cl.input_lights)
        clReleaseMemObject(cl.input_lights); // 3
    DEBUG ///
    if (cl.input_picture)
        clReleaseMemObject(cl.input_picture); // 4
    DEBUG ///
    if (cl.output_zbuffer)
        clReleaseMemObject(cl.output_zbuffer); // 5
    DEBUG ///
    if (cl.output_surface)
        clReleaseMemObject(cl.output_surface); // 6
    DEBUG ///
    if (cl.output_pixels)
        clReleaseMemObject(cl.output_pixels); // 7
    DEBUG ///
    /// SIGSEGFAULT
        if (cl.output_cloud)
            clReleaseMemObject(cl.output_cloud); // 8
    DEBUG ///
    /// SIGSEGFAULT
        if (cl.input_option)
            clReleaseMemObject(cl.input_option); // 9

    /* Deallocate Context */
    DEBUG ///
    /// SIGSEGFAULT
        if (cl.queue)
            clReleaseCommandQueue(cl.queue);
    if (cl.program)
        clReleaseProgram(cl.program);
    if (cl.context)
        clReleaseContext(cl.context);
}