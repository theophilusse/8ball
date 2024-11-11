///#include "camera.h"
#include "frame.h"

int            frame(t_mega *mega, int flg, int save_work_viewport)
{
    int                 err;
    struct s_tool       tool;

    DEBUG ///
    ///blit(mega.viewport, mega.viewport_swp); /// Test (see input_manager -> mouse motion)
    ///blit(mega.viewport_swp, mega.viewport); /// Test (see input_manager -> mouse motion)
    clean_surface(mega->viewport); /// KEEP
    /*clean_surface(mega.ui_viewport);*/
    clean_surface(mega->work_viewport);
    /** Refresh s_cam**/
    // Original
    if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->input_camera,
                                    CL_TRUE, 0,  sizeof(struct s_cam) - sizeof(t_camdata *), mega->camera, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1 error:[%d]\n", err);
        return (1);
    }
    DEBUG ///
    mega->stcl->option.morpho_active = mega->ui->morpho.active;
    if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->input_option,
                                    CL_TRUE, 0, sizeof(struct s_option), &mega->stcl->option, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 8 error:[%d]\n", err);
        return (1);
    }
    DEBUG ///
    /******** SGFAULT ********/
    //if ((err = clEnqueueWriteBuffer(cl->queue, cl->input_cloud,
    //if ((err = clEnqueueWriteBuffer(cl->queue, cl->output_cloud,
    //                                CL_TRUE, 0, cl->cloud_bufsz, &cl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->output_cloud,
                                    CL_TRUE, 0, mega->stcl->cloud_bufsz, mega->stcl->cloud_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write cloud buffer error:[%d]\n", err);
        return (1);
    }
    DEBUG ///
    /**
    err = (int)clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->work_dim,
                                        NULL, cl->global_work_size, NULL,
                                        0, NULL, NULL);
    **/
    err = (int)clEnqueueNDRangeKernel(mega->stcl->queue, mega->stcl->kernel, mega->stcl->work_dim,
                                        NULL, mega->stcl->global_work_size, mega->stcl->local_work_size,
                                        0, NULL, NULL);
    DEBUG ///
    if (err != CL_SUCCESS)
    {
        printf("clEnqueueNDRangeKernel ERROR [%d]\n", err);
        return (1);
    }
    DEBUG ///
    if ((err = clEnqueueReadBuffer(mega->stcl->queue, mega->stcl->output_pixels, CL_TRUE, 0,
                                   mega->stcl->pixels_bufsz, mega->camera->data->backbuffer->pixels, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("clEnqueueReadBuffer (bbuf) ERROR [%d]\n", err);
        return (1);
    }
    DEBUG ///

    ///printf("Zbuffer BUFSZ : [%u]\n", cl->zbuffer_bufsz); ///
    ///if (mega.stcl->option.edit_mode != 0) /// DBGZBUFFER TEST
    if ((err = clEnqueueReadBuffer(mega->stcl->queue, mega->stcl->output_zbuffer, CL_TRUE, 0,
                                   mega->stcl->zbuffer_bufsz, (void *)mega->camera->data->zbuffer, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("clEnqueueReadBuffer (zbuf) ERROR [%d]\n", err);
        return (1);
    }
    DEBUG ///
    if (mega->stcl->option.point_gravity == 1)
        mega->stcl->option.point_gravity = 0;
    ///blit_at(mega.camera->data->backbuffer, mega.viewport, 0, 0); /// REMOVE

    tool = mega->tool[mega->currentTool];
    if (mega->stcl->option.edit_mode == 1) // Show vertices, selection and HUD
    {
        draw_hud_screen(mega->hud_viewport, mega, tool);
    }
    DEBUG ///
    if (mega->stcl->option.display_log == 1) // Not HUD, it's debug
    {
        clean_surface(mega->log_viewport);
        /** Print Current Tool. **/
        ///charset_print(mega.viewport, mega.charset_bis, 50, 50, mega.tool[mega.tool].name); // Print Current Tool.
        print_debug(mega->log_viewport, mega->camera, mega->ui->font.charset, mega->ui->font_bis.charset, 0, 0);
        ui_drawCameraOrientation(mega->log_viewport, mega->camera, mega->viewport->w, mega->viewport->h, mega->ui->font.charset);
    }
    DEBUG ///
    if (mega->ui->active == 1) /** USER INTERFACE **/
    {
        ui_main(mega, mega->ui);
        /*
        if (save_work_viewport == 1)
            blit_mergeAlpha(mega.viewport, mega.work_viewport);
        */
        ///blit_mergeAlpha(mega.ui_viewport, mega.viewport);
    }
    DEBUG ///
    super_blit(mega);
    DEBUG ///
    return (0);
}
