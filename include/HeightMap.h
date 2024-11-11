/*
 * Auteur:
 * Theophile Trosseau
 *
 * Date de creation:
 * 21/04/2019
 *
 * Temps de travail:
 * aprox~ 48h
 *
*/

#ifndef HEIGHTMAP_H
    #define HEIGHTMAP_H

    #include "8ball.h"
    //#include <SDL/SDL_ttf.h>
    //#include "SDL_ttf.h"
    #define PI_2                  1.57079632679489
    #define PI                    3.14159265358979
    #define PI2                   6.28318530717958
    #define MIN_HEIGHT            0
    #define MOVE_HEIGHT           0.1
    #define MOVE_DIR              30
    #define DEFAULT_ZOOM          0.1

    #define WINDOW_W        1000//1280    //640
    #define WINDOW_H        750//960     //480

    #define DEFAULT_R       0
    #define DEFAULT_G       255
    #define DEFAULT_B       0
    #define DEFAULT_A       255

    #define DEFAULT_BTNBG_GRAY      175
    #define DEFAULT_BARBG_GRAY      195

    #define STRING_SIZE     255
    #define GRID_SIZE       150

    #define N_TOOLS                 3
    #define TOOL_SQUARE_DEL         0
    #define TOOL_SQUARE_ADD         1
    #define TOOL_SQUARE_ADD_GRAD    2

    #define EDIT_RADIUS     10
    #define EDIT_INTENSITY  5.0

    #define UPPER_BAR_N_PICTO           9

    #define N_BUTTON        32
    #define BUTTON_IDLE     0
    #define BUTTON_CLICK    1
    #define BUTTON_LOCK     2

    #define BUTTON_INACTIVE 0
    #define BUTTON_ACTIVE   1
    #define PTYPE_FT        0 // Maybe better use TOOL_* defines

    #define N_CURSOR        5
    #define N_COLOR_SCHEME  1

    #define RENDER_CLOUD        0
    #define RENDER_WIREFRAME    1
    #define RENDER_POLYGON      2
    #define DEBUG       printf("%s - %s : %u\n", __FILE__, __func__, __LINE__);

    typedef struct         s_list
    {
        struct s_list   *next;
        char            str[STRING_SIZE];
    }                      t_list;

    typedef struct         s_conf
    {
        int         offset[2];
        double       dim[2];
        double       f;
        double       height;
        int         pxsz;
        int         mouse_rad;
        int         mouse_int;
        int         edit_mod;
        int         color_scheme;
        int         render_type;
    }                      t_conf;

    typedef struct         s_grid
    {
        uint        sz;
        uint        x;
        uint        y;
        int         persp;
        double       *ptr;
        t_conf      *conf;
        SDL_Surface *mask; // Unused for now
    }                      t_grid;

    typedef struct         s_button
    {
        uchar           color[4];
        int             active;
        int             state;
        char            ptrtype;
        void            *arg;
        void            (*ft_ptr)(void *);

        SDL_Surface     *s;
        SDL_Surface     *picto;
    }                      t_button;

    typedef struct         s_toolset
    {
        char file[STRING_SIZE];
        int active;
        uchar *color;
        int state;
        char ptrtype;
        void *arg;
        void (*ft)(void *);
    }                      t_toolset;

    typedef struct         s_toolbar
    {
        uchar           color[4];
        SDL_Surface     *viewport;
        int             x;
        int             y;
        int             w;
        int             h;
        int             n;
        t_button        *btn[N_BUTTON];
    }                      t_toolbar;

    /* Utils */
    char            *dtoa(char *s, double n);

    /* Memory Access */
    int             set_color4(uchar *dst, uchar *src);
    void            fill_surface(SDL_Surface *s, uchar *color);

    /* Draw Pattern */
    void            square(SDL_Surface *s, int x, int y, int w, int h, uchar *rgb);
    void            circle(SDL_Surface *s, uchar *color, int x_centre, int y_centre, int r);
    void            plain_circle(SDL_Surface *viewport, uchar *color, int *org, int ray);
    void            ellipse(SDL_Surface *s, uchar *color, int ox, int oy, long a,long b);
    void            rotate_pt(double **M, double **O, double angle);
    void            perspective(t_grid *grid, t_conf *conf, SDL_Surface *viewport, int *rx, int *ry, uint ix, uint iy, int height);

    /* Import / Export */
    void            export_dxf(t_grid *data, t_conf *conf);
    t_list              *putlist(t_list *l, const char *str);
    void                free_list(t_list *l);

    /* Constructors */
    t_grid          *get_grid(const char *file, SDL_Surface **img);
    double           *get_heightmap(SDL_Surface *img);
    t_conf          *make_conf(void);
    t_toolbar       *make_toolbar(SDL_Surface *screen, int x, int y, int w, int h, uchar *color);

    /* Runtime Events */
    int        event_processing(t_grid *data, t_grid *mask, t_conf **config, SDL_Surface *editor, SDL_Surface *viewport, t_toolbar *up_bar, SDL_Cursor **cursor);

    /* Tools */
    void        btn_square_add(void *input);
    void            square_add(t_grid *data, int *click, Uint8 button, t_conf *conf);
    void        btn_square_del(void *input);
    void            square_del(t_grid *data, int *click, Uint8 button, t_conf *conf);
    void        btn_square_add_grad(void *input);
    void            square_add_grad(t_grid *data, int *click, Uint8 button, t_conf *conf);
    void        btn_render_cloud(void *input);
    void        btn_render_wireframe(void *input);
    void        btn_render_polygon(void *input);

    /* Mouse */
    int             init_cursor(SDL_Cursor **cursor);
    int                 on_surface(SDL_Surface *s, int *click);
    int                 on_area(int *click, int x, int y, int w, int h);
    int                 click_surface(SDL_Surface *s, int *click, int *cx, int *cy);
    int                 click_area(int *click, int *cx, int *cy, int x, int y, int w, int h);
    int                 mouse_input_processing(t_grid *data, SDL_Surface *editor, SDL_Surface *viewport, t_toolbar *upper_toolbar, t_conf **conf, SDL_Cursor **cursor);

    /* User Interface */
    int             init_toolbar(SDL_Surface *screen, int x, int y, int w, int h, uchar *color, t_toolbar **bar, t_toolset *ts);

    /*int                 add_button(t_toolbar *bar, uchar *color, int type, int x, int y, int w, int h, struct s_toolset tools);*/
    int                add_button(t_toolbar *bar, int x, int y, int w, int h, struct s_toolset tool);
    void                toolbar_input_processing(t_toolbar *bar, int *click, Uint8 button);

    /* Render */
    void            draw_background(SDL_Surface *bg);
    void            draw_viewport(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, uchar *color);
    /*void            draw_cloud(t_grid *g, t_conf *conf, SDL_Surface *viewport, uchar *color);*/
    void        draw_cloud(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, int i, int j);///
    void            draw_mask(t_grid *g, t_conf *conf, SDL_Surface *viewport, uchar *color);
    //void            draw_heightmap(t_grid *g, t_conf *conf, SDL_Surface *viewport, uchar *color);
    void            draw_heightmap(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, uchar *color); // Maybe rename heightmap -> editor
    void            draw_toolbar(t_toolbar *bar); // M8be add 'draw_ui'
    void            draw_button(t_button *b, int offset_x, int offset_y);

    void            color_scheme(uchar *color, int i, void *data);

#endif // HEIGHTMAP_H
