#include "user_interface.h"

static SDL_Cursor *init_system_cursor(const char *image[])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for ( row=0; row<32; ++row ) {
    for ( col=0; col<32; ++col ) {
      if ( col % 8 ) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[4+row][col]) {
        case 'X':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case '.':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
  return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}

int             ui_initCursor(t_userInterface *ui)
{
    uint            i;
    SDL_Cursor **cursor;

    if (!ui)
        return (1);
    cursor = ui->cursor;
    i = -1;
    while (++i < UI_CURSOR_COUNT) /** Clean Pointer Table **/
        ui->cursor[i] = NULL;
    if (!(cursor[UI_CURSOR_ARROW] = init_system_cursor(cursor_arrow)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[UI_CURSOR_CROSS] = init_system_cursor(cursor_cross)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[UI_CURSOR_ARROW_VRT] = init_system_cursor(cursor_arrow_VRT)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[UI_CURSOR_ARROW_HRZ] = init_system_cursor(cursor_arrow_HRZ)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    /// /////////////////////////////////
    if (!(cursor[UI_CURSOR_CORNER_UL] = init_system_cursor(cursor_arrow_cornA)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[UI_CURSOR_CORNER_UR] = init_system_cursor(cursor_arrow_cornB)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[UI_CURSOR_CORNER_DL] = init_system_cursor(cursor_arrow_cornC)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[UI_CURSOR_CORNER_DR] = init_system_cursor(cursor_arrow_cornD)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }

    /*if (!(cursor[2] = init_system_cursor(cursor_cross_shift)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[3] = init_system_cursor(dbg_cursor_arrow)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[4] = init_system_cursor(cursor_arrow_shift)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }*/
    SDL_SetCursor(cursor[UI_CURSOR_ARROW]);
    return (0);
}
