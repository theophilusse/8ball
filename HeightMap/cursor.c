#include "HeightMap.h"

static const char *cursor_arrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "X                               ",
  "XX                              ",
  "X.X                             ",
  "X..X                            ",
  "X...X                           ",
  "X....X                          ",
  "X.....X                         ",
  "X......X                        ",
  "X.......X                       ",
  "X........X                      ",
  "X.....XXXXX                     ",
  "X..X..X                         ",
  "X.X X..X                        ",
  "XX  X..X                        ",
  "X    X..X                       ",
  "     X..X                       ",
  "      X..X                      ",
  "      X..X                      ",
  "       XX                       ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

/* XPM */
static const char *cursor_cross[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "        X                       ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  " XXXXXX X XXXXXX                ",
  "X......X X......X               ",
  " XXXXXX X XXXXXX                ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  "       X.X                      ",
  "        X                       ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

/* XPM */
static const char *cursor_cross_shift[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                       X        ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                XXXXXX X XXXXXX ",
  "               X......X X......X",
  "                XXXXXX X XXXXXX ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                      X.X       ",
  "                       X        ",
  "0,0"
};

static const char *dbg_cursor_arrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ff0000",
  "  c None",
  /* pixels */
  "X                               ",
  "XX                              ",
  "X.X                             ",
  "X..X                            ",
  "X...X                           ",
  "X....X                          ",
  "X.....X                         ",
  "X......X                        ",
  "X.......X                       ",
  "X........X                      ",
  "X.....XXXXX                     ",
  "X..X..X                         ",
  "X.X X..X                        ",
  "XX  X..X                        ",
  "X    X..X                       ",
  "     X..X                       ",
  "      X..X                      ",
  "      X..X                      ",
  "       XX        ..             ",
  "                .XX.            ",
  "               .XXXX.           ",
  "               .XXXX.           ",
  "               .XXXX.           ",
  "                .XX.            ",
  "                .XX.            ",
  "                 ..             ",
  "                .XX.            ",
  "                .XX.            ",
  "                 ..             ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

static const char *cursor_arrow_shift[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "        X                       ",
  "        XX                      ",
  "        X.X                     ",
  "        X..X                    ",
  "        X...X                   ",
  "        X....X                  ",
  "        X.....X                 ",
  "        X......X                ",
  "        X.......X               ",
  "        X........X              ",
  "        X.....XXXXX             ",
  "        X..X..X                 ",
  "        X.X X..X                ",
  "        XX  X..X                ",
  "        X    X..X               ",
  "             X..X               ",
  "              X..X              ",
  "              X..X              ",
  "               XX               ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

SDL_Cursor *init_system_cursor(const char *image[])
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

int             init_cursor(SDL_Cursor **cursor)
{
    if (!cursor)
        return (1);
    if (!(cursor[0] = init_system_cursor(cursor_arrow)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[1] = init_system_cursor(cursor_cross)))
    {
        printf("Can't load mouse cursor\n");
        return (1);
    }
    if (!(cursor[2] = init_system_cursor(cursor_cross_shift)))
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
    }
    SDL_SetCursor(cursor[0]);
    return (0);
}
*/
