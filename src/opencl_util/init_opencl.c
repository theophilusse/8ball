#include "opencl_util.h"

/**
 ** Author : ttrossea
 ** init_opencl.c :
 ** Contain init_opencl and several OpenCL core functions.
 **
 ** Use init_opencl to load up OpenCL.
 **
 ** - create_device
 ** - build_program
 ** - init_option (static)
 ** - init_opencl
 **
**/

/**
 ** create_device :
 ** Find a GPU or CPU associated with the first available platform.
 **
**/
cl_device_id create_device(cl_int *error)
{
   cl_uint numplatform;
   cl_platform_id platform_list[5];
   cl_platform_id platform;
   cl_device_id dev;
   int      i;
   int      j;
   cl_device_id devices[512];
   cl_int   ciErrNum;
   cl_device_info qwery;
   cl_device_type devtype;
   cl_uint ciDeviceCount;
   int err;
   //cl_platform_id clSelectedPlatformID = NULL;
   //err = oclGetPlatformID(&clSelectedPlatformID);

   cl_uint num_of_platforms;
    if (clGetPlatformIDs(0, NULL, &num_of_platforms) != CL_SUCCESS)
    {
        printf("Unable to get platform_id\n");
        //return 1;
    }
    cl_platform_id platform_ids[5];
    if (clGetPlatformIDs(num_of_platforms, platform_ids, NULL) != CL_SUCCESS)
    {
        printf("Unable to get platform_id\n");
        //return (1);
    }
    char found = 0;
    cl_uint num_of_devices;
    cl_device_id device_id;
    for(int i=0; i<num_of_platforms; i++)
    {
        if((ciErrNum = clGetDeviceIDs(platform_ids[i], CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_CPU, 1, &device_id, &num_of_devices)) == CL_SUCCESS){
            found = 1;
            //break;
        }
        else
            printf("clGetDeviceIDs: [%s]\n", get_cl_error(ciErrNum));
    }
    if(!found){
        printf("Unable to get device_id\n");
        //return 1;
    }

   //numplatform = 1; //
   //platform_list[0] = clSelectedPlatformID; //

   *error = 1;
   /* Identify a platform */
   ///err = clGetPlatformIDs(1, &platform, &numplatform); /// Original
   err = clGetPlatformIDs(5, platform_list, &numplatform); /// TEST

   for (cl_uint p = 0; p < numplatform; p++) {
    char platform_name[128];
    clGetPlatformInfo(platform_list[p], CL_PLATFORM_NAME, sizeof(platform_name), platform_name, NULL);
    printf("Platform %d: %s\n", p, platform_name);
    }

   //err = clGetPlatformIDs(5, platform_list, NULL); /// TEST
   if(err < 0) {
      perror("Couldn't identify a platform");
      return (0);
   }
   printf("plateform[%u]\n", numplatform); ///
   qwery = CL_DEVICE_TYPE;
   i = -1;
   while (++i < numplatform)
   {
       ciErrNum = clGetDeviceIDs(platform_list[i], CL_DEVICE_TYPE_ALL, 0, NULL, &ciDeviceCount);
       if (ciErrNum != CL_SUCCESS)
       {
           printf("clGetDeviceIDs ERROR : [%d]\n", err);
           display_cl_error(ciErrNum);
           return (0);
       }
       printf("Device count: %d\n", ciDeviceCount);
       /*if ((devices = (cl_device_id*)ALLOC(sizeof(cl_device_id) * ciDeviceCount)) == NULL)
       {
            printf(" Failed to allocate memory for devices !!!\n\n");
            return (0);
       }*/
       ciErrNum = clGetDeviceIDs(platform_list[i], CL_DEVICE_TYPE_ALL, ciDeviceCount, devices, &ciDeviceCount);
       //
       //err = clGetDeviceIDs(platform_list[i], CL_DEVICE_TYPE_ALL, 1, &dev, NULL);
       //if ((err = clGetDeviceInfo(dev, qwery, sizeof(cl_device_type), &devtype, NULL)) != CL_SUCCESS)
       j = -1;
       while (++j < ciDeviceCount)
       {
            if ((err = clGetDeviceInfo(devices[j], qwery, sizeof(cl_device_type), &devtype, NULL)) != CL_SUCCESS)
            {
                printf("clGetDeviceInfo ERROR : [%d]\n", err);
                return (0);
            }
            display_cl_device_type(devtype);
            if (devtype == CL_DEVICE_TYPE_CPU)
                platform = platform_list[i];
            if (devtype == CL_DEVICE_TYPE_GPU)
            {
                platform = platform_list[i];
                i = numplatform; // Stop
                break;
            }
        }
        //FREE(devices);
   }

   /* Access a device */
   //err = clGetDeviceIDs(platform, devtype, 1, &dev, NULL);
   err = clGetDeviceIDs(platform, devtype, 1, &devices[j], NULL);
   if(err < 0) {
      printf("Couldn't access any devices");
      *error = 1;
   }
   else
      *error = 0;
   dev = devices[j];
   //FREE(devices);
   return (dev);
}

/**
 ** build_program :
 ** Build a cl_program on device dev and context ctx, from kernel source filename.
 ** Set error pointer, error is equal to 1 if fail, 0 if success.
 ** Return : cl_program.
 **
**/
/* Create program from a file and compile it */
cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename, cl_int *error)
{
   cl_program program;
   FILE *program_handle;
   char *program_buffer, *program_log;
   size_t program_size, log_size;
   int err;

   *error = 1;
   /* Read program file and place content into buffer */
   program_handle = fopen(filename, "rb");
   ///program_handle = fopen(filename, "r");
   if(program_handle == NULL) {
      printf("Couldn't find the program file");
      return (NULL);
   }
   fseek(program_handle, 0, SEEK_END);
   program_size = ftell(program_handle);
   rewind(program_handle);
   program_buffer = (char*)ALLOC(program_size + 1);
   program_buffer[program_size] = '\0';
   fread(program_buffer, sizeof(char), program_size, program_handle);
   fclose(program_handle);
   /* Create program from file */
   program = clCreateProgramWithSource(ctx, 1,
      (const char**)&program_buffer, &program_size, &err);
   if(err < 0) {
      printf("Couldn't create the program");
      return (program);
   }
   FREE(program_buffer);

   /* Build program */
   /** CRASH ICI */
   err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL); // Crash
   ///err = clBuildProgram(program, 0, NULL, KERNEL_INCLUDE_DIRECTORY, NULL, NULL); /// Original
   ///err = clBuildProgram(program, 1, &dev, KERNEL_INCLUDE_DIRECTORY, NULL, NULL); // Crash
        ///return (program); /// DEBUG
   /** CRASH ICI */
   if(err < 0)
   {
      /* Find size of log and print to std output */
      clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG,
            0, NULL, &log_size);
      program_log = (char*) ALLOC(log_size + 1);
      program_log[log_size] = '\0';
      clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG,
            log_size + 1, program_log, NULL);
      printf("%s\n", program_log);
      FREE(program_log);
      return (program);
   }
   *error = 0;
   return (program);
}

/**
 ** init_option :
 ** Init global GPU environnement variables with default values.
 ** Return : struct s_option.
 **
**/
struct s_option         init_option(void)
{
    struct s_option         option;

    option.display_cloud = 1;
    option.display_model = 1;
    option.occlusion = 1;
    option.edit_mode = 1;
    option.display_log = 0;
    option.max_model = MAX_MODEL;
    option.point_gravity = 1;

    option.set_cloud = 1;
    //option.inc = 64; // Max // BUG CLOUD NOT ALIGNED !!! LOTS OF POINT MISSING !!!
    option.inc = 1024;
    //option.inc = 1;
    option.pixels_range[0] = 0; // Start Idx
    option.pixels_range[1] = option.inc; // Stop Idx

    option.scale_factor = 0.07;

    option.morpho_active = 0;
    option.picdiv[0] = 1;
    option.picdiv[1] = 1;
    option.mod_definition = 10;
    return (option);
}

/**
 ** init_opencl :
 ** Build up the whole struct s_opencl the return it.
 ** Takes a int pointer.
 ** Check error is equal 1 if failed, 0 if success.
 **
**/
struct s_opencl init_opencl(int *error)
{
    int                 i;
    struct s_opencl     cl;
    cl_int              err;

    *error = 1;

    memset(&cl, 0, sizeof(struct s_opencl));
    cl.sig_refresh_model = 0;
    cl.kernel = NULL;
    cl.kernel_cloud_fall = NULL;
    cl.input_model = NULL;
    cl.input_camera = NULL;
    cl.input_lights = NULL;
    cl.input_triangle = NULL;
    cl.input_picture = NULL;
    cl.input_option = NULL;
    cl.output_zbuffer = NULL;
    cl.output_pixels = NULL;
    cl.output_surface = NULL;
    cl.output_cloud = NULL;
    cl.queue = NULL;
    cl.program = NULL;
    cl.context = NULL;

    cl.cloud_buf = NULL;
    cl.picture_buf = NULL;
    cl.triangle_buf = NULL;
    cl.model_buf = NULL;
    cl.option = init_option();
    /* Create device and context */
    cl.device = create_device(&err);
    if (err)
        return (cl);
    cl.context = clCreateContext(NULL, 1, &cl.device, NULL, NULL, &err);
    if(err < 0) {
      perror("Couldn't create a context");
      return (cl);
    }

    /* Build program */
    get_device_info(&cl.info, cl.device);
    i = -1;
    while (++i < cl.info.dimensions)
    {
        printf("/!\\ Dimension [%u] Global work Size : [%zu]\n", i, cl.info.dimension_size[i]);
        if (i == 0)
            cl.global_size = cl.info.dimension_size[i];
        else
            cl.global_size *= cl.info.dimension_size[i];
    }
    printf("/!\\ Total Global Size : [%zu]\n", cl.global_size);
    cl.local_size = cl.info.max_work_group_size / 4;
    printf("/!\\ Local size set to : [%zu]\n", cl.local_size);
    ///cl.num_groups = cl.global_size / cl.local_size; // Probably bad
    cl.num_groups = (cl.info.dimension_size[0] * cl.info.dimension_size[0] /* / 4*/) / cl.local_size;
    printf("/!\\ Number of work-groups : [%zu]\n", cl.num_groups);

    cl.work_dim = 1; // One dimension work
    cl.global_work_size[0] = cl.info.dimension_size[0];
    ///cl.global_work_size[1] = 0/*cl.info.dimension_size[1]*/;
    cl.global_work_size[1] = cl.info.dimension_size[1];
    cl.global_work_size[2] = 0;
    printf("/!\\ Number Global work Size : [%zu]\n", cl.global_work_size[0]);

    cl.local_work_size[0] = cl.local_size;
    cl.local_work_size[1] = cl.local_size;
    cl.local_work_size[2] = 0;
    /*** DEBUG CONFIGURATION **/

    /*
    cl.global_size = WINX * WINY;
    cl.global_work_size[0] = WINX;
    cl.global_work_size[1] = WINY;
    cl.global_work_size[2] = 0;
    cl.local_size = 256;///cl.global_size / 256;
    printf("Debug Conf: Local size set to [%u]\n", cl.local_size);
    //cl.num_groups = cl.global_size / cl.local_size; /// Never change
    cl.num_groups = WINX / cl.local_size; /// Never change
    printf("Debug Conf: Number of work-groups : [%u]\n", cl.num_groups);
    ///cl.global_work_size[0] = cl.global_size;
    */

    /*** DEBUG CONFIGURATION **/

    printf("Build program %s\n", PROGRAM_FILE);
    cl.program = build_program(cl.context, cl.device, PROGRAM_FILE, &err);
    printf("Build program %s\n", PROGRAM_FILE_CLOUD_FALL);
    cl.program_cloud_fall = build_program(cl.context, cl.device, PROGRAM_FILE_CLOUD_FALL, &err);
    if (!err)
        *error = 0;
    printf("Create command queue");
    cl.queue = clCreateCommandQueue(cl.context, cl.device, 0, &err);
    if(err < 0) {
      printf("Couldn't create command queue\n");
      return (cl);
    }
    return (cl);
}
