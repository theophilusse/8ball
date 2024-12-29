#ifndef STRUCTURES_H
#define STRUCTURES_H

    #include "8ball.h"

    /**
    typedef struct          s_vertice_dist
    {
        double dist2d; /// Unused ?
        double dist3d;
        int     coord[2];
        double base[3];
        double cache[3];
        double *vertice;
    }                       t_vertice_dist;

    typedef struct          s_vselection
    {
        int                   model_index;
        uint                  vertice_index;
        struct s_vertice_dist select;
        struct s_vselection *next;
    }                       t_vselection;
    */

    /// /////////////////////

    /*** Containers ***/

    typedef struct s_scanline
    {
        int range[2];
        int pos;
        int w;
    }               t_scanline;

    typedef struct s_mtx_12
    {
        char type;
        double a;
        double b;
    }               t_mtx_12;

    typedef struct s_mtx_13
    {
        char type;
        double a;
        double b;
        double c;
    }               t_mtx_13;


    typedef struct s_mtx_22
    {
        char type;
        double a;
        double b;
        double c;
        double d;
    }               t_mtx_22;

    typedef struct s_mtx_33
    {
        char type;
        double a;
        double b;
        double c;
        double d;
        double e;
        double f;
        double g;
        double h;
        double i;
    }               t_mtx_33;

    /*** Containers's edge ***/

    typedef struct         s_multitype
    {
        void        *pv;
        char        *ps;
        int         *pi;
        uint        *pu;
        float       *pf;
        double      *pd;
        char        c;
        int         i;
        uint        u;
        float       f;
        double      d;
    }                       t_multitype;

    /*** Abstract Structures ***/

    typedef struct s_ftData_parse
    {
        int                     n;
        int                     i;
        char                    sym[2];
        char                    *chunk[2];
    }               t_ftData_parse;

    typedef struct         s_list
    {
        struct s_list   *next;
        char            str[STRING_SIZE];
    }                      t_list;

    typedef struct      				s_cache /** CACHE **/
    {
        double 						base[3];
        double 						cache[3];
    }                   				t_cache;

    typedef struct          			s_select_vertice /** VERTICE **/
    {
		double     					*ptr;
        double     					coord[2];
        char     					model; /// Opt
    }                       			t_select_vertice;

    typedef struct 						s_select_index /** INDEX **/
    {
        uint 						model;
        uint 						n;
    }									t_select_index;

    typedef struct 						s_select_node /** SELECTION **/
    {
        struct s_select_node 		*next;
        struct s_select_index 		index;
        struct s_select_vertice		vrt;
        struct s_cache              mem;
        double                      payload;

    }									t_select_node;
    /// /////////////////////

    typedef struct s_hud_arrow
    {
        /*double          pta[3];
        double          ptb[3];
        double          ptc[3];*/
        double          factor;
        double          max_adj;
    }               t_hud_arrow;

    typedef struct s_hud_angle
    {
        /*double          pta[3];
        double          ptb[3];
        double          ptc[3];*/
        /*double           oppositeAxis[2];*/
        double           ringRayLength;
        double           degrees;
        /*double              axis[3];*/
    }               t_hud_angle;

    typedef struct s_hud_length
    {
        char           side; /// On-Click length.
        double         onClick; /// On-Click length.
        double         factor;
    }               t_hud_length;


    /******** ********/
    typedef struct          s_point
    {
        double           x;
        double           y;
        double           z;
        double           w;
    }                       t_point;

    typedef struct          s_gpu_triangle
    {
        struct s_point   vertices[3];
    }                       s_gpu_triangle;
    /******** ********/

    typedef struct          s_triangle
    {
        double           v0[3];
        double           v1[3];
        double           v2[3];
        double           u[3];
        double           v[3];
        double           n[3];
    }                       t_triangle;

    typedef struct          s_ray
    {
        double           origine[3];
        double           direction[3];
    }                       t_ray;

    typedef struct s_proj
    {
        double      dist;
        double      *ptr; ///
        int         coord[2];
    }              t_proj;

    typedef struct s_objMesh
    {
        double      *v;
        double      *n;
        int         *f;
    }              t_objMesh;

    typedef struct          s_model
    {
        uchar         active;
        uint          id;
        t_proj        *proj;
        double        _translate[3];
        double        _rotate[3];
        double        _scale[3];
        uchar         _ambiant_color[3];
        int          nv;
        int          nn;
        int          nf;
        double        *v;
        double        *n;
        int           *f;
    }                       t_model;

    typedef struct          s_gpu_model
    {
        double        _translate[4];
        double        _rotate[4];
        double        _scale[4];
        /** 27 Octets qui sortent du néan **/
        /*uchar           debug[27];*/
        uchar         _ambiant_color[4];
        int          nv;
        int          nn;
        int          nf;
        size_t 		 next_model; // offset
        /*size_t          v_jmp; // == 0*/
        size_t          n_jmp;
        size_t          f_jmp;
        uchar         active;
        /**uchar           vnf; /// Vertice's Buffer Start Here (followed by NormalBuf and FaceBuf)**/
    }                       t_gpu_model;
			/**
			typedef struct          s_model
			{
				double4        _translate;
				double4        _rotate;
				double4        _scale;
				uchar4        _ambiant_color;
				int          nv;
				int          nn;
				int          nf;
				size_t 		 next_model;
				size_t          v_jmp; // == 0
				size_t          n_jmp;
				size_t          f_jmp;
				uchar         active;
				//uchar		 	vnf; // Vertice's Buffer Start Here (followed by NormalBuf and FaceBuf)
			}                       t_model;
			**/

    typedef struct          s_camdata
    {
        void           *helloworld;
        uint           helloworld_size;
        double         verticesDist[2]; /// For color formula
        double         *zbuffer; // <-- cl_mem Input
        SDL_Surface    *backbuffer; // <-- cl_mem Output
        struct s_model  model[MAX_MODEL];
    }                       t_camdata;

    typedef struct          s_cam
    {
        double      o[4];
        double      pyr[4]; // Absolute Orientation Pitch-Yaw-Roll
        double      ud[4]; // Focal To Lens (focal_distance * direction)
        double      x[4];  // Absolute X (aka struct s_point)
        double      y[4];  // Absolute Y
        double      z[4];  // Absolute Z
        double      ux[4]; // Relative X (aka struct s_point)
        double      uy[4]; // Relative Y
        double      uz[4]; // Relative Z (direction)
        double      h; // Frustum Dimensions
        double      w;
        double      hh; // Precalc Frustum / 2
        double      hw;
        double      unit_w;
        double      unit_h;
        double      focal_distance;
        uint        vw;
        uint        vh;
        t_camdata      *data;
    }                       t_cam;

    typedef struct s_clinfo
    {
        cl_device_type     device_type;
        cl_uint            max_compute_units;
        cl_uint            dimensions;
        size_t             dimension_size[8];
        size_t             max_work_group_size;
        cl_ulong           global_mem_size;
        cl_ulong           constant_buffer_size;
        cl_ulong           local_mem_size;

    }               t_clinfo;

    typedef struct          s_option
    {
        double      picdiv[2];
        double      scale_factor;
        uint 		pixels_range[2];
        uint        mod_definition;
		uint 		display_model;
		uint 		display_cloud;
		uint 		occlusion;
		uint 		edit_mode;
		uint 		display_log;
		uint        max_model;
		uint        point_gravity;

		uint 		set_cloud;
		uint 		inc;

		uchar morpho_active; /// Opt. (opti?)
    }                       t_option;

    typedef struct s_opencl
    {
        uchar           sig_refresh_model;
        /* OpenCL structures */
        cl_device_id device;
        cl_context context;
        cl_program program;
        cl_program program_cloud_fall; //
        cl_kernel kernel;
        cl_kernel kernel_cloud_fall; //
        cl_command_queue queue;
        struct s_clinfo     info;
        size_t local_size, global_size;
        size_t num_groups;

        size_t work_dim;
        size_t global_work_size[3];
        size_t local_work_size[3];

        /* Data and buffers */
        struct s_option     option;

        uint         pixels_bufsz;

        size_t        picture_bufsz;
        void        *picture_buf;
        size_t         model_bufsz;
        void        *model_buf;
        size_t        cloud_bufsz;
        void        *cloud_buf;
        size_t         triangle_bufsz;
        void        *triangle_buf;
        size_t          zbuffer_bufsz;
        void        *surface_buf;
        size_t          surface_bufsz;

        cl_mem input_triangle;
        cl_mem input_model;
        cl_mem input_camera,
                input_lights,
                input_picture,
                input_option,
                input_cloud;
        cl_mem output_zbuffer,
               output_pixels,
               output_surface,
               output_cloud;
    }               t_opencl;

    typedef struct 		s_srf
    {
        /**/
        // Rectangle
        struct s_triangle T;
        double		dpp[2]; // X/Y Depth Per-Pixel
        double 		alen[2];
        double 		blen[2];
        double 		clen[2];
        double 		vdmin;
        uint		shift[2]; // X/Y Offset
        int 		pos[2];
        int 		dim[2];
        int		ptxa[2]; // Sorted Horizontally
        int		ptxb[2];
        int		ptxc[2];
        int		ptya[2]; // Sorted Vertically
        int		ptyb[2];
        int		ptyc[2];
        int			xmin;
        int 		xmax;
        int 		ymin;
        int 		ymax;
        int npix;
        /**/
    }					t_srf;

    /*** ***/
    typedef struct s_ref
    {
        double 		vec[4];
        double 		coord[2];
    }				t_ref;

    typedef struct s_axis
    {
        double 			x[4];
        double 			y[4];
        double 			z[4];
        double 			w[4];
    }				t_axis;

    typedef struct s_persp /// New
    {
        double 			x[2];
        double 			y[2];
        double 			z[2];
        double 			w[2];
    }				t_persp;

    typedef struct s_hud_data
    {
        int			(*mouse_motion)(void *, int); 	/// Mouse motion parametrization.
        char 		buf[256];									/// Data returned by mouse_motion call.
    }				t_hud_data;

    typedef struct s_hud 				    /// Generic HUD
    {									    /// ///
        char 				type; 		    /// Define specific datastruct.
        char 				active; 	    /// HUD's current state.
        int                 select_index;   /// 'arrow' index
        struct s_ref		org; 		    /// Origin
        struct s_axis	    axis; 		    /// Arrows
        struct s_persp		persp; 		    /// On-Screen projection.
        struct s_hud_data	data; 		    /// Specific HUD
    }				t_hud;
    /*** ***/

    typedef struct      s_mouse
    {
        double         drag_ac[3];
        int     motion_ft; /// Function index at mouse motion event to execute.
        int draw_marker;
        int mouseButtonUp;
        int leftButton;
        /// Radius HUD
        double cacheLengthClick;
        double cacheUnitClick[2];
        int cacheClick[2];
        /// Radius HUD
        int onClick[2];
        int mouseDrag[2];
        int mousePos[2];
        int mouseRle[2];
        uint MouseSensitiv;
        uchar skipDrag;
    }                   t_mouse;

    typedef struct          s_tool
    {
        int                     type;
        /**
         - projective
         - HUD
        **/
        char                    name[32]; /** Tool Name **/
        /** Data **/
        int                     refreshOrigin;
        struct s_hud            hud;

        int (*proceed)(void *, int); // Tool function pointer
    }                       t_tool;

    /***********  History ************/
    typedef struct s_history_param
    {
        uchar           _c_u;
        char            _c_s;
        uint            _d_u;
        int             _d_s;
        float           _f32;
        double          _f64;
        double          vec[3];
        char            buf[STRING_SIZE];
        uint            n;
        size_t          _sz;
        void            *ptr;
        struct s_select_node      *selection;
        struct s_select_vertice   vrt;
        uchar                   type; /// 0: Idle ; 1-9: Selection
    }               s_history_param;

    typedef struct s_history
    {
        struct s_history        *undo; /// Prev
        struct s_history        *redo; /// Next
        struct s_history_param  param;
    }               t_history;
    /*********************************/

    /***********  MORPHO  ************/
    #define MORPHO_PARTS_NUM        48
    /***typedef struct s_morpho_node
    {
        struct s_morpho_node *parent;
        struct s_morpho_node *child[8];
        uint            groupId;
        uint            pos[2];
        SDL_Surface     *surface;
        char            name[32];
    }               t_morpho_node;**/

    typedef struct s_morpho_group
    {
        SDL_Surface         *surf;
        uchar               active;
        uint                pos[2];
        uint                dim[2];
        uchar               color[4];
        char                name[32];
    }               t_morpho_group;

    typedef struct s_morpho
    {
        SDL_Surface             *surface;
        uchar                   active;
        uint                    pos[2];
        struct s_morpho_group   part[MORPHO_PARTS_NUM];
        ///t_morpho_node   *root;
    }               t_morpho;
    /*********************************/

    /*************  User Interface  **********/

    typedef struct 	s_ui_font
    {
        /** charset : Must be squares **/
        SDL_Surface 	**charset;
    /*	SDL_Surface 	**highlight;*/
        /** Colors **/
        uchar 		fgColor[4];
        uchar 		bgColor[4];
        uchar 		fgColor_bis[4];
        uchar 		bgColor_bis[4];
        /** Dimensions **/
        uint 		dim;
    }		        t_ui_font;

    typedef struct s_item_status /** STATUS SWITCHES **/
    {
        char        active;
        float       factor;// 0.0-1.0 for scrolls ?
        uchar       param[4];
    }               t_item_status;

    typedef struct s_simple_button
    {
        char                txt[24];
        SDL_Surface         *srf;
        int                 (*fptr)(void *, int);
    }               t_simple_button;

    typedef struct s_ui_function
    {
        int    (*idx[4])(void *, uchar, int *, uint *);
        ///int    (*idx[4])(void);
    }               t_ui_function;

    typedef struct s_box_item /** ITEMS SUCH AS BUTTONS **/
    {
        int         pos[2];
        uint        dim[2];
        uchar           type;
        uint            dataSize;
        size_t          blockSize;
        void            *ptr;
        struct s_ui_function    ft;
        struct s_item_status    status;
    }               t_box_item;

    typedef struct s_box_content /** ALL ELEMENTS **/
    {
        uchar                   type;
        uchar                   color[4];
        uchar                   n_item;
        struct s_box_item       item[UI_BOX_CONTENT_MAX_ITEM]; /// UI_BOX_CONTENT_MAX_ITEM
    }               t_box_content;

    typedef struct s_ui_scrollbar
    {
        uchar       axis; /// 0 Horizontal ; 1 Vertical
        int         shift;
        uint        length;
        float       fPercent;
    }               t_ui_scrollbar;

    typedef struct s_ftData_zone
    {
        int         minDim[2];
        int         maxDim[2];
        int         pos[2];
        int         dim[2];
    }              t_ftData_zone;

    /************************************************************/
    typedef struct      s_ftData_range
    {
        int     from;
        int     to;
    }                   t_ftData_range;

    typedef struct      s_ftData_textMethod
    {
        int                     display;
        char                    dyn;
        struct s_ftData_range   sel;
        struct s_ftData_zone    zone;
    }                   t_ftData_textMethod;

    typedef struct      s_ftData_gTextData
    {
        SDL_Surface                 *surf;
        struct s_ui_font            font;
        struct s_ftData_textMethod  dsp;
    }                   t_ftData_gTextData;
    /************************************************************/

    typedef struct s_ui_box /** ZONE **/
    {
        uchar       active;
        /*uchar       z_index;*/
        uint        dim[2];
        uint        envDim[2];
        int         pos[2];
        t_box_content           *content;
        SDL_Surface             *viewport;
        t_ui_font               *font;
        struct s_ui_scrollbar    horizontal_bar;
        struct s_ui_scrollbar    vertical_bar;
        char        title[UI_BOX_TITLE_STRLEN]; /// UI_BOX_TITLE_STRLEN
    }               t_ui_box;
    /*****************************************/

    typedef struct s_ui_event
    {
        uchar type; /// 0 = NONE ; 1 = KILLBOX ; 2 = BARGRAB ;
                    /// 3 = LEFT_EDGE ; 4 = RIGHT_EDGE ; 5 = UPPER_EDGE ; 6 = LOWER_EDGE
                    /// 7 = UPPER_LEFT_CORNER ; 8 = UPPER_RIGHT_CORNER ; 9 = LOWER_LEFT_CORNER ; 10 = LOWER_RIGHT_CORNER
        uchar flag;
        uchar handle;
        uchar itemHandle;
        int             pIndex[2];
        void *ptr;
    }               t_ui_event;

    typedef struct      s_ui_assets
    {
        SDL_Surface         *azerty;
        SDL_Surface         *nagscreen;
        SDL_Surface         *spKill;
        SDL_Surface         *grid;
        SDL_Surface         *scroller;
        SDL_Surface         *button_on;
        SDL_Surface         *button_off;
        SDL_Surface         *cross;
        SDL_Surface         *arrow_u;
        SDL_Surface         *arrow_d;
        SDL_Surface         *arrow_l;
        SDL_Surface         *arrow_r;
        SDL_Surface         *fall;
        SDL_Surface         *save;
        SDL_Surface         *bye;
    }                   t_ui_assets;


    /*********************/
    /**
        #define DATATYPE_FILTR_TABLE_LENGTH         6
        #define DATATYPE_FUNCT_TABLE_LENGTH         4
        #define DATATYPE_PTYPE_TABLE_LENGTH         4
    **/
    /*********************/
    typedef struct s_userInterface
    {
        uchar       active;
        uchar       sigFrame;
        uchar       sigRefresh;
        uint        boxCount;
        struct s_ui_event          event;
        struct s_morpho            morpho;
        struct s_ui_box            box[UI_BOX_COUNT]; /// UI_BOX_COUNT
        struct s_ui_font           font;
        struct s_ui_font           font_bis;
        struct s_ui_assets         assets;
        SDL_Cursor                 *cursor[UI_CURSOR_COUNT];
        /// No constructor !
        /**
            int                        (*filtr[DATATYPE_FILTR_TABLE_LENGTH])(void *, void *, void *, uchar type); ///
            int                        (*funct[DATATYPE_FUNCT_TABLE_LENGTH])(void); ///
            int                        (*dtype[DATATYPE_DTYPE_TABLE_LENGTH])(void); ///
        **/
    }              t_userInterface;

    typedef struct  s_multithread_item
    {
        uchar           index;
        pthread_t       thread;
        void            *shared;
        void            *local;
        void            *global;
    }               t_multithread_item;

    typedef struct  s_multithread
    {
        void                            *(*fTask)(void *); // Multithread function pointer
        void                            *(*fDisp)(void *); // Display loading bar
        struct  s_multithread_item      item[THREAD_COUNT + 1];
        uint                            local_data[THREAD_COUNT];
        uint                            global;
        /** pthread_attr_t  attribute; **/
    }               t_multithread;


    typedef struct      s_sceneNode
    {
        /*uint                    stack_size;*/
        struct s_sceneNode     *stk;
        struct s_sceneNode     *parent;
        size_t                  datSz;
        void                    *data;
    }                   t_sceneNode;

    /*
        typedef struct s_mem_core;
        typedef struct s_mem_core;
    */
    /** typedef struct s_mem_core; **/

    /**
      * Global variables struct.
    **/
    typedef struct s_globalVars
    {
        char                    mouseCaption[STRING_SIZE];
        const SDL_VideoInfo     *videoInfo;
        HWND                    window;
        char                    *wTitle;
        void                    *corePage;
    }               t_globalVars;

    /**
     ** Mega structure containing pointers of all allocated data
     **
    **/
    typedef struct s_mega
    {
        SDL_Surface *screen;
        SDL_Surface *viewport;
        SDL_Surface *hud_viewport;
        SDL_Surface *log_viewport;
        SDL_Surface *ui_viewport;
        SDL_Surface *direct_viewport;
        SDL_Surface *viewport_swp;
        SDL_Surface *work_viewport;
        SDL_Surface *picture;
        /*SDL_Surface **tileset;*/
        void *helloworld;
        uint helloworld_size;
        t_cam *camera;
        t_opencl *stcl;
        SDL_Event event;
        int (**input_manager)(struct s_mega *, int);
        struct s_tool (**toolset_builder)(struct s_mega *, int *);
        double          sun[3];
        /**  UI   **/
        /*struct s_hud_angle  hud_angle;
        struct s_hud_arrow  hud_arrow;*/
        struct s_hud           hud;
        struct s_select_node   *selectStack;

        int                 currentTool;
        int                 currentObject;
        struct s_tool       tool[TOOLSET_SIZE];
        /**       **/

        /** KEYBOARD **/
        int             keyboardUp;
        /**       **/

        /** MOUSE **/
        struct s_mouse  mouse;
        t_globalVars    *global;
        /*
        double                  drag_v[3];  /// Obsolete
        double                  drag_va[3]; /// Obsolete
        */
        //double                  axis[3];
        /*double                  axis_hud_absdot;
        double                  axis_hud_reldot;
        double                   dragFactorScale;
        double                  dragFactor;
        double                  dragLength;
        double                  dragSum[3];
        double                  dragSumLength;*/ /// mouse_motion* funcitons
        /**       **/

        /**     UI      **/
        t_userInterface      *ui;
        /**             **/
        /**     History **/
        t_history       *timeMachine;
        /**             **/

        struct s_multithread        thread;
    }              t_mega;

#endif // STRUCTURES_H
