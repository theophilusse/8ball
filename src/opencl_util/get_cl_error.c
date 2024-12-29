#include "opencl_util.h"

const char *get_cl_error(cl_int err)
{
    if (err != CL_SUCCESS) {
        // Handle the error based on the error code
        switch (err) {
                case CL_DEVICE_NOT_FOUND:
                    return("Error: Device not found.\n");
                case CL_DEVICE_NOT_AVAILABLE:
                    return("Error: Device not available.\n");
                case CL_COMPILER_NOT_AVAILABLE:
                    return("Error: Compiler not available.\n");
                case CL_MEM_OBJECT_ALLOCATION_FAILURE:
                    return("Error: Memory object allocation failure.\n");
                case CL_OUT_OF_RESOURCES:
                    return("Error: Out of resources.\n");
                case CL_OUT_OF_HOST_MEMORY:
                    return("Error: Out of host memory.\n");
                case CL_PROFILING_INFO_NOT_AVAILABLE:
                    return("Error: Profiling information not available.\n");
                case CL_MEM_COPY_OVERLAP:
                    return("Error: Memory copy overlap.\n");
                case CL_IMAGE_FORMAT_MISMATCH:
                    return("Error: Image format mismatch.\n");
                case CL_IMAGE_FORMAT_NOT_SUPPORTED:
                    return("Error: Image format not supported.\n");
                case CL_BUILD_PROGRAM_FAILURE:
                    return("Error: Program build failure.\n");
                case CL_MAP_FAILURE:
                    return("Error: Map failure.\n");
                case CL_MISALIGNED_SUB_BUFFER_OFFSET:
                    return("Error: Misaligned sub buffer offset.\n");
                case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
                    return("Error: Execution status error for events in wait list.\n");
                case CL_COMPILE_PROGRAM_FAILURE:
                    return("Error: Compile program failure.\n");
                case CL_LINKER_NOT_AVAILABLE:
                    return("Error: Linker not available.\n");
                case CL_LINK_PROGRAM_FAILURE:
                    return("Error: Link program failure.\n");
                case CL_DEVICE_PARTITION_FAILED:
                    return("Error: Device partition failed.\n");
                case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
                    return("Error: Kernel argument information not available.\n");
                case CL_INVALID_VALUE:
                    return("Error: CL_INVALID_VALUE.\n");
                case CL_INVALID_DEVICE_TYPE:
                    return("Error: CL_INVALID_DEVICE_TYPE.\n");
                case CL_INVALID_PLATFORM:
                    return("Error: CL_INVALID_PLATFORM.\n");
                case CL_INVALID_DEVICE:
                    return("Error: CL_INVALID_DEVICE.\n");
                case CL_INVALID_CONTEXT:
                    return("Error: CL_INVALID_CONTEXT.\n");
                case CL_INVALID_QUEUE_PROPERTIES:
                    return("Error: CL_INVALID_QUEUE_PROPERTIES.\n");
                case CL_INVALID_COMMAND_QUEUE:
                    return("Error: CL_INVALID_COMMAND_QUEUE.\n");
                case CL_INVALID_HOST_PTR:
                    return("Error: CL_INVALID_HOST_PTR.\n");
                case CL_INVALID_MEM_OBJECT:
                    return("Error: CL_INVALID_MEM_OBJECT.\n");
                case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
                    return("Error: CL_INVALID_IMAGE_FORMAT_DESCRIPTOR.\n");
                case CL_INVALID_IMAGE_SIZE:
                    return("Error: CL_INVALID_IMAGE_SIZE.\n");
                case CL_INVALID_SAMPLER:
                    return("Error: CL_INVALID_SAMPLER.\n");
                case CL_INVALID_BINARY:
                    return("Error: CL_INVALID_BINARY.\n");
                case CL_INVALID_BUILD_OPTIONS:
                    return("Error: CL_INVALID_BUILD_OPTIONS.\n");
                case CL_INVALID_PROGRAM:
                    return("Error: CL_INVALID_PROGRAM.\n");
                case CL_INVALID_PROGRAM_EXECUTABLE:
                    return("Error: CL_INVALID_PROGRAM_EXECUTABLE.\n");
                case CL_INVALID_KERNEL_NAME:
                    return("Error: CL_INVALID_KERNEL_NAME.\n");
                case CL_INVALID_KERNEL_DEFINITION:
                    return("Error: CL_INVALID_KERNEL_DEFINITION.\n");
                case CL_INVALID_KERNEL:
                    return("Error: CL_INVALID_KERNEL.\n");
                case CL_INVALID_ARG_INDEX:
                    return("Error: CL_INVALID_ARG_INDEX.\n");
                case CL_INVALID_ARG_VALUE:
                    return("Error: CL_INVALID_ARG_VALUE.\n");
                case CL_INVALID_ARG_SIZE:
                    return("Error: CL_INVALID_ARG_SIZE.\n");
                case CL_INVALID_KERNEL_ARGS:
                    return("Error: CL_INVALID_KERNEL_ARGS.\n");
                case CL_INVALID_WORK_DIMENSION:
                    return("Error: CL_INVALID_WORK_DIMENSION.\n");
                case CL_INVALID_WORK_GROUP_SIZE:
                    return("Error: CL_INVALID_WORK_GROUP_SIZE.\n");
                case CL_INVALID_WORK_ITEM_SIZE:
                    return("Error: CL_INVALID_WORK_ITEM_SIZE.\n");
                case CL_INVALID_GLOBAL_OFFSET:
                    return("Error: CL_INVALID_GLOBAL_OFFSET.\n");
                case CL_INVALID_EVENT_WAIT_LIST:
                    return("Error: CL_INVALID_EVENT_WAIT_LIST.\n");
                case CL_INVALID_EVENT:
                    return("Error: CL_INVALID_EVENT.\n");
                case CL_INVALID_OPERATION:
                    return("Error: CL_INVALID_OPERATION.\n");
                case CL_INVALID_GL_OBJECT:
                    return("Error: CL_INVALID_GL_OBJECT.\n");
                case CL_INVALID_BUFFER_SIZE:
                    return("Error: CL_INVALID_BUFFER_SIZE.\n");
                case CL_INVALID_MIP_LEVEL:
                    return("Error: CL_INVALID_MIP_LEVEL.\n");
                case CL_INVALID_GLOBAL_WORK_SIZE:
                    return("Error: CL_INVALID_GLOBAL_WORK_SIZE.\n");
                case CL_INVALID_PROPERTY:
                    return("Error: CL_INVALID_PROPERTY.\n");
                case CL_INVALID_IMAGE_DESCRIPTOR:
                    return("Error: CL_INVALID_IMAGE_DESCRIPTOR.\n");
                case CL_INVALID_COMPILER_OPTIONS:
                    return("Error: CL_INVALID_COMPILER_OPTIONS.\n");
                case CL_INVALID_LINKER_OPTIONS:
                    return("Error: CL_INVALID_LINKER_OPTIONS.\n");
                case CL_INVALID_DEVICE_PARTITION_COUNT:
                    return("Error: CL_INVALID_DEVICE_PARTITION_COUNT.\n");
                default:
                    return("Error: Unknown error occurred.");
        }
        return ("CL_SUCCESS"); // Handle the error appropriately
    }
}
