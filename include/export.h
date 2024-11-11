#ifndef EXPORT_H
    #define EXPORT_H

    #include "8ball.h"
    #include "user_interface.h"

    void        export_cloud_to_dxf(t_mega *mega, int nv);

    void        print_segment(t_model *m, uint seg_index); /*Export C*/

    void        print_c(int fd, const char *format, void *pointer, ...); /*Print data in C*/

    void        export_obj(t_cam *c, uint modelHandle, const char *filename);

#endif // EXPORT_H
