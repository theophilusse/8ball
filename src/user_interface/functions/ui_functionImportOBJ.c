#include "user_interface.h"

int             ui_functionImportOBJ(void *pMega, int flag)
{
    t_mega      *mega;
    char        fName[STRING_SIZE];
    struct s_ftData_zone    zone;

    if (!pMega)
        return (1);
    mega = (t_mega *)pMega;

    zone = zone_upLeftCorner();
    fName[0] = '\0';
    ui_ask_form(zone, "Importer OBJ: %s", &fName[0]);
    if (obj_import(mega, fName))
        return (1);

    ///
    cl_int          err;
    t_opencl        *cl;
    t_camdata       *data;

    /*
        DEBUG ///
        printf("TODOOOOOOOOOOOOOOOOO !!! Trash.\n");
        DEBUG ///
    */
    cl = mega->stcl;
    data = mega->camera->data;
   /// Test Re-Alloc gpu model buffer

    if (cl->triangle_buf)
        FREE(cl->triangle_buf);
    if (push_triangle_opencl(cl, data))
        return (1);

    clReleaseMemObject(cl->input_triangle);
    cl->input_triangle = clCreateBuffer(cl->context, CL_MEM_READ_ONLY /*|
     CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR*/, cl->triangle_bufsz, NULL/*cl->triangle_buf*/, &err);
    if (err != CL_SUCCESS)
    {
        printf("Couldn't create model buffer\n");
        return (1);
    }
    /// Test.
    err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->input_triangle); /** Arg Models **/
    if(err < 0) {
      printf("Couldn't create kernel 5th argument : [%d]\n", err);
      return (1);
    }
    /// Test.
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_triangle,
            CL_TRUE, 0, cl->triangle_bufsz, cl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1 [er:%d]\n", err);
        return (1);
    }
    cl->sig_refresh_model = 0;
    return (0);
}
