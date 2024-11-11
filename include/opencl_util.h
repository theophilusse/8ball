#ifndef OPENCL_UTIL_H
    #define OPENCL_UTIL_H

    #include "8ball.h"

    #define KERNEL_INCLUDE_DIRECTORY "-I clkernel" // Original
    //#define KERNEL_INCLUDE_DIRECTORY "-I E:/BOULOT/AMANDINE/8ball/clkernel"
    //#define PROGRAM_FILE "clkernel/add_numbers.cl"
    ///#define PROGRAM_FILE "clkernel/rasterize.cl" // Original
    //#define KERNEL_FUNC "add_numbers"

    #define PROGRAM_FILE "clkernel/kernel.cl" // TEST
    #define PROGRAM_FILE_CLOUD_FALL "clkernel/cloud_fall.cl" // TEST
    ///#define PROGRAM_FILE "clkernel/testkernel.cl" // TEST
    #define KERNEL_FUNC "rasterize"
    #define KERNEL_FUNC_CLOUD_FALL "cloud_fall"
    #define ARRAY_SIZE 64

    /**typedef struct s_DeviceDesc
    {
        cl_device_id    deviceId;
        cl_device_type  deviceType;
        char*           deviceTypeString;
        char*           deviceName;
    }              t_DeviceDesc;*/


    struct s_opencl OpenCL_stuff(int *error);

    cl_device_id        create_device(cl_int *error);
    cl_program          build_program(cl_context ctx, cl_device_id dev, const char* filename, cl_int *error);
    struct s_opencl     init_opencl(int *error);

    int                init_clmem(t_cam *cam, double *sun, SDL_Surface *picture, t_opencl *cl);
    int                init_clmem_cloud_fall(t_cam *cam, SDL_Surface *picture, t_opencl *cl);
    int                get_device_info(t_clinfo *cl, cl_device_id dev);

    int                init_kernel(t_opencl *cl);
    int                init_kernel_cloud_fall(t_opencl *cl);
    int                push_model_opencl(t_opencl *cl, t_camdata *d);
    size_t             f_buffer_size(int *f);
    int                push_triangle_opencl(t_opencl *cl, t_camdata *d);

    int        init_clmem_option(t_opencl *cl);
    int        init_clmem_picture(t_opencl *cl, SDL_Surface *picture);
    int        init_clmem_cloud_buffer(t_opencl *cl, SDL_Surface *picture, int flg);
    int        init_clmem_triangle(t_camdata *camdata, t_opencl *cl);

    /** Destructors **/
    void            release_opencl(struct s_opencl cl);


#endif // OPENCL_UTIL_H
