#include "opencl_util.h"

int         get_device_info(t_clinfo *cl, cl_device_id dev)
{
    int                i;
    cl_device_info     qwery;
    size_t             retSize;
    char               devname[64];
    cl_int             err;

    if (!cl)
        return (1);
    qwery = CL_DEVICE_NAME;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(char) * 64, devname, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    printf("---- %s ----\n", devname);

    qwery = CL_DEVICE_TYPE;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(cl_device_type), &cl->device_type, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    printf("Device Type : [");
    if (cl->device_type == CL_DEVICE_TYPE_CPU)
        printf("CPU]\n");
    if (cl->device_type == CL_DEVICE_TYPE_GPU)
        printf("GPU]\n");
    if (cl->device_type == CL_DEVICE_TYPE_ACCELERATOR)
        printf("Accelerator] !\n");
    if (cl->device_type == CL_DEVICE_TYPE_DEFAULT)
        printf("Default] !\n");
    if (cl->device_type == CL_DEVICE_TYPE_CUSTOM)
        printf("Custom] !\n");

    qwery = CL_DEVICE_MAX_COMPUTE_UNITS;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(cl_uint), &cl->max_compute_units, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    printf("Max compute units : [%u]\n", cl->max_compute_units);

    qwery = CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(cl_uint), &cl->dimensions, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    printf("Max work item dimension : [%u]\n", cl->dimensions);
    if (cl->dimensions > 8)
    {
        /*printf("Too Much dimensions !\n");
        return (1);*/
        cl->dimensions = 8;
    }

    qwery = CL_DEVICE_MAX_WORK_ITEM_SIZES;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(size_t) * cl->dimensions, cl->dimension_size, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    i = -1;

    /**while (++i < cl->dimensions)
        printf("\t[%u] Max work item size : [%u]\n", i, cl->dimension_size[i]);**/
    cl->max_work_group_size = (size_t)1024;
    return (0); /// DEBUG
    /*** Original
    qwery = CL_DEVICE_MAX_WORK_GROUP_SIZE;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(size_t), &cl->max_work_group_size, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    ***/
    printf("Max work group size : [%zu]\n", cl->max_work_group_size);
    return (0); /// DEBUG
    qwery = CL_DEVICE_GLOBAL_MEM_SIZE;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(cl_ulong), &cl->global_mem_size, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    printf("Global Memory Size : [%lu] bytes\n", (unsigned long)cl->global_mem_size);
    return (0); /// DEBUG
    qwery = CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(cl_ulong), &cl->constant_buffer_size, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    printf("Constant Buffer Size : [%lu] bytes\n", (unsigned long)cl->constant_buffer_size);

    qwery = CL_DEVICE_LOCAL_MEM_SIZE;
    if ((err = clGetDeviceInfo(dev, qwery, sizeof(cl_ulong), &cl->local_mem_size, &retSize)) != CL_SUCCESS)
    {
        printf("clGetDeviceInfo ERROR : [%d]\n", err);
        return (1);
    }
    printf("Local Buffer Size : [%lu] bytes\n", (unsigned long)cl->local_mem_size);

    printf("----------");
    i = (int)strlen(devname);
    while (i--)
        printf("-");
    printf("\n");
    return (0);
}
