#include "opencl_util.h"

/*
    cl->input_models = clCreateBuffer(cl->context, CL_MEM_READ_ONLY |
         CL_MEM_COPY_HOST_PTR, (sizeof(struct s_model) - sizeof(void *) * 3) * , sun, &err); ///
    if (err < 0)
        printf("Couldn't create sundata\n");
*/

size_t              f_buffer_size(int *f)
{
    size_t          a;
    size_t          jmp;

    if (!f)
        return (0);
    a = 0;
    while (*f != 0)
    {
        jmp = *f + 1;
        a += jmp;
        f += jmp;
    }
    return (sizeof(int) * a);
}

int                 push_model_opencl(t_opencl *cl, t_camdata *d)
{
    int         mdl;
    t_model     *m;

    DEBUG ///
    if (!cl || !d)
        return (1);

    /*** Count ***/
    size_t total_size;
    total_size = 0;
    size_t face_buf_sz;

    m = &d->model[0];
    mdl = 0;
    ///while (d->model[mdl].active == 1)
    while (mdl < MAX_MODEL)
    {
        if (m->active != 1)
            break;
        if (!m->v || !m->f || !m->n)
            continue;
        total_size += (sizeof(struct s_gpu_model))/// Structure size minus pointers
                        + (sizeof(double) * (size_t)((m->v[0] + 1) * m->v[1])) /// Vertice Buf
                        + (sizeof(double) * (size_t)((m->n[0] + 1) * m->n[1])) /// Normal Buf
                        + f_buffer_size(m->f); /// Face Buf
        /** /// No Normals.
        total_size += (sizeof(struct s_gpu_model))/// Structure size minus pointers
                        + (sizeof(double) * (size_t)((m->v[0] + 1) * m->v[1])) /// Vertice Buf
                        + f_buffer_size(m->f); /// Face Buf
        **/
        m++;
        mdl++;
        /*if (++mdl >= MAX_MODEL)
            return (1);*/
    }

    /** /// Debug.
        printf("v_buffer_size : %u\n", (sizeof(double) * (size_t)((m->v[0] + 1) * m->v[1])));
        printf("v_nvert : %u\n", (size_t)(m->v[0] + 1) );// * m->v[1])));
        printf("v_size : %u\n", (size_t)(m->v[1]) );// * m->v[1])));
        printf("v_type : %u\n", sizeof(double) );// * m->v[1])));
        printf("n_buffer_size : %u\n", (sizeof(double) * (size_t)((m->n[0] + 1) * m->n[1])));
        printf("f_buffer_size : %u\n", f_buffer_size(m->f));
    **/
    /*** Alloc ***/
    void            *host_model_buffer;

    total_size += sizeof(size_t); /// Test.
    printf("[GPU] Allocating %zu bytes geometry.\n", total_size);
    if (!(host_model_buffer = ALLOC(total_size)))
        return (1);

    /*** Bake ***/
    void                *cpyret;
    t_gpu_model         *gpumodel;
    /**((size_t *)host_model_buffer) = total_size - sizeof(size_t);
    gpumodel = ((size_t *)host_model_buffer) + 1;*/
    gpumodel = ((t_gpu_model *)host_model_buffer);
    mdl = 0;
    while (d->model[mdl].active == 1)
    {
        m = &d->model[mdl];
        gpumodel->active = m->active;
        copy_v3(m->_translate, gpumodel->_translate);
        copy_v3(m->_rotate, gpumodel->_rotate);
        copy_v3(m->_scale, gpumodel->_scale);
        gpumodel->_ambiant_color[0] = m->_ambiant_color[0];
        gpumodel->_ambiant_color[1] = m->_ambiant_color[1];
        gpumodel->_ambiant_color[2] = m->_ambiant_color[2];
        ///gpumodel->_ambiant_color[3] = m->_ambiant_color[3]; /* no Alpha */
        gpumodel->nv = m->nv;
        gpumodel->nn = m->nn;
        gpumodel->nf = m->nf;
        /*gpumodel->v_jmp = 0;*/

        ///gpumodel->n_jmp = (size_t)((m->v[0] + 1) * m->v[1]) * sizeof(double);
        ///gpumodel->n_jmp = (uint)((m->v[0] + 1) * m->v[1]) * sizeof(double);
        gpumodel->n_jmp = (size_t)((m->v[0] + 1) * m->v[1]) * sizeof(double);
        //gpumodel->n_jmp = (size_t)(m->v[0] * m->v[1]) * sizeof(double);

        printf("n_jmp = %zu\n", gpumodel->n_jmp); ///
        gpumodel->f_jmp = gpumodel->n_jmp + ((uint)((m->n[0] + 1) * m->n[1]) * sizeof(double)); /// Normals.
        ///gpumodel->f_jmp = gpumodel->n_jmp; /// No Normals.

        /** Maybe here **/
        face_buf_sz = f_buffer_size(m->f);

        printf("Vec Seg Size: [%u]\n", (uint)((m->v[0] + 1) * m->v[1]));
        /*** CRASH vec4 ***/
        /*** ???? ***/
        printf("Pointers : [%p] [%p]\n", gpumodel, m->v);
        //return (1);
        if ((cpyret = memcpy(
            (void *)((void *)gpumodel + sizeof(struct s_gpu_model)),
            (const void *)m->v, gpumodel->n_jmp)) == NULL)
                return (1);
        printf("Max value [%zu]\n", gpumodel->n_jmp - 2069);///
        //return (1);
        /*** CRASH ***/
        //return (1); /// DEBUG///////////////////////////

        printf("nvertices = [%f]\n", *((double *)(&gpumodel->active + 4)) );
        if (memcpy((void *)((void *)gpumodel + sizeof(struct s_gpu_model) + gpumodel->n_jmp),
               (const void *)m->n,
               (size_t)(gpumodel->nn * sizeof(double))) == NULL)
               return (1);
        printf("nnormals = [%f]\n", *((double *)(&gpumodel->active + 4 + gpumodel->n_jmp)) );
        if (memcpy((void *)((void *)gpumodel + sizeof(struct s_gpu_model) + gpumodel->f_jmp),
               (const void *)m->f,
                face_buf_sz /*(size_t)(gpumodel->nf * sizeof(int))*/) == NULL)
                return (1);
        /** // Original no copy ???
        memccpy((void *)(&gpumodel->active + 1), (const void *)m->v,
                (int)gpumodel->n_jmp,
                sizeof(char));
        memccpy((void *)(&gpumodel->active + 1 + gpumodel->n_jmp), (const void *)m->n,
                (int)(gpumodel->f_jmp - gpumodel->n_jmp),
                sizeof(char));
        memccpy((void *)(&gpumodel->active + 1 + (gpumodel->f_jmp * sizeof(double))), (const void *)m->f,
                face_buf_sz,
                sizeof(char));
        **/
        /** Maybe here **/

        if (++mdl >= MAX_MODEL)
        {
            FREE(host_model_buffer);
            return (1);
        }
        if (d->model[mdl].active == 0)
            gpumodel->next_model = 0;
        else
            gpumodel->next_model = sizeof(struct s_gpu_model) + gpumodel->f_jmp + face_buf_sz;
        gpumodel = (t_gpu_model *)(((char *)gpumodel) + gpumodel->next_model);
    }
    cl->model_buf = host_model_buffer;
    cl->model_bufsz = total_size;
    return (0);
}

void                *alloc_triangle_auxmem(uint ntriangle, size_t *bufsz)
{
    size_t      total_size;

    total_size = sizeof(struct s_srf) * ntriangle;
    if (bufsz)
    {
        *bufsz = total_size;
        DEBUG
    }
    return (ALLOC(total_size));
}

size_t              triangle_buffer_size(int *f, uint vecsize)
{
    size_t          a;
    size_t          jmp;

    if (!f)
        return (0);
    a = 0;
    while (*f != 0)
    {
        jmp = *f + 1;
        a += jmp - 2;
        f += jmp;
    }
    ///return (sizeof(struct s_point) * a);
    return ((sizeof(struct s_point) * vecsize) * a);
}

int                 push_triangle_opencl(t_opencl *cl, t_camdata *d)
{
    uint        vecsize;
    int         mdl;
    t_model     *m;

    if (!cl || !d)
        return (1);

    /*** Count ***/
    size_t total_size;
    mdl = 0;
    total_size = sizeof(struct s_point);
    while (d->model[mdl].active == 1)
    {
        m = &d->model[mdl];
        vecsize = m->v[1];
        total_size += triangle_buffer_size(m->f, vecsize); /// Face Buf
        if (++mdl >= MAX_MODEL)
            return (1);
    }
    /*** Alloc ***/
    void            *host_triangle_buffer;

    /***total_size += sizeof(size_t);***/
    if (!(host_triangle_buffer = ALLOC(total_size)))
        return (1);
    /*** Bake ***/
    uint            count_vertices;
    int             *fce;
    uint            flen;
    uint            j;
    uint            i;
    double         *gputriangle;
    gputriangle = ((double *)host_triangle_buffer);

    gputriangle += 4;
    count_vertices = 0;
    mdl = 0;
    while (d->model[mdl].active == 1)
    {
        m = &d->model[mdl];
        vecsize = m->v[1];
        fce = m->f;
        ///i = -1; // Keep?
        i = 0;
        while (i < m->nf)
        {
            flen = fce[0];
            j = 2;
            while (j < flen)
            {
                ///get_v3(m->v, fce[1], gputriangle, m->_translate, m->_rotate, m->_scale);
                copy_v3(&m->v[fce[1] * vecsize], gputriangle);
                #ifdef DEBUG_TRIANGLE
                    printf("[%f] [%f] [%f]", *gputriangle, *(gputriangle + 1), *(gputriangle + 2)); //
                #endif
                gputriangle += 4;
                ///get_v3(m->v, fce[j], gputriangle, m->_translate, m->_rotate, m->_scale);
                copy_v3(&m->v[fce[j] * vecsize], gputriangle);
                #ifdef DEBUG_TRIANGLE
                    printf(" <-> [%f] [%f] [%f]", *gputriangle, *(gputriangle + 1), *(gputriangle + 2)); //
                #endif
                gputriangle += 4;
                ///get_v3(m->v, fce[j + 1], gputriangle, m->_translate, m->_rotate, m->_scale);
                copy_v3(&m->v[fce[j + 1] * vecsize], gputriangle);
                #ifdef DEBUG_TRIANGLE
                    printf(" <-> [%f] [%f] [%f]", *gputriangle, *(gputriangle + 1), *(gputriangle + 2)); //
                #endif
                gputriangle += 4;
                count_vertices += 3;
                j++;
            }
            #ifdef DEBUG_TRIANGLE
                printf("\n"); //
            #endif
            fce += flen + 1;
            i++;
        }
        if (++mdl >= MAX_MODEL)
        {
            printf("MAX_MODEL Reached !!\n");///
            FREE(host_triangle_buffer);
            return (1);
        }
    }
    printf("Loaded vertices: %u\n", count_vertices);
    *((double *)host_triangle_buffer) = (double)count_vertices;
    if ( count_vertices > 0 && !( cl->surface_buf = alloc_triangle_auxmem(count_vertices / 3, NULL) ) )
    {
        FREE(host_triangle_buffer);
        return (1);
    }
    cl->surface_bufsz = count_vertices; // DEBUG
    cl->triangle_buf = host_triangle_buffer;
    cl->triangle_bufsz = total_size;
    return (0);
}
