#include "export.h"

void         print_segment(t_model *m, uint seg_index)
{
    uint                i;
    uint                k;
    uint                vecsize;
    uint                adr;
    double              vector[3];
    double              *vptr;
    double              *nptr;
    int                 *fptr;

    /***
    printf("rot[%f][%f][%f] ; sca[%f][%f][%f] ; tra[%f][%f][%f]\n",
           m->_rotate[0],
           m->_rotate[1],
           m->_rotate[2],
           m->_scale[0],
           m->_scale[1],
           m->_scale[2],
           m->_translate[0],
           m->_translate[1],
           m->_translate[2]);
    ***/
    printf("============== SEGMENT ");
    if (!m || seg_index > 2)
        return ;
    i = -1;
    switch (seg_index)
    {
        case 0: {
                printf("VERTICE ==============\n");
                if (!(vptr = m->v))
                    return ;
                vecsize = (uint)vptr[1];
                printf("double v_segdump[%u] =\n{", ((uint)(vptr[0] + 1) * vecsize));
                while (++i < (uint)m->v[0] + 1)
                {
                    adr = i * vecsize;
                    printf("\n\t");
                    copy_v3(&vptr[adr], vector);
                    if (i != 0)
                        translate_vector(vector, m->_rotate, m->_scale, m->_translate);
                    k = -1;
                    while (++k < vecsize)
                    {
                        /**if (vptr[adr + k] == 0)
                            printf("0");
                        else**/
                        printf("%f", k < 3 ? vector[k] : vptr[adr + k]);
                        if (i != (uint)m->v[0] || k != vecsize - 1)
                            printf(",");
                    }
                }
                printf("\n");
                break;
            };
        case 1: {
                printf(" NORMAL ==============\n");
                if (!(nptr = m->n))
                    return ;
                vecsize = (uint)nptr[1];
                printf("double n_segdump[%u] =\n{", (uint)(nptr[0] + 1) * vecsize);
                while (++i < (uint)m->n[0] + 1)
                {
                    adr = i * vecsize;
                    k = -1;
                    printf("\n\t");
                    while (++k < vecsize)
                    {
                        if (nptr[adr + k] == 0.0)
                            printf("0.0");
                        else
                            printf("%f", nptr[adr + k]);
                        if (i != m->n[0] || k != vecsize - 1)
                            printf(",");
                    }
                }
                printf("\n");
                break;
            };
        case 2: {
                printf("   FACE ==============\n");
                if (!(fptr = m->f))
                    return ;
                //printf("int f_segdump[%u] =\n{", (f_buffer_size(fptr) / sizeof(int)) + 1 );
                while (++i < m->nf)
                {
                    vecsize = *fptr + 1;
                    k = -1;
                    printf("\n\t");
                    while (++k < vecsize)
                    {
                        printf("%d,", *(fptr++));
                        /**if (i != m->nf - 1 || k != vecsize - 1)
                            printf(",");**/
                    }
                }
                printf("\n\t0\n");
                break;
            };
    }
    printf("};\n");
    printf("=============================================\n");
}
