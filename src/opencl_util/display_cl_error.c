#include "opencl_util.h"

void display_cl_error(cl_int err)
{
    if (err != CL_SUCCESS) {
        // Handle the error based on the error code
        switch (err) {
                case CL_DEVICE_NOT_FOUND:
                    printf("Error: Device not found.\n");
                    break;
                case CL_DEVICE_NOT_AVAILABLE:
                    printf("Error: Device not available.\n");
                    break;
                case CL_COMPILER_NOT_AVAILABLE:
                    printf("Error: Compiler not available.\n");
                    break;
                case CL_MEM_OBJECT_ALLOCATION_FAILURE:
                    printf("Error: Memory object allocation failure.\n");
                    break;
                case CL_OUT_OF_RESOURCES:
                    printf("Error: Out of resources.\n");
                    break;
                case CL_OUT_OF_HOST_MEMORY:
                    printf("Error: Out of host memory.\n");
                    break;
                case CL_PROFILING_INFO_NOT_AVAILABLE:
                    printf("Error: Profiling information not available.\n");
                    break;
                case CL_MEM_COPY_OVERLAP:
                    printf("Error: Memory copy overlap.\n");
                    break;
                case CL_IMAGE_FORMAT_MISMATCH:
                    printf("Error: Image format mismatch.\n");
                    break;
                case CL_IMAGE_FORMAT_NOT_SUPPORTED:
                    printf("Error: Image format not supported.\n");
                    break;
                case CL_BUILD_PROGRAM_FAILURE:
                    printf("Error: Program build failure.\n");
                    break;
                case CL_MAP_FAILURE:
                    printf("Error: Map failure.\n");
                    break;
                case CL_MISALIGNED_SUB_BUFFER_OFFSET:
                    printf("Error: Misaligned sub buffer offset.\n");
                    break;
                case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
                    printf("Error: Execution status error for events in wait list.\n");
                    break;
                case CL_COMPILE_PROGRAM_FAILURE:
                    printf("Error: Compile program failure.\n");
                    break;
                case CL_LINKER_NOT_AVAILABLE:
                    printf("Error: Linker not available.\n");
                    break;
                case CL_LINK_PROGRAM_FAILURE:
                    printf("Error: Link program failure.\n");
                    break;
                case CL_DEVICE_PARTITION_FAILED:
                    printf("Error: Device partition failed.\n");
                    break;
                case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
                    printf("Error: Kernel argument information not available.\n");
                    break;
                case CL_INVALID_VALUE:
                    printf("Error: CL_INVALID_VALUE.\n");
                    break;
                case CL_INVALID_DEVICE_TYPE:
                    printf("Error: CL_INVALID_DEVICE_TYPE.\n");
                    break;
                case CL_INVALID_PLATFORM:
                    printf("Error: CL_INVALID_PLATFORM.\n");
                    break;
                case CL_INVALID_DEVICE:
                    printf("Error: CL_INVALID_DEVICE.\n");
                    break;
                case CL_INVALID_CONTEXT:
                    printf("Error: CL_INVALID_CONTEXT.\n");
                    break;
                case CL_INVALID_QUEUE_PROPERTIES:
                    printf("Error: CL_INVALID_QUEUE_PROPERTIES.\n");
                    break;
                case CL_INVALID_COMMAND_QUEUE:
                    printf("Error: CL_INVALID_COMMAND_QUEUE.\n");
                    break;
                case CL_INVALID_HOST_PTR:
                    printf("Error: CL_INVALID_HOST_PTR.\n");
                    break;
                case CL_INVALID_MEM_OBJECT:
                    printf("Error: CL_INVALID_MEM_OBJECT.\n");
                    break;
                case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
                    printf("Error: CL_INVALID_IMAGE_FORMAT_DESCRIPTOR.\n");
                    break;
                case CL_INVALID_IMAGE_SIZE:
                    printf("Error: CL_INVALID_IMAGE_SIZE.\n");
                    break;
                case CL_INVALID_SAMPLER:
                    printf("Error: CL_INVALID_SAMPLER.\n");
                    break;
                case CL_INVALID_BINARY:
                    printf("Error: CL_INVALID_BINARY.\n");
                    break;
                case CL_INVALID_BUILD_OPTIONS:
                    printf("Error: CL_INVALID_BUILD_OPTIONS.\n");
                    break;
                case CL_INVALID_PROGRAM:
                    printf("Error: CL_INVALID_PROGRAM.\n");
                    break;
                case CL_INVALID_PROGRAM_EXECUTABLE:
                    printf("Error: CL_INVALID_PROGRAM_EXECUTABLE.\n");
                    break;
                case CL_INVALID_KERNEL_NAME:
                    printf("Error: CL_INVALID_KERNEL_NAME.\n");
                    break;
                case CL_INVALID_KERNEL_DEFINITION:
                    printf("Error: CL_INVALID_KERNEL_DEFINITION.\n");
                    break;
                case CL_INVALID_KERNEL:
                    printf("Error: CL_INVALID_KERNEL.\n");
                    break;
                case CL_INVALID_ARG_INDEX:
                    printf("Error: CL_INVALID_ARG_INDEX.\n");
                    break;
                case CL_INVALID_ARG_VALUE:
                    printf("Error: CL_INVALID_ARG_VALUE.\n");
                    break;
                case CL_INVALID_ARG_SIZE:
                    printf("Error: CL_INVALID_ARG_SIZE.\n");
                    break;
                case CL_INVALID_KERNEL_ARGS:
                    printf("Error: CL_INVALID_KERNEL_ARGS.\n");
                    break;
                case CL_INVALID_WORK_DIMENSION:
                    printf("Error: CL_INVALID_WORK_DIMENSION.\n");
                    break;
                case CL_INVALID_WORK_GROUP_SIZE:
                    printf("Error: CL_INVALID_WORK_GROUP_SIZE.\n");
                    break;
                case CL_INVALID_WORK_ITEM_SIZE:
                    printf("Error: CL_INVALID_WORK_ITEM_SIZE.\n");
                    break;
                case CL_INVALID_GLOBAL_OFFSET:
                    printf("Error: CL_INVALID_GLOBAL_OFFSET.\n");
                    break;
                case CL_INVALID_EVENT_WAIT_LIST:
                    printf("Error: CL_INVALID_EVENT_WAIT_LIST.\n");
                    break;
                case CL_INVALID_EVENT:
                    printf("Error: CL_INVALID_EVENT.\n");
                    break;
                case CL_INVALID_OPERATION:
                    printf("Error: CL_INVALID_OPERATION.\n");
                    break;
                case CL_INVALID_GL_OBJECT:
                    printf("Error: CL_INVALID_GL_OBJECT.\n");
                    break;
                case CL_INVALID_BUFFER_SIZE:
                    printf("Error: CL_INVALID_BUFFER_SIZE.\n");
                    break;
                case CL_INVALID_MIP_LEVEL:
                    printf("Error: CL_INVALID_MIP_LEVEL.\n");
                    break;
                case CL_INVALID_GLOBAL_WORK_SIZE:
                    printf("Error: CL_INVALID_GLOBAL_WORK_SIZE.\n");
                    break;
                case CL_INVALID_PROPERTY:
                    printf("Error: CL_INVALID_PROPERTY.\n");
                    break;
                case CL_INVALID_IMAGE_DESCRIPTOR:
                    printf("Error: CL_INVALID_IMAGE_DESCRIPTOR.\n");
                    break;
                case CL_INVALID_COMPILER_OPTIONS:
                    printf("Error: CL_INVALID_COMPILER_OPTIONS.\n");
                    break;
                case CL_INVALID_LINKER_OPTIONS:
                    printf("Error: CL_INVALID_LINKER_OPTIONS.\n");
                    break;
                case CL_INVALID_DEVICE_PARTITION_COUNT:
                    printf("Error: CL_INVALID_DEVICE_PARTITION_COUNT.\n");
                    break;
                default:
                    printf("Error: Unknown error occurred. Error code: %d\n", err);
                    printf("Please check your OpenCL setup and ensure that all resources are available.\n");
                    printf("Consider checking the following:\n");
                    printf("1. Ensure that the OpenCL device is properly installed and configured.\n");
                    printf("2. Verify that there is enough memory available on the device.\n");
                    printf("3. Check for any previous errors in your OpenCL calls that may have led to this issue.\n");
                    printf("4. Consult the OpenCL documentation for more information on error codes.\n");
                    break;
        }
        return; // Handle the error appropriately
    }
}
