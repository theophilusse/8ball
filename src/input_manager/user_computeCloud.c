#include "input_manager.h"

// Compute barycentric coordinates (u, v, w) for
// point p with respect to triangle (a, b, c)
void        Barycentric(double *p, double *a, double *b, double *c, double *barycenter)
{
    double v0[4];
    double v1[4];
    double v2[4];

    sub_v3(b, a, v0);
    sub_v3(c, a, v1);
    sub_v3(p, a, v2);
    /*
    v0 = b - a,
    v1 = c - a,
    v2 = p - a;
    */

    double d00 = dot_prod3(v0, v0);
    double d01 = dot_prod3(v0, v1);
    double d11 = dot_prod3(v1, v1);
    double d20 = dot_prod3(v2, v0);
    double d21 = dot_prod3(v2, v1);
    double denom = d00 * d11 - d01 * d01;
	/*
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
	*/
	///barycenter = (double4)(0,0,0,0);
	barycenter[0] = -1;
	barycenter[1] = -1;
	barycenter[2] = -1;
	if (denom != 0)
	{
		barycenter[0] = (d11 * d20 - d01 * d21) / denom;
		barycenter[1] = (d00 * d21 - d01 * d20) / denom;
		barycenter[2] = 1.0f - barycenter[0] - barycenter[1];
	}
}

double 			fall(double *particle, double *gravity, uint nvertices, double* a, double* b, double* c, double *cloud_debug) // Test private triangles
{
	double					bary[4];
	double					I[4];
	double           		n[4];
	double           		u[4];
	double           		v[4];
	double 			tmp[4];
	double 			tnorm[4];
	double w[4];
	double wa[4];
	double wb[4];
	double D[4];
	double 					priv_minimum_zdist; //
	double 					zdist;
	double denom;
	double num;
	//struct s_triangle 		T; // Optional
	/*uint 				global_size;
	uint 				global_id;
	uint 				local_size;
	uint 				local_id;
	uint 				num_groups;
	uint 				group_id;*/

	/*global_size = get_global_size(0);
	global_id = get_global_id(0);
	local_size = get_local_size(0);
	local_id = get_local_id(0);
	num_groups = get_num_groups(0);
	group_id = get_group_id(0);*/

	uint 		addr;
	uint 		k = 0;

	k = 0;
	zdist = 0;
	//addr = local_id * 3;
	/*a = triangle[addr];
	b = triangle[addr + 1];
	c = triangle[addr + 2];*/
	/*u = a - c;
	v = b - c;*/ // Original
	/*u = c - a;
	v = c - b;*/
	sub_v3(c, a, u);
	sub_v3(c, b, v);

        cross_prod3(u, v, tmp);
		unit3(tmp, tnorm, NULL);

		//sub_v3(a, particle, w);
		sub_v3(c, particle, w);
		denom = dot_prod3(gravity, tnorm);
		///denom = _dot(gravity, -gravity); // Debug
		//num = _dot(w, tnorm);
		num = dot_prod3(w, tnorm);
		///num = _dot(w, -gravity);
		//if (denom > 0)
		if (denom != 0)
			zdist = num / denom;
        ///printf("z:[%f]\n", zdist);///f

		/** zdist = Intersect(a, tnorm, particle, gravity);**/ // KEEP
		//I = (double4)(0,0,0,0) + (particle + zdist * gravity); // No cast test*

		I[0] = 0 + (particle[0] + zdist * gravity[0]); // No cast test
		I[1] = 0 + (particle[1] + zdist * gravity[1]); // No cast test
		I[2] = 0 + (particle[2] + zdist * gravity[2]); // No cast test
		/** I[3] = 0 + (particle[3] + zdist * gravity[3]); // No cast test **/
		//I = particle + (zdist * gravity); // No cast test
		/**zdist *= Barycentric(I, a, b, c, &bary);**/

		/***** bary.x problem ******/
		Barycentric(I, a, b, c, bary); // Keep

		if (bary[0] > 1)
			zdist = 0;
		 if (bary[1] > 1)
			zdist = 0;
		if (bary[2] > 1)
			zdist = 0;
		if (bary[0] < 0)
			zdist = 0;
		if (bary[1] < 0)
			zdist = 0;
		if (bary[2] < 0)
			zdist = 0;
		/*if ( addr + 2 <= nvertices ) // Test Local memory /////////////
			zdist = 0;*/
	///barrier(CLK_LOCAL_MEM_FENCE); ///
	///if (zdist > 0)
	///if (zdist < DBL_EPSILON)
	/*return (5);*/
	if (zdist == 0)
		return (DBL_MAX);
	return (zdist);
}

/**
void 			set_cloud_from_picture(__global s_backbuffer *picture, __global double4 *cloud, struct s_option opt)
{
	struct t_backbuffer pb;
	double4		point;
	double 		scale_factor = 0.01;
	double 		pavg;
	double 		depth;
	uint2		coord;
	uint2 		dim;
	uint 		global_addr;
	uint 		global_size;
	uint 		local_addr;
	uint 		local_size;
	uint 		group_addr;
	uint         x;
    uint         y;
	uint 		npix;
	uint 		gnpix;
	uint 		k;
	uint 		adr;
	__global uchar *pixels;

	pb = *picture;
	pixels = ((__global uchar *)&picture->pixels);
	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);

	uint index;
	dim = pb.dim;
	npix = dim.x * dim.y;
	gnpix = npix * 4;

	uint cadr;
	uint pitch;
	uint bpp;
	pitch = pb.pitch;
	bpp = pitch / dim.x;
	k = -1;
	while ( (index = (++k * global_size) + global_addr) < npix )
	{
		coord.y = ( index / dim.x );
		coord.x = ( index % dim.x );
		//if ( (coord.x < dim.x && coord.x > 0) && // BUG , MOD
		//	(coord.y < dim.y && coord.y > 0) )
		//{
			depth = 0;//global_addr;//10; // Debug
			adr = ((coord.y * pitch) + coord.x * bpp); // TEST
			cadr = ((coord.y * dim.x) + coord.x); // TEST

			pavg = ( pixels[ adr ] + pixels[ adr + 1 ] + pixels[ adr + 2 ] ); /// 24bpp no div

			point.x = (double)(coord.x * opt.scale_factor) - ((dim.x / 2) * opt.scale_factor);
			point.y = (double)((dim.y / 2) * opt.scale_factor) - (coord.y * opt.scale_factor);
			//point.z = (double)coord.z * scale_factor;
			//point.z = (double)pavg * 0.001;
			point.z = -100;
			point.w = (double)0;

			if (cadr < npix)
				cloud[cadr] = point;
		//}
	}
}
***/

void            *td_computeCloudFall(void *p_mega)
{
    t_multithread_item          *pThread;
    t_mega      *mega;
    t_camdata   *data;
    uchar       *pixel;
    double      depth;
    struct s_model     model;
    size_t        zCloud;
    double      *pCloud;
    int         *pFace;
    double      *pVert;
    double gravity[3];
    struct s_triangle       T;
    struct s_ray            R;
    uint        bpp;
    uint        pitch;
    uint        gaddr_pic;

    if (!(pThread = (t_multithread_item *)p_mega))
        pthread_exit (NULL);
    if (!(mega = (t_mega *)pThread->shared))
        pthread_exit (NULL);
    if (!mega->camera || !(data = mega->camera->data))
        pthread_exit (NULL);
    if (!(pixel = (uchar *)mega->picture->pixels))
        pthread_exit (NULL);
    if (!mega->stcl)
        pthread_exit (NULL);
    zCloud = mega->stcl->cloud_bufsz;
    if (!(pCloud = mega->stcl->cloud_buf))
        pthread_exit (NULL);

    pitch = (uint)mega->picture->pitch;
    bpp = pitch / (uint)mega->picture->w;
    double      picdiv[2];
    picdiv[0] = mega->stcl->option.picdiv[0];
    picdiv[1] = mega->stcl->option.picdiv[1];
    gravity[0] = 0;
    gravity[1] = 0;
    gravity[2] = 1;
    int intersect;
    uint seg;
    float f_seg;
    uint i;
    uint k;
    uint dParticle;
    uint addr;
    double          dist_min;
    double          hit[4];

    f_seg = ((zCloud / (sizeof(double) * 4)) / THREAD_COUNT);
    //printf("Base : f_seg : [%f]\n", f_seg);
    ///printf("Base : f_seg : [%f]\n", (float)(zCloud / (sizeof(double) * 4)));
    while (f_seg > (1.0 - FLT_EPSILON))
        f_seg -= 1.0;
    ///printf("f_seg : [%f]\n", f_seg);

    uint tFrom = ((zCloud / (sizeof(double) * 4)) / THREAD_COUNT) * (uint)pThread->index;
    uint tTo = tFrom + ((zCloud / (sizeof(double) * 4)) / THREAD_COUNT);
    dParticle = tFrom;
    //pCloud += 4; /// Test
    pCloud += dParticle * 4;
    uint moduleDist = 1;
    uint currentLine;

    if (0) /// Old.
    {
        double      len;
        len = length3(mega->camera->o);
        if (len <= 1)
            moduleDist = 1;
        else
            moduleDist = (uint)( (len * len) * 0.005 ) + 1;
    }
    moduleDist = mega->stcl->option.mod_definition;

    ///pCloud += (dParticle * 4) * 4;
    //while (dParticle < zCloud / (sizeof(double) * 4))
    ///printf("[Thread:%d][tFrom:%u][tTo:%u]\n", (uint)pThread->index, tFrom, tTo);

    *((uint *)pThread->local) = 0;
    while (dParticle < tTo && mega->thread.global == 1)
    {
        depth = 0;
        currentLine = dParticle / mega->picture->w; /// Test
        i = -1;
        dist_min = DBL_MAX;
        while ((currentLine % moduleDist) == 0 && (dParticle % moduleDist) == 0 && ++i < MAX_MODEL) // For each model
        {
            model = data->model[i];
            if (model.active == 0) // If model is active
                break;
            if ((pFace = model.f) && (pVert = model.v)) // ->retrieves model's pointers
                while (*pFace != 0) // For Each faces
                {
                    /*seg = 3;
                    while (seg < *pFace + 1)*/
                    seg = 0;
                    while (seg < *pFace - 2)
                    {
                        copy_v3(&pVert[(/*1 + */pFace[1]) * (uint)(pVert[1])], T.v0);
                        copy_v3(&pVert[(/*1 + */pFace[seg + 2]) * (uint)(pVert[1])], T.v1);
                        copy_v3(&pVert[(/*1 + */pFace[seg + 3]) * (uint)(pVert[1])], T.v2);
                        /*k = 0;
                        printf("pFace[%d][%d][%d][%d][%d]\n", pFace[0], pFace[1], pFace[2], pFace[3], pFace[4]);*/
                        // // Normal !!!
                        sub_v3(T.v0, T.v2, T.u);
                        sub_v3(T.v1, T.v2, T.v);
                        cross_prod3(T.u, T.v, T.n);
                        /**
                            // intersect3D_RayTriangle(): find the 3D intersection of a ray with a triangle
                            //    Input:  a ray R, and a triangle T
                            //    Output: *I = intersection point (when it exists)
                            //    Return: -1 = triangle is degenerate (a segment or point)
                            //             0 =  disjoint (no intersect)
                            //             1 =  intersect in unique point I1
                            //             2 =  are in the same plane
                            // Raytrace //
                            int intersect3D_RayTriangle( struct s_ray R, struct s_triangle T, double* I , double *Dist );
                        **/
                        R.direction[0] = 0;
                        R.direction[1] = 0;
                        R.direction[2] = -1;
                        copy_v3(pCloud, R.origine);
                        R.origine[2] = DBL_MAX; ///
                        //R.origine[2] = 10; ///
                        //if ((intersect = intersect3D_RayTriangle(R, T, hit, &hit[3] )) == 1)
                        ///double 			fall(double *particle, double *gravity, uint nvertices, double* a, double* b, double* c, double *cloud_debug) // Test private triangles
                        hit[3] = fall(pCloud, gravity, model.v[0], T.v0, T.v1, T.v2, hit); // Test private triangles
                        if (hit[3] != DBL_MAX) // Hitting surface
                        {
                            if (hit[3] < dist_min)
                            {
                                dist_min = hit[3];
                                ///gaddr_pic = (currentLine * pitch) + (dParticle % pitch); // Original
                                ///gaddr_pic = (gaddr_pic % pitch); /// X
                                ///gaddr_pic += (currentLine * pitch); /// Y
                                gaddr_pic = (dParticle * bpp); /// Test
                                depth = ((double)pixel[gaddr_pic] + (double)pixel[gaddr_pic + 1] + (double)pixel[gaddr_pic + 2]) / 3;
                                ///depth /= 16; /// Test
                                depth = (double)((uint)depth / 16); /// Test
                                ///printf("addr[%u]\n", gaddr_pic);
                                ///printf("depth[%f]\n", depth);
                            }
                        }
                        seg++;
                    }
                    pFace += pFace[0] + 1;
                }
        }
        //copy_v3(hit, pCloud);
        //pCloud[3] = dist_min;
        //pCloud[2] = dist_min;
        if (dist_min == DBL_MAX)
        {
            pCloud[2] = 0;
            pCloud[3] = 0;
        }
        else
        {
            pCloud[0] = pCloud[0] + gravity[0] * dist_min; // Keep
            ///pCloud[0] = pCloud[0];
            pCloud[1] = pCloud[1] + gravity[1] * dist_min; // Keep
            pCloud[2] = pCloud[2] + gravity[2] * dist_min; // Keep
            ///pCloud[3] = dist_min; // Old
            ///pCloud[3] = depth + 1;
            pCloud[3] = depth;
        }
        dParticle++;
        pCloud += 4;
        *((uint *)pThread->local) = dParticle - tFrom;
    }
    pthread_exit (NULL);
    return (NULL);
}

void            *td_displayLoading(void *p_mega)
{
    t_multithread_item          *pThread;
    t_mega      *mega;
    size_t        zCloud;
    uint        tSum;
    uint        tTo;
    uint        count;
    int         index;
    float       fPercent[2];
    float       fUnit;
    Uint8       *key;

    if (!(pThread = (t_multithread_item *)p_mega))
        pthread_exit (NULL);
    if (!(mega = (t_mega *)pThread->shared))
        pthread_exit (NULL);
    if (!mega->stcl)
        pthread_exit (NULL);
    if (!(zCloud = mega->stcl->cloud_bufsz))
        pthread_exit(NULL);
    charset_print_noAlpha(mega->screen, mega->ui->font.charset, 0, mega->viewport->h - 26, "Loading... [Press 's' to abort]");
    tSum = 0;
    tTo = (zCloud / (sizeof(double) * 4));
    fUnit = 1.0 / tTo;
    fPercent[1] = 0.0;
    while (tSum < tTo - 16)
    {
        count = 0;
        index = -1;
        while (++index < THREAD_COUNT)
            count += mega->thread.local_data[index];
        if (tSum < count)/// && count < tTo - 16)
        {
            tSum = count;
            fPercent[0] = fPercent[1];
            fPercent[1] = (float)tSum * fUnit;
            ///loading_bar(loadingBar, fPercent[0], fPercent[1]);
            loading_bar(mega->screen, fPercent[0], fPercent[1]);
            SDL_Flip(mega->screen);
            ///blit_and_flip_at(loadingBar, mega->screen, 0, mega->viewport->h - (loadingBar->h + 1)); // Render !
            ///blit(loadingBar, mega->screen);
        }
        //

        // KEEP : Key 's'->Stop process.
        SDL_PumpEvents();
        key = SDL_GetKeyState(NULL);
        if (key[SDLK_s])
        {
            BEEP_WARNING
            mega->thread.global = 0;
            return ((void *)key);
        }

        // Garbage.
        ///printf("Local Val [%u]\n", *((uint *)pThread->local)); ///
        /*printf("Local Val [%u]\n", count); ///
        DEBUG*/
        /*if (count >= 3)
        {
            pthread_exit (NULL);
            return (NULL);
        }*/
        //
    }
    pthread_exit(NULL);
    return (NULL);
}

int             user_computeCloud_CPU(t_mega *mega, int flg)
{
    uint            i;
    ///int pthread_join (pthread_t th, void ** thread_return);

    if (!mega->camera->data)
        return (1);


    /************ PREPARE BUFFER FIRST !!! ************/
    user_computeCloud(mega, 0);
    //return (0);
    ///double          *pCld;

    /// Vector4 format : R, G, B, (DEPTH)
    /// TODO : void set_cloud_from_picture(__global s_backbuffer *picture,
    ///                                    __global double4 *cloud,
    ///                                    struct s_option opt)

    /************ PREPARE BUFFER FIRST !!! ************/
    ///return (0);
    /** int pthread_create (pthread_t * thread, NULL, void * (* start_routine) (void *), void * arg); **/
    mega->thread.fTask = td_computeCloudFall;
    mega->thread.fDisp = td_displayLoading;
    i = -1;
    while (++i < THREAD_COUNT)
        mega->thread.local_data[i] = 0;
    mega->thread.global = 1;
    i = -1;
    while (++i < THREAD_COUNT)
    {
        mega->thread.item[i].index = (uchar)i; ///
        mega->thread.item[i].shared = mega; ///
        mega->thread.item[i].local = (void *)&mega->thread.local_data[i]; ///
        mega->thread.item[i].global = (void *)&mega->thread.global; ///
        if (pthread_create(&mega->thread.item[i].thread, NULL, mega->thread.fTask, (void *)&mega->thread.item[i]))
        {
            printf("[pthread_create error]\n"); //
            i = -1;
            while (++i < THREAD_COUNT)
            {
                pthread_cancel(mega->thread.item[i].thread);
            }
            // Need some precautions
            return (1);
        }
    }
    mega->thread.item[THREAD_COUNT].shared = mega; ///
    if (pthread_create(&mega->thread.item[THREAD_COUNT].thread, NULL, mega->thread.fDisp, (void *)&mega->thread.item[THREAD_COUNT]))
    {
        i = -1;
        while (++i < THREAD_COUNT + 1)
        {
            pthread_cancel(mega->thread.item[i].thread);
        }
    }

    ///int intersect3D_RayTriangle( struct s_ray R, struct s_triangle T, double* I , double *Dist )
    ///int intersect3D_RayTriangle( struct s_ray R, struct s_triangle T, double* I , double *Dist )
    /* Attente de la fin des threads. */
    i = -1;
    while (++i < THREAD_COUNT + 1)
    {
        pthread_join(mega->thread.item[i].thread, NULL);
    }

    /**
    if (pthread_join(mega->thread.item[THREAD_COUNT].thread, NULL))
    {
        i = -1;
        while (++i < THREAD_COUNT)
        {
            pthread_cancel(mega->thread.item[i].thread);
        }
    }
    i = -1;
    while (++i < THREAD_COUNT)
    {
        pthread_join(mega->thread.item[i].thread, NULL);
    }
    **/


    uint err;
    /// WRITE CLOUD BACK TO GRAM
    /*
    if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->output_cloud,
                                    CL_TRUE, 0, mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 7 [%d]\n", err);
        return (1);
    }
    */
    /*if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->output_cloud,
                                    CL_TRUE, 0, mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 7 [%d]\n", err);
        return (1);
    }*/
    /*if ((err = clEnqueueWriteBuffer(cl->queue, cl->output_cloud,
                                    CL_TRUE, 0, cl->cloud_bufsz, cl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 7 [%d]\n", err);
        return (1);
    }*/
    /*if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->output_cloud,
                                    CL_TRUE, 0, mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write cloud buffer error:[%d]\n", err);
        return (1);
    }*/
    if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->output_cloud,
                                    CL_TRUE, 0, mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 7 [%d]\n", err);
        return (1);
    }
    //mega->stcl->option.set_cloud = 1;
    return (0);
}

int             user_computeCloud(t_mega *mega, int flg)
{
    /** OpenCL Stuff **/
    int         err;
    uint        debug_cloud = 1;

    mega->stcl->option.set_cloud = 1;
    mega->stcl->option.pixels_range[0] = 0; // Start Idx
    mega->stcl->option.pixels_range[1] = mega->stcl->option.inc; // Stop Idx
    while ( mega->stcl->option.pixels_range[0] < mega->picture->w * mega->picture->h)
    {
        if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->input_option, // OUT_OF_RESOURCES Second exe
                                    CL_TRUE, 0, sizeof(struct s_option), &mega->stcl->option, 0, NULL, NULL)) != CL_SUCCESS)
        {
            printf("Couldn't write option.pixels_range error:[%d]\n", err);
            return (1);
        }
        err = (int)clEnqueueNDRangeKernel(mega->stcl->queue, mega->stcl->kernel_cloud_fall, mega->stcl->work_dim,
                                        NULL, mega->stcl->global_work_size, mega->stcl->local_work_size,
                                        0, NULL, NULL);
        if (err != CL_SUCCESS)
        {
            printf("clEnqueueNDRangeKernel cloud_fall ERROR [%d]\n", err);
            return (1);
        }
        mega->stcl->option.set_cloud = 0;
        mega->stcl->option.pixels_range[0] += mega->stcl->option.inc;
        mega->stcl->option.pixels_range[1] = mega->stcl->option.pixels_range[0] + mega->stcl->option.inc;
    }
    /* ********* CLOUD RESULT ********* */
    clFinish(mega->stcl->queue);
    if ((err = clEnqueueReadBuffer(mega->stcl->queue, mega->stcl->input_cloud, CL_TRUE, 0,
                                   mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("clEnqueueReadBuffer ERROR [%d]\n", err);
        return (1);
    }
    if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->output_cloud,
                                    CL_TRUE, 0, mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 7 [%d]\n", err);
        return (1);
    }/**
    if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->input_cloud,
                                    CL_TRUE, 0, mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 7 [%d]\n", err);
        return (1);
    }**/
    ///print_vector_array((double *)stcl.cloud_buf, stcl.cloud_bufsz / sizeof(double)); // Debug PRINT ALL
    ///print_vector_array((double *)mega->stcl->cloud_buf, 64); // Debug

    /* ********* INIT CAMERA ********** */
    ///return (root_destructor(screen, viewport, picture, charset, camera, &stcl, 1));
    /*if (init_kernel(mega->stcl))
    {
        printf("Init OpenCL Kernel : ERROR.\n");
        return (1);
    } *//// ????

    ///return (root_destructor(screen, viewport, picture, charset, camera, &stcl, 1));
    /** Run **/
    printf("Success\n");
    /*** DEBUG Picture ***/
    /*blit_at(picture, viewport, (picture->w / 2) - 50, (picture->h / 2) - 50);
    refresh(viewport, screen);*/
    /*** DEBUG Picture ***/


    /*err = (int)clEnqueueNDRangeKernel(stcl.queue,
        stcl.kernel,
        stcl.work_dim,
        NULL,
        stcl.global_work_size,
        NULL,
        0,
        NULL,
        NULL);
    //clFinish(stcl.queue);
    if (err != CL_SUCCESS)
        printf("clEnqueueNDRangeKernel ERROR [%d]\n", err);
    if ((err = clEnqueueReadBuffer(stcl.queue, stcl.output_pixels, CL_FALSE, 0, stcl.pixels_bufsz, camera->data->backbuffer->pixels, 0, NULL, NULL)) != CL_SUCCESS)
        printf("clEnqueueReadBuffer ERROR [%d]\n", err);
    //clFinish(stcl.queue);
    */
    /** OpenCL Stuff **/
    return (0);
}
