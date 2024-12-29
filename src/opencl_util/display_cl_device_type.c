#include "opencl_util.h"

void        display_cl_device_type(cl_device_type device_type)
{
    switch (device_type)
    {
        case CL_DEVICE_TYPE_DEFAULT:
            printf("CL_DEVICE_TYPE_DEFAULT\n");
            break;
        case CL_DEVICE_TYPE_CPU:
            printf("CL_DEVICE_TYPE_CPU\n");
            break;
        case CL_DEVICE_TYPE_GPU:
            printf("CL_DEVICE_TYPE_GPU\n");
            break;
        case CL_DEVICE_TYPE_ACCELERATOR:
            printf("CL_DEVICE_TYPE_ACCELERATOR\n");
            break;
        #ifdef CL_VERSION_1_2
        case CL_DEVICE_TYPE_CUSTOM:
            printf("CL_DEVICE_TYPE_CUSTOM\n");
            break;
        #endif
        case CL_DEVICE_TYPE_ALL:
            printf("CL_DEVICE_TYPE_ALL\n");
            break;
    }
}
