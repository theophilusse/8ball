#include "opencl_util.h"

int        init_clmem_option(t_opencl *cl)
{
    cl_int      err;

    cl->input_option = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
         sizeof(struct s_option), &cl->option, &err);
    if (err < 0) {
        printf("Couldn't create option buffer\n");
        return (1);
    }
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_option,
                                    /*CL_FALSE*/CL_TRUE, 0,  sizeof(struct s_option), (void *)&cl->option, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1\n");
        return (1);
    }
    return (0);
}

int        init_clmem_picture(t_opencl *cl, SDL_Surface *picture)
{
    cl_int      err;

    DEBUG ///
    /*** // Original.
    cl->picture_bufsz = ((picture->h * picture->pitch) + picture->w * (picture->pitch / picture->w))
                        + (4 * sizeof(uint));
    ***/
    cl->picture_bufsz = ((picture->h * picture->w) * (picture->pitch / picture->w))
                        + (4 * sizeof(uint));
    printf("Picturze BUFSZ [%u]\n", cl->picture_bufsz); /// Debug.
    if (!(cl->picture_buf = (void *)ALLOC((size_t)cl->picture_bufsz)))
        return (1);
    ((uint *)cl->picture_buf)[0] = (uint)picture->w;
    ((uint *)cl->picture_buf)[1] = (uint)picture->h;
    ((uint *)cl->picture_buf)[2] = (uint)picture->pitch; /// PITCH
    ((uint *)cl->picture_buf)[3] = (uint)(picture->pitch / picture->w); /// BPP
    cl->picture_bufsz -= 650;
    // Original.
        memcpy((void *)&(((uint *)cl->picture_buf)[4]), picture->pixels, cl->picture_bufsz - (4 * sizeof(uint))); // Test
    ///memccpy((void *)&(((uint *)cl->picture_buf)[4]), picture->pixels, 1, cl->picture_bufsz - (4 * sizeof(uint)));

    ///(picture->h * picture->pitch) + picture->w * (picture->pitch / picture->w); // MAP A PIXEL

    cl->input_picture = clCreateBuffer(cl->context, CL_MEM_READ_WRITE //CL_MEM_READ_ONLY
         ///CL_MEM_COPY_HOST_PTR, (cl->picture_bufsz * sizeof(uchar)) + (sizeof(uint) * 4),
                                , cl->picture_bufsz,
                                cl->picture_buf, &err);
    if(err < 0)
    {
        printf("Couldn't create picture buffer\n");
        return (1);
    }
   if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_picture,
                                    /*CL_FALSE*/CL_TRUE, 0,  cl->picture_bufsz, cl->picture_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1\n");
        return (1);
    }
    return (0);
}

int        init_clmem_cloud_buffer(t_opencl *cl, SDL_Surface *picture, int flg)
{
    cl_int      err;

    if (flg == 1) /** Export Mode - Total picture **/
    {
        /** Build Cloud Buffer **/
        cl->cloud_bufsz = ((picture->w * picture->h) * (sizeof(double) * 4));
        if (!(cl->cloud_buf = ALLOC(cl->cloud_bufsz)))
        {
            printf("Couldn't allocate Cloud Host Buffer\n");
            return (1);
        }
        cl->output_cloud = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, /** kernel.cl **/
             cl->cloud_bufsz, cl->cloud_buf, &err);
        if (err < 0) {
            printf("Couldn't create output cloud buffer\n");
            return (1);
        }
        cl->input_cloud = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, /** Unsused ? **/
            cl->cloud_bufsz, cl->cloud_buf, &err);
        if (err < 0) {
            printf("Couldn't create input cloud buffer\n");
            return (1);
        }
        return (0);
        /** Build Cloud Buffer **/
    }
    if (flg == 0) /** Preview Mode **/ /// Deadcode
    {
        /** Build Cloud Buffer **/
        if (picture->w <= 100 && picture->h <= 100)
            return (init_clmem_cloud_buffer(cl, picture, 1));
        if (picture->w <= 100)
            cl->option.picdiv[0] = 1;
        else
            cl->option.picdiv[0] = ((float)picture->w / 100);
        if (picture->h <= 100)
            cl->option.picdiv[1] = 1;
        else
            cl->option.picdiv[1] = ((float)picture->h / 100);
        printf("picdiv[%f][%f], [%f][%f]\n", cl->option.picdiv[0], cl->option.picdiv[1], (picture->w / cl->option.picdiv[0]), (picture->h / cl->option.picdiv[1])); ///
        ///return (1); /*** DEBUG ***/

        ///cl->cloud_bufsz = (((picture->w / cl->option.picdiv[0]) * (picture->h / cl->option.picdiv[1])) * (sizeof(double) * 4));
        cl->cloud_bufsz = ((100 * 100) * (sizeof(double) * 4));
        if (!(cl->cloud_buf = ALLOC(cl->cloud_bufsz)))
        {
            printf("Couldn't allocate Cloud Host Buffer\n");
            return (1);
        }
        cl->output_cloud = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, /** kernel.cl **/
             cl->cloud_bufsz, cl->cloud_buf, &err);
        if (err < 0) {
            printf("Couldn't create output cloud buffer\n");
            return (1);
        }
        cl->input_cloud = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, /** Unsused ? **/
            cl->cloud_bufsz, cl->cloud_buf, &err);
        if (err < 0) {
            printf("Couldn't create input cloud buffer\n");
            return (1);
        }
        /** Build Cloud Buffer **/
        return (0);
    }
    return (1);
}

int         init_clmem_triangle(t_camdata *camdata, t_opencl *cl)
{
    cl_int              err;

    cl->output_surface = NULL;
    cl->input_triangle = NULL;
    if (push_triangle_opencl(cl, camdata))
        return (1);
    cl->input_triangle = clCreateBuffer(cl->context, CL_MEM_READ_ONLY /*|
         CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR*/, cl->triangle_bufsz, cl->triangle_buf, &err);
    if (err != CL_SUCCESS)
    {
        printf("Couldn't create model buffer\n");
        return (1);
    }
    cl->output_surface = clCreateBuffer(cl->context, CL_MEM_READ_ONLY /*|
         CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR*/, cl->surface_bufsz, cl->surface_buf, &err);
    if (err != CL_SUCCESS)
    {
        printf("Couldn't create triangle surface buffer\n");
        return (1);
    }
    ///print_vector_array((double *)cl->triangle_buf + 4, 12); // Debug
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_triangle,
                                    /*CL_FALSE*/CL_TRUE, 0,  cl->triangle_bufsz, cl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1\n");
        return (1);
    }
    printf("Model buffer ptr  : [%p]\n", cl->triangle_buf); //
    printf("Model triangle n. : [%u]\n", (cl->triangle_bufsz - sizeof(struct s_point)) / (sizeof(struct s_point) * 3)); //
    printf("Model buffer size : [%u]\n", cl->triangle_bufsz); //
    printf("Memory object : [%p]\n", cl->input_triangle); //
    return (0);
};


int         init_clmem(t_cam *cam, double *sun, SDL_Surface *picture, t_opencl *cl)
{
    cl_int              err;

    if (!cam)
        return (1);
    cl->model_buf = NULL;
    cl->input_camera = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                                      sizeof(struct s_cam) - sizeof(t_camdata *), cam, &err);
    if (err < 0)
        printf("Couldn't create camera\n");
    cl->input_lights = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                      sizeof(double) * 4, sun, &err);
    if (err < 0)
        printf("Couldn't create sundata\n");
    if (push_model_opencl(cl, cam->data))
        return (1);
    printf("[%p] Model @%p size:[%u]\n", cl->context, cl->model_buf, cl->model_bufsz); // Debug
    cl->input_model = clCreateBuffer(cl->context, CL_MEM_READ_ONLY /*|
         CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR*/, cl->model_bufsz, cl->model_buf, &err);
    if (err != CL_SUCCESS)
    {
        printf("Couldn't create model buffer\n");
        return (1);
    }
    /**
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_model, CL_TRUE, 0, cl->model_bufsz, cl->model_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write model buffer\n");
        return (1);
    }*/
    cl->zbuffer_bufsz = (cam->vw * cam->vh) * (sizeof(double) * 4);
    cl->output_zbuffer = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
         ///(cam->vw * cam->vh) * (sizeof(double) + 3 * sizeof(uchar)), cam->data->zbuffer, &err);
         cl->zbuffer_bufsz, cam->data->zbuffer, &err);
    if (err < 0)
        printf("Couldn't create zbuffer\n");
    cl->pixels_bufsz = cam->data->backbuffer->w * cam->data->backbuffer->h * (cam->data->backbuffer->pitch / cam->data->backbuffer->w);
    cl->output_pixels = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
         cl->pixels_bufsz, cam->data->backbuffer->pixels, &err);
    if (err < 0)
        printf("Couldn't create backbuffer\n");

    /* Create a command queue */
    /**
     cl_int clEnqueueWriteBuffer ( 	cl_command_queue command_queue,
        cl_mem buffer,
        cl_bool blocking_write,
        size_t offset,
        size_t cb,
        const void *ptr,
        cl_uint num_events_in_wait_list,
        const cl_event *event_wait_list,
        cl_event *event)
    **/
    printf("Sizeof S_CAM : [%u]\n", sizeof(struct s_cam) - sizeof(void *)); /// Debug Alignement
    printf("Sizeof uint : [%u]\n", sizeof(uint) ); /// Debug Alignement
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_camera,
                                    /*CL_FALSE*/CL_TRUE, 0,  sizeof(struct s_cam) - sizeof(t_camdata *), cam, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1\n");
        return (1);
    }
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_lights,
                                    /*CL_FALSE*/CL_TRUE, 0,  sizeof(double) * 3, sun, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 2\n");
        return (1);
    }
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_picture,
                                    /*CL_FALSE*/CL_TRUE, 0,  cl->picture_bufsz, cl->picture_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 3\n");
        return (1);
    }
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->output_zbuffer,
                                    /*CL_FALSE*/CL_TRUE, 0,  (cam->vw * cam->vh) * (sizeof(double) * 4)/*(sizeof(double) + 3 * sizeof(uchar))*/, cam->data->zbuffer, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 4\n");
        return (1);
    }
    ///if (cl->input_triangle)
        /*if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_model,
                                        CL_TRUE, 0, cl->model_bufsz, cl->model_buf, 0, NULL, NULL)) != CL_SUCCESS)
        {
            printf("Couldn't write buffer 5\n");
            return (1);
        }*/
        /*if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_triangle,
                                        CL_TRUE, 0, cl->triangle_bufsz, cl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
        {
            printf("Couldn't write buffer 5\n");
            return (1);
        }*/
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->output_pixels,
                                    /*CL_FALSE*/CL_TRUE, 0, cl->pixels_bufsz, cam->data->backbuffer->pixels, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 6\n");
        return (1);
    }
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->output_cloud,
                                    CL_TRUE, 0, cl->cloud_bufsz, cl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 7 [%d]\n", err);
        return (1);
    }
    if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_option,
                                    /*CL_FALSE*/CL_TRUE, 0, sizeof(struct s_option), &cl->option, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 8\n");
        return (1);
    }
    return (0);
};
