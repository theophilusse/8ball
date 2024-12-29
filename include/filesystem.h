#ifndef FILESYSTEM_H
    #define FILESYSTEM_H

    #include "8ball.h"

    #define OBJ_BASE_DIR        "OBJ\\"

    void    *fs_abort(int fd, void *toFree, void *ret);
    char    *fd_readClose(int fd, uint *buf_size);
    void    *fs_close(int fd, void *ret);
    int 	fs_touch(char *path);
    int     fs_read(char *path);
    int     fs_pipe(char *in_path, char *out_path, int *fd_in, int *fd_out);
    char    *fd_readClose(int fd, uint *buf_size);
    int     obj_comment(int fd, const char *comment);
    int     getValidFileName(char *buf, const char *filename, const char *extension);

#endif // FILESYSTEM_H
