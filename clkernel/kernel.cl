#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define DBL_EPSILON 0x1.0p-52

void 		reset_zbuffer(__global double *zbuffer, uint2 dim)
{
	uint npix;
	uint gnpix;
	uint addr;
	uint gaddr;
	uint k;
	uint 		global_addr;
	uint 		global_size;
	uint 		local_addr;
	uint 		local_size;
	uint 		group_addr;

	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);
	npix = dim.x * dim.y;
	gnpix = npix * 4;
	k = -1;
	while ( (addr = (++k * global_size) + global_addr) < npix )
	{
		gaddr = addr * 4;
		if (zbuffer[(gaddr + 3) % gnpix] == DBL_MAX)
			continue;
		zbuffer[gaddr % gnpix] = 0; // R
		zbuffer[(gaddr + 1) % gnpix] = 0; // G
		zbuffer[(gaddr + 2) % gnpix] = 0; // B
		zbuffer[(gaddr + 3) % gnpix] = DBL_MAX; // Z
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
}

void 		_debug_(__global double *zbuffer, double value)
{
	uint npix;
	uint debug;

	npix = 1500 * 750;
	debug = -1;
	while (++debug < npix * 4)
	// while (++debug < npix)
	//if (fmod((double)debug, (double)100) == 0)
	//if ((int)debug % 2 == 0)
	{
		/*if (zbuffer[debug * 4] == value)
			return ;*/
		//if (debug % 16 == 0)
		//zbuffer[debug] = 0; // R
		
		if (debug % 8 == 0)
			zbuffer[debug] = 255;
		else
			zbuffer[debug] = 0; // R
		/*
		zbuffer[debug * 4] = value; // R
		zbuffer[(debug * 4) + 1] = 0; // G
		zbuffer[(debug * 4) + 2] = 0; // B
		zbuffer[(debug * 4) + 3] = 0; // Z
		*/
	}
}

	///#define deg_to_rad(deg) (deg * 3.14159265358979 / 180)
	double 		deg_to_rad(double deg)
	{
		return (deg * 3.14159265358979 / 180);
	}
	///#define rad_to_deg(rad) (rad * 180 / 3.14159265358979)
	double 		rad_to_deg(double rad)
	{
		return (rad * 180 / 3.14159265358979);
	}

	///#define _length(v) (sqrt(fabs((v.x * v.x) + (v.y * v.y) + (v.z * v.z))))
	double 			_length(double4 v)
	{
		return (sqrt(fabs((v.x * v.x) + (v.y * v.y) + (v.z * v.z))));
	}
	///#define _length2(v) (sqrt(fabs((v[0] * v[0]) + (v[1] * v[1]))))
	double 			_length2(double2 v)
	{
		return (sqrt(fabs((v.x * v.x) + (v.y * v.y))));
	}

	///#define _dot(a, b) (a.x * b.x + a.y * b.y + a.z * b.z)
	double 			_dot(double4 a, double4 b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}
	///#define _dot2(a, b) ((a.x * b.x) + (a.y * b.y))
	double			_dot2(double2 a, double2 b)
	{
		return ((a.x * b.x) + (a.y * b.y));
	}

	///#define _min(a, b) ((a < b) ? a : b)
	int 			_min(int a, int b)
	{
		return ((a < b) ? a : b);
	}
	///#define _max(a, b) ((a > b) ? a : b)
	int 			_max(int a, int b)
	{
		return ((a > b) ? a : b);
	}

	double4 		_clamp(double4 x, double min, double max)
	{
		if (x.x < min)
			x.x = min;
		if (x.x > max)
			x.x = max;
		if (x.y < min)
			x.y = min;
		if (x.y > max)
			x.y = max;
		if (x.z < min)
			x.z = min;
		if (x.z > max)
			x.z = max;
		return (x);
	}

typedef struct 			s_ray
{
	double4 		org;
	double4 		dir;
}						t_ray;
	
typedef struct          s_triangle
{
    double4           v0;
    double4           v1;
    double4           v2;
    double4           u;
    double4           v;
    double4           n;
}                       t_triangle;

typedef struct 		t_backbuffer
{
	uint2 		dim;
	uint		pitch;
	uint		bpp;
	void 		*pixels;
}					s_backbuffer;

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
	size_t          n_jmp;
	size_t          f_jmp;
	uchar         active;
}                       t_model;

    typedef struct          s_cam
    {
        double4      o;
        double4      pyr; // Absolute Orientation Pitch-Yaw-Roll
        double4      ud; // Focal To Lens (focal_distance * direction)
        double4      x;  // Absolute X (aka struct s_point)
        double4      y;  // Absolute Y
        double4      z;  // Absolute Z
        double4      ux; // Relative X (aka struct s_point)
        double4      uy; // Relative Y
        double4      uz; // Relative Z (direction)
        double      h; // Frustum Dimensions
        double      w;
        double      hh; // Precalc Frustum / 2
        double      hw;
        double      unit_w;
        double      unit_h;
        double      focal_distance;
		uint2 		sdim; // Screen Dimensions
    }                       t_cam;
	
    typedef struct          s_option
    {
		double2 	picdiv;
		double 		scale_factor;
		uint2 		pixels_range;
		uint 		mod_definition;
		uint 		display_model;
		uint 		display_cloud;
		uint 		occlusion;
		uint 		edit_mode;
		uint 		display_log; /// Unused inside Kernel
		uint        max_model;
		uint 		point_gravity;
		
		uint 		set_cloud;
		uint 		inc;

		uchar morpho_active; /// Opt. (opti?)
    }                       t_option;

	typedef struct s_srf
	{
		double4 	color;
		double2		dpp;
		double4 	v0;
		double4 	v1;
		double4 	v2;
		double 		invDenom; // For Barycentric coordinates
		double 		vdmin;
	    float d00;
		float d01;
		float d11;
		float d20;
		float d21;
		float 		u;
		float 		v;
		float 		w;
		int2		dppo; // Corner point 
		int2 		dim;
		int2 		pos;
		int2		ptya; // Sorted Vertically
		int2		ptyb;
		int2		ptyc;
		int2		pt_bis;
		int 		npix;
		int s0;
		int s1;
		int s2;
		int s0isright;
		uchar type;
	}			t_srf;
	
	typedef struct olds_srf
	{
		double4 	color;
		double2		dpp;
		double2		dppo;
		double 		vdmin;
		int2 		dim;
		int2 		pos;
		int2		ptya; // Sorted Vertically
		int2		ptyb;
		int2		ptyc;
		int2		pt_bis;
		int 		npix;
		int s0;
		int s1;
		int s2;
		int s0isright;
		uchar type;
	}			oldt_srf;
	
	typedef struct s_sortsrf
	{
		__global struct s_srf		*p;
		int 		vdmin;
		///int 		npix; /// Optionnal
	}				t_sortsrf;
	
	/////////////////////////////
	
	double4           unit_vec(double4 v)
	{
		double 		l;

		l = _length(v);

		//if (l <= DBL_EPSILON || l == 0)
		/*if (l <= 1) // Dont do this
			return (v * l);*/
		return (v / l);
	}

	double2           unit_vec2(double2 v)
	{
		double 		l;

		l = _length2(v);
		/*if (l <= DBL_EPSILON || l == 0)
			return (1);*/
		return (v / l);
	}
	
	double4			rot_vec3(double4 axis, double a, double4 lev) /*** Debug this function ***/
	{
		double4			q;
		double				cosa;
		double				sina;

		cosa = (double)cos(a);
		sina = (double)sin(a);
		q.x = (cosa + (1 - cosa) * axis.x * axis.x) * lev.x;
		q.x += ((1 - cosa) * axis.x * axis.y - axis.z * sina) * lev.y;
		q.x += ((1 - cosa) * axis.x * axis.z + axis.y * sina) * lev.z;
		q.y = ((1 - cosa) * axis.x * axis.y + axis.z * sina) * lev.x;
		q.y += (cosa + (1 - cosa) * axis.y * axis.y) * lev.y;
		q.y += ((1 - cosa) * axis.y * axis.z - axis.x * sina) * lev.z;
		q.z = ((1 - cosa) * axis.x * axis.z - axis.y * sina) * lev.x;
		q.z += ((1 - cosa) * axis.y * axis.z + axis.x * sina) * lev.y;
		q.z += (cosa + (1 - cosa) * axis.z * axis.z) * lev.z;
		return (q);
	}
	
double4         get_v3(__global double *vertices, int i, double4 pos, double4 rotate, double4 scale)
	{
		int            	add;
		double4           x_axis;
		double4           y_axis;
		double4           z_axis;
		double4			 out;

		x_axis = (double4)(1,0,0,0); // Passer ca sur memoire __constant
		y_axis = (double4)(0,1,0,0); // Passer ca sur memoire __constant
		z_axis = (double4)(0,0,1,0); // Passer ca sur memoire __constant
		add = (vertices[1] * i);

		out.x = *(vertices + add);
		out.y = *(vertices + add + 1);
		out.z = *(vertices + add + 2);
		out.x *= scale.x;
		out.y *= scale.y;
		out.z *= scale.z;
		out = rot_vec3(x_axis, deg_to_rad(rotate.x), out);
		out = rot_vec3(y_axis, deg_to_rad(rotate.y), out);
		out = rot_vec3(z_axis, deg_to_rad(rotate.z), out);
		out.x += pos.x;
		out.y += pos.y;
		out.z += pos.z;
		return (out);
	}

	double4         basic_get_v3(__global double *vertices, int i)
	{
		int            	add;
		double4           x_axis;
		double4           y_axis;
		double4           z_axis;
		double4			 out;

		x_axis = (double4)(1,0,0,0); // Passer ca sur memoire __constant
		y_axis = (double4)(0,1,0,0); // Passer ca sur memoire __constant
		z_axis = (double4)(0,0,1,0); // Passer ca sur memoire __constant
		add = (vertices[1] * i);
		out.x = *(vertices + add);
		out.y = *(vertices + add + 1);
		out.z = *(vertices + add + 2);
		return (out);
	}
	
	/*** (Absolute to Relative orientation) ***/
	double4            translate_angle_absrel(double4 vec, struct s_cam c)
	{
		double4       unit_vector;
		double       l;

		l = _length(vec);
		unit_vector = vec / l; // Original
		unit_vector = rot_vec3(c.y, -c.pyr.y, unit_vector); // Debug This
		unit_vector = rot_vec3(c.x, -c.pyr.x, unit_vector);
		unit_vector = rot_vec3(c.z, -c.pyr.z, unit_vector);
		if (l != 1)
			return (unit_vector * l);
		return (unit_vector);
	}


void 			_debug_picture_(__global double *zbuffer, __global uchar *picture)
{
	__global s_backbuffer *pb;
	__global uchar *pixels;
	double4		point;
	uint2		coord;
	uint2 		dim;
	uint         x;
    uint         y;
	uint 		npix;
	uint 		gnpix;
	uint 		k;
	uint 		adr;
	double 		pavg;
	uint 		global_addr;
	uint 		global_size;
	uint 		local_addr;
	uint 		local_size;
	uint 		group_addr;

	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);
	
	pb = (__global s_backbuffer *)picture;
	pixels = ((__global uchar *)(&pb->pixels));
	uint pitch;
	uint bpp;
	pitch = pb->pitch; // Original

	uint index;
	dim = pb->dim;
	npix = dim.x * dim.y;
	gnpix = npix * 4;
	
	uint zadr;
	uint2 zdim;
	uint znpix;
	zdim = (uint2)(1500,750);
	znpix = 1500 * 750;
	bpp = pitch / dim.x;
	k = -1;
	while ( (index = (++k * global_size) + global_addr) < npix )
	{
		coord.y = ( index / dim.x );
		coord.x = ( index % dim.x );
		if ( (coord.x < dim.x && coord.x > 0) &&
			(coord.y < dim.y && coord.y > 0) )
		{
			adr = ((coord.y * pitch) + coord.x * bpp); // TEST
			zadr = (((coord.y * zdim.x) + coord.x) * 4);
			pavg = ( pixels[ adr ] + pixels[ adr + 1 ] + pixels[ adr + 2 ] ) / 3; /// Oiginal Marche pas
			///pavg = ( picture[ index * 3 ] + picture[ ( index * 3 ) + 1 ] + picture[ ( index * 3 ) + 2 ] ) / 3; /// Trying 24 bpp
			if (coord.y < zdim.y)
			{
				zbuffer[zadr] = (double)pixels[ adr % gnpix ];
				zbuffer[zadr + 1] = (double)pixels[ (adr + 1) % gnpix];
				zbuffer[zadr + 2] = (double)pixels[ (adr + 2) % gnpix];
				/*zbuffer[zadr] = (double)pixels[ (index * 4) % gnpix ];
				zbuffer[zadr + 1] = (double)pixels[ ((index + 1) * 4) % gnpix];
				zbuffer[zadr + 2] = (double)pixels[ ((index + 2) * 4) % gnpix];*/
				zbuffer[zadr + 3] = 0;
			}
		}
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	
}

	int2        vector_to_pixel(struct s_cam c, double4 input_vector, uint2 dim) /// " Working "
	{
		double2 		 fdim;
		double4           vec3;
		double2           a;
		double2           b;
		double2           p;
		double           dot;
		double2          dot_side;
		double4          angle;
		double2			 pixel;
		int2 			 screen_pixel;
		int2 			 error;

		error.x = -1;
		error.y = -1;
		/* Pre-requis */
		/*input_vector = unit_vec(input_vector);*/
		if (_dot(input_vector, c.ud) < DBL_EPSILON) // Behind Camera
			return (error);
		//vec3 = input_vector; // Test
		vec3 = translate_angle_absrel(input_vector, c); /** <-- Debug this **/
		/* Axe X */
		a.x = vec3.x;
		a.y = vec3.z;
		a = unit_vec2(a);
		b.x = 0;
		b.y = 1;
		p.x = 1;
		p.y = 0;
		dot = _dot2(b, a);
		dot_side.x = _dot2(p, a);

		angle.x = acos(dot);
		angle.y = M_PI_2;
		angle.z = M_PI - angle.x - angle.y;

		fdim.x = c.w;
		fdim.y = c.h;
		
		pixel.x = (c.focal_distance/sin(angle.z)) * sin(angle.x);
		if (dot_side.x >= DBL_EPSILON)
			pixel.x += fdim.x / 2;
		else
			pixel.x = (fdim.x / 2) - pixel.x;

		/* Axe Y */
		a.x = vec3.z;
		a.y = vec3.y;
		a = unit_vec2(a);
		b.x = 1;
		b.y = 0;
		p.x = 0;
		p.y = 1;
		dot = _dot2(b, a);

		dot_side.y = _dot2(p, a);

		angle.x = acos(dot);
		angle.y = M_PI_2;
		angle.z = M_PI - angle.x - angle.y;

		pixel.y = (c.focal_distance/sin(angle.z)) * sin(angle.x);
		if (dot_side.y >= DBL_EPSILON)
			pixel.y += fdim.y / 2;
		else
			pixel.y = (fdim.y / 2) - pixel.y;
		/*if (pixel.x >= fdim.x || pixel.y >= fdim.y || pixel.x < 0 || pixel.y < 0)*/ /// Original Straight Cut
		if (pixel.x >= fdim.x * 2 || pixel.y >= fdim.y * 2 || pixel.x < -fdim.x || pixel.y < -fdim.y) /// Test
			return (error);

		double       width_unit = (fdim.x / dim.x);
		double       height_unit = (fdim.y / dim.y);
		screen_pixel.x = (int)(pixel.x / width_unit);
		screen_pixel.y = dim.y - (int)(pixel.y / height_unit);
		return (screen_pixel);
	}

	int2                 map_vertice(struct s_cam c, uint2 dim, double4 v3)
	{
		int2		ret;
		
		ret = vector_to_pixel(c, unit_vec(v3 - c.o), dim); /// " Working "
		return (ret);
	}

	double2           cross_prod2(double2 a, double2 b)
	{
		double2			ret;

		ret.x = a.x * b.y - a.y * b.x;
		ret.y = a.y * b.x - a.x * b.y;
		return (ret);
	}

	double4            cross_prod3(double4 a, double4 b)
	{
		double4 		ret;

		ret.x = a.y * b.z - a.z * b.y;
		ret.y = a.z * b.x - a.x * b.z;
		ret.z = a.x * b.y - a.y * b.x;
		return (ret);
	}
	struct s_ray			make_ray(double4 org, double4 dir)
	{
		struct s_ray 		R;
		
		R.org = org;
		R.dir = dir;
		return (R);
	}
	struct s_triangle       make_triangle(double4 v1, double4 v2, double4 v3)
	{
		struct s_triangle       T;

		T.v0 = v1;
		T.v1 = v2;
		T.v2 = v3;
		T.u = T.v1 - T.v0;
		T.v = T.v2 - T.v0;
		T.n = unit_vec(cross_prod3(T.u, T.v));
		return (T);
	}
	

	double4         reverse_normal(double4 triangle_normal, double4 vertice)
	{
		double4  n_;
		double4  n;
		double4  bn_;
		double4  bn;

		n = triangle_normal;
		n_ = -n;
		bn = n + vertice;
		bn_ = n_ + vertice;
		if (_length(bn_) < _length(bn))
			return (n_);
		return (n);
	}

	void        draw_triangle_to_zbuffer(__global double *zbuffer, struct s_cam camera, uint2 dim, uchar4 rgb, int2 a, int2 b, int2 c, struct s_triangle triangle, struct s_srf surf, double4 sun_position, __global uchar *picture)
	{
		double4       point;
		double4       ambia;
		double4       diffu;
		double4       specw;
		double4       pc;
		double4       light;
		double4       origine;
		double2   _a;
		double2   _b;
		double2   _c;
		double2   vfa;
		double2   vfb;
		double2   vf_out;
		double2     vs1;
		double2     vs2;
		double2     q;
		double 		depth;
		double   t;
		double   s;
		double       vector_length;
		double       dot_light;
		double       dot_light_spec;
		double2		dv; // Depth per pixel
		int2		coord;
		int2		relcoord;
		int maxX = _max(a.x, _max(b.x, c.x));
		int minX = _min(a.x, _min(b.x, c.x));
		int maxY = _max(a.y, _max(b.y, c.y));
		int minY = _min(a.y, _min(b.y, c.y));
		uint 		adr;
		uint 		gnpix;
		uint 		lnpix;
		uint 		npix;
		uint2 		rectDim;
		
		float d20;
		float d21;

		origine = camera.o;
		//reverse_normal(triangle.n, triangle.v0);

		/*** Triangle Center **/
		point = triangle.v0 + triangle.v1 + triangle.v2;
		point *= 1.f/3.f;
		pc = unit_vec(origine - point);
		
		if (fabs(_dot(pc, triangle.n)) <= 0.00006) /// Avoid "square artefacts" bug  /// BUG
			return ;
		vector_length = _length(point);

		diffu.x = rgb.x;
		diffu.y = rgb.y;
		diffu.z = rgb.z;
		ambia.x = (uchar)((double)rgb.x * 0.2);
		ambia.y = (uchar)((double)rgb.y * 0.2);
		ambia.z = (uchar)((double)rgb.z * 0.2);
		ambia.w = DBL_MAX;
		///ambia.w = vector_length;
		specw.x = 255;
		specw.y = 255;
		specw.z = 255;

		light = point + origine;
		light -= sun_position;
		light = unit_vec(light);
		dot_light = _dot(light, triangle.n); /// GOOD
		
		if (dot_light <= DBL_EPSILON)
			dot_light = 0; // Original
		pc = rot_vec3(triangle.n, deg_to_rad(180), pc); /// Specular Light.
		dot_light_spec = _dot(light, pc);
		
		if (dot_light_spec <= DBL_EPSILON)
			dot_light_spec = 0;
		else
			dot_light_spec = pow(dot_light_spec, 20); /// TEST
		diffu *= dot_light;
		specw *= dot_light_spec;
		ambia += diffu;
		ambia += specw;
		ambia = _clamp(ambia, 0, 255);
		
		_a.x = (double)surf.ptya.x;
		_a.y = (double)surf.ptya.y;
		_b.x = (double)surf.ptyb.x;
		_b.y = (double)surf.ptyb.y;
		_c.x = (double)surf.ptyc.x;
		_c.y = (double)surf.ptyc.y;
		/*_a.x = (double)a.x;
		_a.y = (double)a.y;
		_b.x = (double)b.x;
		_b.y = (double)b.y;
		_c.x = (double)c.x;
		_c.y = (double)c.y;*/
		vs1 = _b - _a;
		vs2 = _c - _a;
		vfb = cross_prod2(vs1, vs2);
		coord.x = minX;
		
		npix = (dim.x * dim.y);
		gnpix = npix * 4;
		
		uint index;
		uint 		global_id;
		uint 		global_size;
		uint 		local_id;
		uint 		local_size;
		uint 		num_group;
		uint 		group_id;
		
		rectDim = (uint2)(maxX - minX, maxY - minY);
		if (rectDim.y <= 0 || rectDim.x <= 0)
			return ;
		global_id = get_global_id(0);
		global_size = get_global_size(0);
		local_id = get_local_id(0);
		local_size = get_local_size(0);
		num_group = get_num_groups(0);
		group_id = get_group_id(0);
		coord.x = minX;
		coord.y = minY;
		
		uint k = -1;
		lnpix = rectDim.x * rectDim.y;
		/***** implementer surf !!! *****/
		while ( (index = (++k * local_size) + local_id) < lnpix )
		{
			relcoord.x = ( index / rectDim.x );
			relcoord.y = ( index % rectDim.x );
			coord.y = minY + relcoord.x;
			coord.x = minX + relcoord.y;
			if ( (coord.x <= maxX && coord.x < dim.x && coord.x > 0) &&
				(coord.y <= maxY && coord.y < dim.y && coord.y > 0) )
			{
				q.x = (double)coord.x - _a.x;
				q.y = (double)coord.y - _a.y;
				vfa = cross_prod2(q, vs2);
				vf_out = vfa / vfb;
				s = vf_out.x;
				vfa = cross_prod2(vs1, q);
				vf_out = vfa / vfb;
				t = vf_out.x;
				if ((s >= -0.000001) && (t >= -0.000001) && (s + t <= 1.000001) ) /// No gap between triangles ; Need to verify precise value
				{
					adr = (((coord.y * dim.x) + coord.x) * 4);
					depth = zbuffer[(adr + 3) % gnpix];
					//ambia.w = /* _length(triangle.v0) + */(t * _length(triangle.v1 ) ) + (s * _length(triangle.v2) );
					//ambia.w = /* _length(triangle.v0) + */(s * _length(triangle.v1 ) ) + (t * _length(triangle.v2) );
					//ambia.w = surf.v0.w + (s * surf.v1.w ) + (t * surf.v2.w );
					ambia.w = surf.v0.w + (s * (surf.v1.w - surf.v0.w) ) + (t * (surf.v2.w - surf.v0.w) );
					//ambia.w = surf.v0.w + (t * (surf.v1.w - surf.v0.w) ) + (s * (surf.v2.w - surf.v0.w) );
					//ambia.w = surf.v0.w;// * ( (t * (surf.v1.w - surf.v0.w) ) + (s * (surf.v2.w - surf.v0.w) ) );
					//ambia.w = surf.v1.w;// * ( (t * (surf.v1.w - surf.v0.w) ) + (s * (surf.v2.w - surf.v0.w) ) );
					//Marker
					/*srf.d00 = _dot(triangle.v0, triangle.v0); // Inside constructor
					srf.d01 = _dot(triangle.v0, triangle.v1);
					srf.d11 = _dot(triangle.v1, triangle.v1);*/

					/*d20 = _dot2(v2, v0);
					d21 = _dot2(v2, v1);
					///I = particle + zdist * gravity;
					bary = Barycentric(I, a, b, c);*/
					
					/*if ()
					{
						dv.x = (double)(surf.dpp.x * (double)relcoord.x);
						dv.y = (double)(surf.dpp.y * (double)relcoord.y);
					}
					else
					{
						
					}
					ambia.w = surf.vdmin + (dv.x + dv.y); // KEEP THIS
					//ambia.w = (dv.x + dv.y); // TRY THIS DEBUG
					///ambia = (double4)(255 - ambia.w * 10, 255 - ambia.w * 10, 255 - ambia.w * 10, ambia.w);
					*/
					/*dv.x = (double)(surf.dpp.x * (double)relcoord.x);
					dv.y = (double)(surf.dpp.y * (double)relcoord.y);
					ambia.w = surf.vdmin + (dv.x + dv.y); // KEEP THIS*/
					
					//ambia.w = vector_length; // Debug OLD
					//ambia = (double4)(255 - ambia.w * ambia.w, 255 - ambia.w * ambia.w, 255 - ambia.w * ambia.w, ambia.w);
					
					if (depth > ambia.w || depth == DBL_MAX) // Bug ?
						*((__global double4 *)(&zbuffer[adr % gnpix])) = ambia;
				}
			}
		}
		return ;
		
		/** Original Linear **/
		/*
		while (coord.x <= maxX && coord.x < dim.x && coord.x > 0) /// Original
		{
			coord.y = minY;
			while (coord.y <= maxY && coord.y < dim.y && coord.y > 0)
			{
				q.x = (double)coord.x - _a.x;
				q.y = (double)coord.y - _a.y;
				vfa = cross_prod2(q, vs2);
				vfb = cross_prod2(vs1, vs2);
				vf_out = vfa / vfb;
				s = vf_out.x;
				vfa = cross_prod2(vs1, q);
				vf_out = vfa / vfb;
				t = vf_out.x;

				if ((s >= -0.000001) && (t >= -0.000001) && (s + t <= 1.000001) ) /// No gap between triangles ; Need to verify precise value
				{
					adr = (((coord.y * dim.x) + coord.x) * 4);
					depth = zbuffer[(adr + 3) % gnpix];
					if (depth > vector_length || depth == DBL_MAX) // Bug ?
						*((__global double4 *)(&zbuffer[adr % gnpix])) = ambia;
				}
				coord.y++; // Linear
			}
			coord.x++; // Linear
		}
		*/
	}

void     draw_f(struct s_option option, struct s_cam camera, __global double *zbuffer, uint2 dim, uchar4 rgb, struct s_triangle T, struct s_srf surf, double4 sun_position, __global uchar *picture)
{
	double4        origine;
	double4           n;
	
	int2             _a;
	int2             _b;
	int2             _c;

	uchar4          color;

	//Marker
	/** Pick Data **/
	origine = camera.o;
	
	color.x = rgb.x;
	color.y = rgb.y;
	color.z = rgb.z;
	color.w = 255;
	
	///n = unit_vec(basic_get_v3(nrm, i));

	/*_a = map_vertice(camera, dim, T.v0);
	_b = map_vertice(camera, dim, T.v1);
	_c = map_vertice(camera, dim, T.v2);*/
	/*_a = surf.ptya;
	_b = surf.ptyb;
	_c = surf.ptyc;*/
	/*T.v0 -= origine;
	T.v1 -= origine;
	T.v2 -= origine;*/
	// Marker
	if (surf.npix != 0)
		draw_triangle_to_zbuffer(zbuffer, camera, dim, color, surf.ptya, surf.ptyb, surf.ptyc, T, surf, sun_position, picture); // Debug Picture;
	//if (_a.x != -1 && _a.y != -1 && _b.x != -1 && _b.y != -1 && _c.x != -1 && _c.y != -1)
		//draw_triangle_to_zbuffer(zbuffer, camera, dim, color, _a, _b, _c, T, sun_position); // Remettre
		//draw_triangle_to_zbuffer(zbuffer, camera, dim, color, _a, _b, _c, T, surf, sun_position, picture); // Debug Picture;
}

///void 			draw_flat_top(__global double *zbuffer, int2 v0, int2 v1, int2 v2, double mindist, double2 dpp, int2 pos, double4 color, uint width)
void 			draw_flat_top(__global double *zbuffer, struct s_srf surf, uint width, uint maxaddr)
{
	double2 	dv;
	double 		depth;
	int2 		slope;
	int2		coord;
	int2 		range_y;
	int2 		range_x;
	uint 		z;
	
	/**
	uint local_id = get_local_id(0);
	uint local_size = get_local_size(0);
	**/
	
	slope = (int2)( surf.s1 ,
					surf.s0 );
	range_y = (int2)( surf.ptya.y, surf.ptyc.y ); /// Vertical Scanline Start / End
	coord.y = range_y.x;
	
	/** _debug_(zbuffer, (uint2)(1500,850)); **/
	z = width * coord.y;
	///coord.y = range_y.x + local_id;
	while (coord.y < range_y.y)
	{
		range_x = (int2)( (int)(slope.x * (coord.y - surf.ptya.y) + surf.ptya.x),
						  (int)(slope.y * (coord.y - surf.ptyb.y) + surf.ptyb.x));
		coord.x = range_x.x;
		while (coord.x < range_x.y)
		{
			dv.x = (double)(surf.dpp.x * (coord.x - surf.pos.x));
			dv.y = (double)(surf.dpp.y * (coord.y - surf.pos.y));
			depth = surf.vdmin + (dv.x + dv.y);
			//depth = 4; // Test debug
			////put_pixel_to_zbuffer(zbuffer, coord.x, z, depth, surf.color, maxaddr); ///
			zbuffer[(((coord.y * width) + coord.x) * 4)] = 255;
			zbuffer[(((coord.y * width) + coord.x) * 4) + 1] = 0;
			zbuffer[(((coord.y * width) + coord.x) * 4) + 2] = 0;
			zbuffer[(((coord.y * width) + coord.x) * 4) + 3] = depth;
			coord.x++;
			//_debug_(zbuffer, (uint2)(1500,850));
			//return ;
		}
		coord.y++;
		z += width;
		///coord.y += local_size;
	}
	return ;
}

void 			draw_flat_bottom(__global double *zbuffer, struct s_srf surf, uint width, uint maxaddr)
{
	double2 	dv;
	double2		slope;
	double 		depth;
	int2		coord;
	int2 		range_y;
	int2 		range_x;
	uint 		y;
	uint 		x;
	uint 		z;
	
	/**
	uint local_id = get_local_id(0);
	uint local_size = get_local_size(0);
	**/
	
	return ;
	slope = (double2)( surf.s1 ,
					   surf.s0 );
	range_y = (int2)( surf.ptya.y, surf.ptyc.y ); /// Vertical Scanline Start / End
	coord.y = range_y.x;
	///coord.y = range_y.x + local_id;
	while (coord.y < range_y.y)
	{
		
		range_x = (int2)( (int)(slope.x * (coord.y - surf.ptya.y) + surf.ptya.x),
						  (int)(slope.y * (coord.y - surf.ptyb.y) + surf.ptyb.x));
		coord.x = range_x.x;
		z = width * coord.y;
		while (coord.x < range_x.y)
		{
			dv.x = (double)(surf.dpp.x * (coord.x - surf.pos.x));
			dv.y = (double)(surf.dpp.y * (coord.y - surf.pos.y));
			depth = surf.vdmin + (dv.x + dv.y);
			////put_pixel_to_zbuffer(zbuffer, coord.x, z, depth, surf.color, maxaddr); ///
			*((__global double4 *)(zbuffer + (((coord.y * width) + coord.x) * 4))) = (double4)(255, 0, 0, depth);
			coord.x++;
		}
		coord.y++;
		///coord.y += local_size;
	}
	return ;
}

void 		render_surface(__global double *zbuffer, struct s_srf srf, uint local_id, uint2 dim) /// Rasterize surface TODO
{
	uint 		width;
	uint2 		coord;
	uint 		maxaddr;
	
	width = dim.x;
	coord = (uint2)( 0, 0 );
	maxaddr = dim.x * dim.y;

	/*if (srf.npix == 0)
		return ;*/
	/*_debug_(zbuffer, dim);
	return ;*/
	if (srf.type == 2)
	{
		///void 		_debug_(__global double *zbuffer, uint2 dim)
		/*_debug_(zbuffer, dim);
		return ;*/
		/*draw_flat_top(zbuffer, srf.ptya, srf.ptyb, srf.ptyc, srf.vdmin, srf.dpp, srf.pos, srf.color, width, srf);
		draw_flat_bottom(zbuffer, srf.ptya, srf.ptyb, srf.ptyc, srf.vdmin, srf.dpp, srf.pos, srf.color, width);*/
		draw_flat_top(zbuffer, srf, width, maxaddr);
		
		draw_flat_bottom(zbuffer, srf, width, maxaddr);
		return ;
	}
	if (srf.type == 0)
	{
		draw_flat_top(zbuffer, srf, width, maxaddr);
		return ;
	}
	if (srf.type == 1)
	{
		draw_flat_bottom(zbuffer, srf, width, maxaddr);
		return ;
	}
}

double4				surface_color_shader(struct s_triangle triangle, double4 sunposition, double4 origine, double4 color)
{
	double4       point;
	double4       ambia;
	double4       diffu;
	double4       specw;
	double4       pc;
	double4       light;
	double       vector_length;
	double       dot_light;
	double       dot_light_spec;
	int2		coord;

	//reverse_normal(triangle.n, triangle.v0);

	/*** Triangle Center **/
	point = triangle.v0 + triangle.v1 + triangle.v2;
	point *= 1.f/3.f;
	pc = unit_vec(origine - point);
	
	if (fabs(_dot(pc, triangle.n)) <= 0.00006) /// Avoid "square artefacts" bug  /// BUG
		return ((double4)(0,0,0,DBL_MAX));
	vector_length = _length(point);

	diffu.x = color.x;
	diffu.y = color.y;
	diffu.z = color.z;
	ambia.x = (uchar)((double)color.x * 0.2);
	ambia.y = (uchar)((double)color.y * 0.2);
	ambia.z = (uchar)((double)color.z * 0.2);
	ambia.w = vector_length;
	specw.x = 255;
	specw.y = 255;
	specw.z = 255;

	light = point + origine;
	light -= sunposition;
	light = unit_vec(light);
	dot_light = _dot(light, triangle.n); /// GOOD
	
	if (dot_light <= DBL_EPSILON)
		dot_light = 0; // Original
	pc = rot_vec3(triangle.n, deg_to_rad(180), pc); /// Specular Light.
	dot_light_spec = _dot(light, pc);
	
	if (dot_light_spec <= DBL_EPSILON)
		dot_light_spec = 0;
	else
		dot_light_spec = pow(dot_light_spec, 20); /// TEST
	diffu *= dot_light;
	specw *= dot_light_spec;
	ambia += diffu;
	ambia += specw;
	return (_clamp(ambia, 0, 255));
}

double				get_srf_length(struct s_srf surf, uint x, uint y) // Surface to analyse ; Relative X coord ; Relative Y coord
{
	/*double 		length;
	
	length = x * surf.dpp.x + surf.dppo.x;
	length += y * surf.dpp.y + surf.dppo.y;*/
	return (surf.vdmin + surf.dpp.x * x + surf.dpp.y * y);
	
}

struct s_srf 		make_surface(struct s_cam camera, struct s_triangle T, double4 sun_pos, double4 color, uint2 dim)
{
	struct s_srf 	srf;
	double 			alpha_split;
	int2             a;
	int2             b;
	int2             c;
	int2             ptxa;
	int2             ptxb;
	int2             ptxc;
	double2 			alen;
	double2 			blen;
	double2 			clen;
	int2 			swp;
	int 			xmin;
	int 			xmax;
	int 			ymin;
	int 			ymax;
	uchar 	corner; // Corner point : TL(0)(+;+) , TR(1)(-;+) , DL(2)(+;-) , DR(3)(-,-)

	//Marker
	/*a = map_vertice(camera, dim, camera.o - T.v0);
	b = map_vertice(camera, dim, camera.o - T.v1);
	c = map_vertice(camera, dim, camera.o - T.v2);*/
	/*T.v0 = camera.o - T.v0;
	T.v1 = camera.o - T.v1;
	T.v2 = camera.o - T.v2;*/
	
	a = map_vertice(camera, camera.sdim, T.v0);
	b = map_vertice(camera, camera.sdim, T.v1);
	c = map_vertice(camera, camera.sdim, T.v2);
	
	//
	/*T.v0 = camera.o - T.v0;
	T.v1 = camera.o - T.v1;
	T.v2 = camera.o - T.v2;*/
	T.v0 = T.v0 - camera.o;
	T.v1 = T.v1 - camera.o;
	T.v2 = T.v2 - camera.o;
	
	char 		skip;

	skip = 0;
	if (a.x == -1)
		skip++;
	if (b.x == -1)
		skip++;
	if (c.x == -1)
		skip++;
	//if (a.x != -1 && a.y != -1 && b.x != -1 && b.y != -1 && c.x != -1 && c.y != -1)
	if (skip >= 1)
	{
		srf.npix = 0;
		srf.vdmin = DBL_MAX;
	}
	else
	{

		/*
		srf.d00 = _dot(T.v0, T.v0);
		srf.d01 = _dot(T.v0, T.v1);
		srf.d11 = _dot(T.v1, T.v1);
		srf.invDenom = 1.0 / (d00 * d11 - d01 * d01);
		*/
		
		/** Sort Vertically START **/
		if (a.y <= b.y && a.y <= c.y)
		{
			srf.ptya = a;
			alen.y = _length(T.v0);
			srf.v0 = T.v0;
			if (b.y <= c.y)
			{
				srf.ptyb = b;
				srf.ptyc = c;
				blen.y = _length(T.v1);
				srf.v1 = T.v1;
				clen.y = _length(T.v2);
				srf.v2 = T.v2;
			}
			if (c.y <= b.y)
			{
				srf.ptyb = c;
				srf.ptyc = b;
				blen.y = _length(T.v2);
				srf.v1 = T.v2;
				clen.y = _length(T.v1);
				srf.v2 = T.v1;
			}
		}
		if (b.y <= a.y && b.y <= c.y)
		{
			srf.ptya = b;
			alen.y = _length(T.v1);
			srf.v0 = T.v1;
			if (a.y <= c.y)
			{
				srf.ptyb = a;
				srf.ptyc = c;
				blen.y = _length(T.v0);
				srf.v1 = T.v0;
				clen.y = _length(T.v2);
				srf.v2 = T.v2;
				
			}
			if (c.y <= a.y)
			{
				srf.ptyb = c;
				srf.ptyc = a;
				blen.y = _length(T.v2);
				srf.v1 = T.v2;
				clen.y = _length(T.v0);
				srf.v2 = T.v0;
			}
		}
		if (c.y <= a.y && c.y <= b.y)
		{
			srf.ptya = c;
			alen.y = _length(T.v2);
			srf.v0 = T.v2;
			if (a.y <= b.y)
			{
				srf.ptyb = a;
				srf.ptyc = b;
				blen.y = _length(T.v0);
				srf.v1 = T.v0;
				clen.y = _length(T.v1);
				srf.v2 = T.v1;
			}
			if (b.y <= a.y)
			{
				srf.ptyb = b;
				srf.ptyc = a;
				blen.y = _length(T.v1);
				srf.v1 = T.v1;
				clen.y = _length(T.v0);
				srf.v2 = T.v0;
			}
		}
		/** Sort Vertically END **/
		
		/** Sort Horizontally START **/
		if (a.x <= b.x && a.x <= c.x)
		{
			ptxa = a;
			alen.x = _length(T.v0);
			if (b.x <= c.x)
			{
				ptxb = b;
				ptxc = c;
				blen.x = _length(T.v1);
				clen.x = _length(T.v2);
			}
			if (c.x <= b.x)
			{
				ptxb = c;
				ptxc = b;
				blen.x = _length(T.v2);
				clen.x = _length(T.v1);
			}
		}
		if (b.x <= a.x && b.x <= c.x)
		{
			ptxa = b;
			alen.x = _length(T.v1);
			if (a.x <= c.x)
			{
				ptxb = a;
				ptxc = c;
				blen.x = _length(T.v0);
				clen.x = _length(T.v2);
			}
			if (c.x <= a.x)
			{
				ptxb = c;
				ptxc = a;
				blen.x = _length(T.v2);
				clen.x = _length(T.v0);
			}
		}
		if (c.x <= a.x && c.x <= b.x)
		{
			ptxa = c;
			alen.x = _length(T.v2);
			if (a.x <= b.x)
			{
				ptxb = a;
				ptxc = b;
				blen.x = _length(T.v0);
				clen.x = _length(T.v1);
			}
			if (b.x <= a.x)
			{
				ptxb = b;
				ptxc = a;
				blen.x = _length(T.v1);
				clen.x = _length(T.v0);
			}
		}
		/** Sort Horizontally END **/
		if (alen.x <= blen.x && alen.x <= clen.x)
			srf.vdmin = alen.x;
		if (blen.x <= alen.x && blen.x <= clen.x)
			srf.vdmin = blen.x;
		if (clen.x <= blen.x && clen.x <= alen.x)
			srf.vdmin = clen.x;

		xmax = ptxc.x;
		xmin = ptxa.x;
		ymax = srf.ptyc.y;
		ymin = srf.ptya.y;
		srf.pos = (int2)(xmin, ymin);
		srf.dim.x = xmax - xmin;
		srf.dim.y = ymax - ymin;

		srf.dpp.x = ( alen.x - clen.x ) / (double)( srf.dim.x );
		srf.dpp.y = ( alen.y - clen.y ) / (double)( srf.dim.y );
		
		double2 Xaxis;
		double2 Yaxis;
		double2 Xv;
		double2 Yv;
		double dotx;
		double doty;
		
		Xv = (double2)(ptxc.x - ptxa.x, ptxc.y - ptxa.y);
		Yv = (double2)(srf.ptyc.x - srf.ptya.x, srf.ptyc.y - srf.ptya.y);
		
		/// Using barycentric coordinates.
		double ba;
		double bb;
		double bc;
		
		srf.npix = srf.dim.x * srf.dim.y;
		srf.color = surface_color_shader(T, sun_pos, camera.o, color);
	}
	return (srf);
}

///void 		draw_model_stack(struct s_option option, struct s_cam camera, __global struct s_model *arg_models, __global double *zbuffer, double4 sun_pos, uint2 cdim)
void 		draw_model_stack(struct s_option option, struct s_cam camera, __global double4 *arg_tri, __global struct s_srf *surface_global_buffer,
							__global double *zbuffer, __global uchar *picture, double4 sun_pos, uint2 cdim)
{
	double4 		color;
	///struct s_model model;
    int         i;
	uint2		dim;
	double4 	nvertices;
	
	uint 		global_id;
	uint 		global_size;
	uint 		local_id;
	uint 		local_size;
	uint 		num_group;
	uint 		group_id;

	uint 		addr;
	
	__local double4 	ta;
	__local double4 	tb;
	__local double4 	tc;
	double4 			a;
	double4 			b;
	double4 			c;
	//__local struct s_srf surface_buffer[1024]; // Test (verify !!!!!!! ) <- MUST BE EQUAL TO LOCAL_SIZE ;;; TOO LARGE !!!!
	///__local struct s_sortsrf surface_buffer[1024]; // Test (verify !!!!!!! ) <- MUST BE EQUAL TO LOCAL_SIZE
	struct s_sortsrf		surface;
	//dim = camera.sdim; // Original
	dim = cdim;
	
	global_id = get_global_id(0);
	global_size = get_global_size(0);
	local_id = get_local_id(0);
	local_size = get_local_size(0);
	num_group = get_num_groups(0);
	group_id = get_group_id(0);
	color = (double4)(255, 0, 0, 0);
	
	struct s_srf 		*pswp;
	struct s_srf 		surf;
	struct s_triangle T;
	nvertices = *arg_tri;
	arg_tri++;
    i = 0;
	addr = group_id * 3;
	///addr = global_id * 3;
    while (addr + 2 <= (uint)nvertices.x)
	{
		///model = *arg_models;
		///barrier(CLK_LOCAL_MEM_FENCE); //
		if (local_id == 0)
		{
			ta = arg_tri[addr];
			tb = arg_tri[addr + 1];
			tc = arg_tri[addr + 2];

			/*a = arg_tri[addr];
			b = arg_tri[addr + 1];
			c = arg_tri[addr + 2];*/
			
		}
		barrier(CLK_LOCAL_MEM_FENCE); //
		//Marker
		a = ta;
		b = tb;
		c = tc;
		a -= camera.o;
		b -= camera.o;
		c -= camera.o;
		a.w = _length(a);
		b.w = _length(b);
		c.w = _length(c);
		T = make_triangle(a, b, c);
		/**
		//draw_f(option, camera, zbuffer, dim, color, T, sun_pos, picture); // Debug picture
		**/
		
		
		surf = make_surface(camera, T, sun_pos, color, dim); // Compute surface
		
		/*
		surface.p = &surface_global_buffer[global_id];
		surface.vdmin = surf.vdmin;
		surface_global_buffer[global_id] = surf; // Push Result in local memory
		surface_buffer[local_id] = surface; // Push Result in local memory
		odd_even_transpose_sort_on_local_surfaces(surface_buffer, local_id, local_size, group_id);
		*/
		

		///surf = surface_buffer[local_id];
		/*** render_surface(zbuffer, surface_buffer[local_id], local_id, dim.x); ***/
		
		/** render_surface(zbuffer, *surface_buffer[local_id].p, local_id, dim.x); */ // <--- Remettre ça.
		if (surf.npix != 0)
			render_surface(zbuffer, surf, local_id, dim); // <--- Test
		
		/*if (local_id == 0)
		{
			
			
		}*/
	
		/**
		sort_iter = 1;
		while (sort_surfaces(surface_buffer, 1024, local_id, sort_iter))
			sort_iter++;**/
		
		i++;
		addr = ((i * num_group) + group_id) * 3;
		///addr = (i * global_id) * 3;
	}
	///barrier(CLK_GLOBAL_MEM_FENCE);
}

///void 		draw_model_stack(struct s_option option, struct s_cam camera, __global struct s_model *arg_models, __global double *zbuffer, double4 sun_pos, uint2 cdim)
///void 		OLDdraw_model_stack(struct s_option option, struct s_cam camera, __global double4 *arg_tri, __global double *zbuffer, __global uchar *picture, double4 sun_pos, uint2 cdim)
void 		OLDdraw_model_stack(struct s_option option, struct s_cam camera, __global double4 *arg_tri, __global double *zbuffer, __global uchar *picture, double4 sun_pos, uint2 cdim)
{
	struct s_srf surf;
	uchar4 		color;
	double4 		dcolor;
	///struct s_model model;
    int         i;
	uint2		dim;
	double4 	nvertices;
	
	uint 		global_id;
	uint 		global_size;
	uint 		local_id;
	uint 		local_size;
	uint 		num_group;
	uint 		group_id;

	uint 		addr;
	
	__local double4 	ta;
	__local double4 	tb;
	__local double4 	tc;
	double4 			a;
	double4 			b;
	double4 			c;
	//dim = camera.sdim; // Original
	dim = cdim;
	
	global_id = get_global_id(0);
	global_size = get_global_size(0);
	local_id = get_local_id(0);
	local_size = get_local_size(0);
	num_group = get_num_groups(0);
	group_id = get_group_id(0);
	color = (uchar4)(255, 0, 0, 0);
	
	struct s_triangle T;
	nvertices = *arg_tri;
	arg_tri++;
    i = 0;
	addr = group_id * 3;
    while (addr + 2 <= nvertices.x)
	{
		//Marker
		///model = *arg_models;
		barrier(CLK_LOCAL_MEM_FENCE); //
		if (local_id == 0)
		{
			ta = arg_tri[addr];
			tb = arg_tri[addr + 1];
			tc = arg_tri[addr + 2];
		}
		/*a = camera.o;
		b = camera.o;
		c = camera.o;*/
		barrier(CLK_LOCAL_MEM_FENCE); //
		/*a -= ta;
		b -= tb;
		c -= tc;*/
		a = ta;
		b = tb;
		c = tc;
		/*a = camera.o - ta;
		b = camera.o - tb;
		c = camera.o - tc;*/
		/*a = ta - camera.o;
		b = tb - camera.o;
		c = tc - camera.o;
		a.w = _length(a);
		b.w = _length(b);
		c.w = _length(c);*/
		a.w = _length(a - camera.o);
		b.w = _length(b - camera.o);
		c.w = _length(c - camera.o);
		T = make_triangle(a, b, c);
		surf = make_surface(camera, T, sun_pos, dcolor, dim); // Compute surface
		//draw_f(option, camera, zbuffer, dim, color, T, sun_pos); // Remettre
		draw_f(option, camera, zbuffer, dim, color, T, surf, sun_pos, picture); // Debug picture
		i++;
		addr = ((i * num_group) + group_id) * 3;
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
}

void     put_zbuffer_to_backbuffer(struct s_cam cam, __global double *zbuffer, __global uchar4 *backbuf) // Original (Crashing)
{
	__global s_backbuffer *pb;
	__global uchar4 *pixels;
	uint2 		dim;
	uchar4		pix;
	uint 		global_addr;
	uint 		global_size;
	uint 		local_addr;
	uint 		local_size;
	uint 		group_addr;
	uint         x;
    uint         y;
	uint npix;
	uint addr;
	uint gaddr;
	uint k;

	pb = (__global s_backbuffer *)backbuf;
	pixels = (__global uchar4 *)pb;
	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);

	dim = cam.sdim;
	npix = dim.x * dim.y;
	
	k = -1;
	while ( (addr = (++k * global_size) + global_addr) < npix )
	{
		gaddr = addr * 4;
		if (zbuffer[gaddr + 3] == DBL_MAX)
			pix.w = 0;
		else
            pix.w = 255;
		pix.x = (uchar)(zbuffer[gaddr]);
		pix.y = (uchar)(zbuffer[gaddr + 1]);
		pix.z = (uchar)(zbuffer[gaddr + 2]);
		pixels[addr % npix] = pix;
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
}

///void        draw_cloud(t_grid *g, t_grid *msk, t_conf *conf, SDL_Surface *viewport, int i, int j)
void        draw_cloud_to_zbuffer(__global double *cloud, __global uchar *picture, struct s_option option, struct s_cam camera, __global double *zbuffer, uint2 picdim, double2 picdiv)
{
	__global s_backbuffer *pb;
	__global uchar *pixels;
	double4 	pc;
	double4 	va;
	double4 	vb;
	double4 	point;
	double 		pcl;
	int2 		spix;
	uint2 		dim;
	uint 		gnpix;
	uint 		zadr;
	uint 		pnpix;
	uint 		global_addr;
	uint 		global_size;
	uint 		local_addr;
	uint 		local_size;
	uint 		group_addr;
	uint         x;
    uint         y;
	uint npix;
	uint addr;
	uint gaddr;
	uint gaddr_pic;
	uint saddr;
	uint k;
	uchar4 	picpix;
	uchar4 	color;
	uchar 	depth; /// Grayscale value.
	double npt;
	double step;

	/*** CRITICAL VALUE (too low = crunch glass cube) ***/
	///step = 0.1 / (double)depth;
	///step = 0.5 / 255;
	///step = 0.1;
	step = 0.5 / 255.0;
	/*** CRITICAL VALUE (too low = crunch glass cube) ***/

	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);
	
	uint2		coord;
	uint 		pitch;
	uint 		bpp;
	pb = (__global s_backbuffer *)picture;
	pixels = ((__global uchar *)(&pb->pixels));
	pitch = pb->pitch;
	bpp = pitch / picdim.x;
	
	dim = camera.sdim;
	npix = dim.x * dim.y;
	gnpix = npix * 4;
	pnpix = (picdim.x * picdim.y); // Original
	///pnpix = (100 * 100);
	k = -1;
	
	while ( (addr = (++k * global_size) + global_addr) < pnpix )
	{
		gaddr = addr * 4; // Original
		point.w = cloud[gaddr + 3];		
		if (point.w != 0)
		{
			point.x = cloud[gaddr];
			point.y = cloud[gaddr + 1];
			point.z = cloud[gaddr + 2];
			
			pc = point - camera.o;
			pcl = _length(pc);
			///va = unit_vec(pc);
			va = unit_vec(pc);
			vb = camera.ud;
			if (_dot(va, vb) >= DBL_EPSILON && pcl > 0)
			{
				/**
					coord.y = ( addr / (uint)(picdim.x * (uint)option.picdiv.x));
					coord.x = ( addr % (uint)(picdim.y * (uint)option.picdiv.y));
				**/
				// Original
					coord.y = ( addr / picdim.x);
					coord.x = ( addr % picdim.x);
				/*
					depth = (double)picdim.y / picdiv.y;
					coord.y = (uint)(addr / (uint)depth);
					depth = (double)picdim.x / picdiv.x;
					coord.x = (uint)(addr % (uint)depth);
				*/
				// DEBUG
					/*coord.y = ( addr / 100) * picdiv.y;
					coord.x = ( addr % 100) * picdiv.x;
					*/
				///coord.x = ( addr % picdim.y);
				gaddr_pic = ((coord.y * pitch) + coord.x * bpp); // Original
				
				///gaddr_pic = ((coord.y * pitch) + (coord.x * picdiv.x) * bpp); // TEST
				picpix.x = pixels[gaddr_pic];
				picpix.y = pixels[gaddr_pic + 1];
				picpix.z = pixels[gaddr_pic + 2];
				picpix.w = (picpix.x + picpix.y + picpix.z) / 3;
				///pcl = _length(pc - camera.focal_distance);
				depth = picpix.w / 8;
				if (depth == 0) /// Non avoiding black pixels
					depth = 1;
				///npt = 1 - (sqrt((double)depth) >> 2);
				//npt = 1 - (sqrt((double)pcl) * 0.5);
				//npt = 1 - (1 / sqrt((double)pcl / 2)); // * 0.5);
				///npt = (1 / sqrt((double)pcl / 2)); // * 0.5);
				npt = 1 - (1 / (sqrt((double)pcl) * 64)); // * 0.5);
				depth = (double)(npt * (double)depth);
				//depth = npt;
				if (npt <= 0)
				{
					depth = 1;
					npt = 0;
				}

				/*npt = 1 - (sqrt((double)pcl) * 0.1);
				color = (uchar4)((uchar)(255 * npt), (uchar)(255 * npt), 0, 0);*/
				///npt = 1 - (sqrt((double)pcl) * 0.1);
				while (depth--)
				{
					spix = map_vertice(camera, dim, point);
					if (spix.x >= 0 && spix.y >= 0 && spix.x < dim.x && spix.y < dim.y)
					{
						saddr = ( (spix.y * dim.x) + spix.x ) * 4;
						if (saddr < gnpix)
						{
							color = (uchar4)((uchar)(picpix.x * npt), (uchar)(picpix.y * npt), (uchar)(picpix.z * npt), 0);

							zbuffer[saddr] = color.x;
							zbuffer[(saddr + 1)] = color.y;
							zbuffer[(saddr + 2)] = color.z;
							color.w = zbuffer[(saddr + 3)];
							if (color.w > pcl - DBL_EPSILON)
								zbuffer[(saddr + 3)] = pcl;
							///zbuffer[saddr] = (double4)color;
						}
					}
					///point.z += step; /// Test
					point.z -= step; /// Test
				}
			}
		}
	}
	barrier(CLK_GLOBAL_MEM_FENCE);	
}


#define PAD_X 0.001
#define PAD_Y 0.001

void 			set_cloud_from_picture(__global uchar *picture, __global double *cloud, struct s_option opt, __global struct s_model *models) /* RT not implemented */// Original
{
	 double scale_factor = 0.01;
	__global s_backbuffer *pb;
	__global uchar *pixels;
	double4		point;
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
	double 		pavg;
	double 		depth;

	pb = (__global s_backbuffer *)picture;
	pixels = ((__global uchar *)&pb->pixels);
	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);

	uint index;
	dim = pb->dim;
	npix = dim.x * dim.y;
	gnpix = npix * 4;
	
	uint cadr;
	uint pitch;
	uint bpp;
	pitch = pb->pitch;
	bpp = pitch / dim.x;
	
	k = -1;
	while ((index = (++k * global_size) + global_addr) < npix )
	{
		coord.y = ( index / dim.x );
		coord.x = ( index % dim.x );
		if ( (coord.x < dim.x && coord.x > 0) &&
			(coord.y < dim.y && coord.y > 0) )
		{
			///depth = rayTracing();
			depth = 0;//global_addr;//10; // Debug
			adr = ((coord.y * pitch) + coord.x * bpp); // TEST
			cadr = ((coord.y * dim.x) + coord.x) * 4; // TEST

			pavg = ( pixels[ adr ] + pixels[ adr + 1 ] + pixels[ adr + 2 ] ); /// 24bpp no div
			
			point.x = (double)(coord.x * opt.scale_factor) - ((dim.x / 2) * opt.scale_factor);
			point.y = (double)((dim.y / 2) * opt.scale_factor) - (coord.y * opt.scale_factor);
			//point.z = (double)coord.x * scale_factor;

			//point.z = (double)pavg * 0.001;
			point.z = ((double)pavg / 3);
			/*point.z = (double)depth;*/

			//*((__global double4 *)(&zbuffer[adr % gnpix])) = point;
			cloud[cadr] = point.x;
			cloud[cadr + 1] = point.y;
			///cloud[cadr + 2] = point.z; // Original
			cloud[cadr + 2] = -8; // Debug intersections
			cloud[cadr + 3] = DBL_MAX;
		}
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
}

/********** RT *****************/

int intersect3D_RayTriangle( struct s_ray R, struct s_triangle T, /** double4 *I, **/ double *Dist )
{
    double4     dir;             // ray vectors
    double4     w0;              // ray vectors
    double4     w1;              // ray vectors
    ///double4     w;               // ray vectors
    double     r, a, b;              // params to calc ray-plane intersect

    if (T.n.x == 0 && T.n.y == 0 && T.n.z == 0)             // triangle is degenerate
        return (-1);                  // do not deal with this case

    dir = R.dir;										// ray direction vector
    w0 = R.org - T.v0; // Original
    w1 = T.v0 - R.org; // Original TEST

    T.n = cross_prod3(T.u, T.v); // Original TEST

	/*
    double4 to;
    double4 rt;
    double denom;
	//////////////////T.n = reverse_normal(T.n, T.v0); // Test
	denom = _dot(T.n, R.dir);
    if (fabs(denom) > DBL_EPSILON) // your favorite epsilon
    ///if (denom > DBL_EPSILON) // TEST
    {
        to = T.v0 - R.org; //
		to = unit_vec(to); // Test
		r = _dot(to, T.n) / denom; // Original
        if (r >= DBL_EPSILON) // DEBUG TEST
        {
            rt = dir * r;//
            *Dist = r;
            return (1); // you might want to allow an epsilon here too
        }
    }
    return (0); // Test
	*/
    a = -_dot(T.n, w0); // Original
    b = _dot(T.n, dir); // Original
    if (fabs(b) < DBL_EPSILON + 0.01) {     // ray is  parallel to triangle plane // Test
        if (a == 0)                 // ray lies in triangle plane
        //if (a >= 0)                 // ray lies in triangle plane
            return (2);
        return (0);              // ray disjoint from plane
    }
	
	double4 	tmp;
	double4       I;

    // get intersect point of ray with triangle plane
    r = a / b; // Original
    if (r <= 1)                    // ray goes away from triangle
        return (0);                   // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect
	I = R.org + r * dir;            // intersect point of ray and plane
    /// Test
    ///*Dist = length3(tmp); // Original
    ////*Dist = sqrt(length3(tmp)); // Log Zbuffer
    //return (1);
    /// Test
    double4       Tu;
    double4       Tv;
    double4       w;
    //double       Tn[3];
    // is I inside T?
    double    uu, uv, vv, wu, wv, D;
    /// Test
    Tu = unit_vec(T.u);
    Tv = unit_vec(T.v);
    /// Test
    uu = _dot(T.u,T.u);
    uv = _dot(T.u,T.v);
    vv = _dot(T.v,T.v);
    w = T.v0 - I;
    wu = _dot(w, T.u);
    wv = _dot(w, T.v);
    D = (uv * uv) - uu * vv;

    // get and test parametric coords
    double s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0 || s > 1)         // I is outside T
        return (0);
    t = (uv * wu - uu * wv) / D;
    if (t < 0 || (s + t) > 1)  // I is outside T
        return (0);
    Tu = T.u * s;
    Tv = T.v * t;
    tmp = Tu + Tv;
    tmp += T.v0;

    tmp = tmp - R.org; // Original
    *Dist = _length(tmp);
    return (1);                       // I is in T
}
/** int intersectPlane(const Vec3f &n, const Vec3f &p0, const Vec3f &l0, const Vec3f &l, float &t)
{
	// assuming vectors are all normalized
	float denom = dotProduct(n, l);

	if (denom > 1e-6) {
		Vec3f p0l0 = p0 - l0;
		t = dotProduct(p0l0, n) / denom;
		return (t >= 0);
	}
	return (0);
} */
/********** RT *****************/

// Compute barycentric coordinates (u, v, w) for
// point p with respect to triangle (a, b, c)
double4 Barycentric(double4 p, double4 a, double4 b, double4 c)
{
	double4 	barycenter;
    double4 v0 = b - a,
			v1 = c - a,
			v2 = p - a;
    double d00 = _dot(v0, v0);
    double d01 = _dot(v0, v1);
    double d11 = _dot(v1, v1);
    double d20 = _dot(v2, v0);
    double d21 = _dot(v2, v1);
    double denom = d00 * d11 - d01 * d01;
	/*
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
	*/
    barycenter.x = (d11 * d20 - d01 * d21) / denom;
    barycenter.y = (d00 * d21 - d01 * d20) / denom;
    barycenter.z = 1.0f - barycenter.x - barycenter.y;
	return (barycenter);
}

double Intersect(double4 planeP, double4 planeN, double4 rayP, double4 rayD)
{
    double d = _dot(planeP, -planeN);
    double t = -(d + rayP.z * planeN.z + rayP.y * planeN.y + rayP.x * planeN.x) / (rayD.z * planeN.z + rayD.y * planeN.y + rayD.x * planeN.x);
    ///return (rayP + t * rayD); // Original double4
	return (t);
}

///double4 			fall(__global struct s_model *model, double4 particle, double4 gravity) /// Original
double4 			fall(__global struct s_model *model, double4 particle, double4 gravity, __global double *zbuffer, __global uchar *picture) // Test
{
	double4			ret;
	double4			bary;
	double4			I;

	double4        translate;
	double4        rotate;
	double4        scale;
	double4           n;
	__local double4           a;
	__local double4           b;
	__local double4           c;
	__global char   *ptr;
	__global double *vrt;
	__global double *nrm;
	__global int 	*fce;
	int             nf;
	int             i;
	int             j;
	int             flen;
	double 			minimum_zdist;
	double 			zdist;
	struct s_model 	local_stack_model;
	struct s_model 	stack_model;
	struct s_triangle 	T;
	double denom; //
	double t; //
	ptr = (__global char *)((__global uchar *)model + sizeof(struct s_model));
	vrt = (__global double *)ptr;
	nrm = (__global double *)(ptr + model->n_jmp);
	fce = (__global int *)(ptr + model->f_jmp);

	if (get_local_id(0) == 0)
		local_stack_model = *model;
	barrier(CLK_LOCAL_MEM_FENCE);
	stack_model = local_stack_model;
	translate = stack_model._translate;
	rotate = stack_model._rotate;
	scale = stack_model._scale;

	nf = stack_model.nf;
	ret = particle;
	i = 0;
	//_debug_picture_(zbuffer, picture); // DEBUG
	//return ((double4)(particle.x, particle.y, particle.z + 5, 0)); // DEBUG
	minimum_zdist = DBL_MAX;
	while (i < nf)
	//while (i < nf)
	{
		flen = fce[0];
		j = 2;
		if (get_local_id(0) == 0)
			a = get_v3(vrt, fce[1], translate, rotate, scale);
		//barrier(CLK_LOCAL_MEM_FENCE);
		while (j < flen)
		{
			if (get_local_id(0) == 0)
			{
				b = get_v3(vrt, fce[j], translate, rotate, scale);
				c = get_v3(vrt, fce[j + 1], translate, rotate, scale);
			}
			//barrier(CLK_LOCAL_MEM_FENCE);
			/*b -= particle;
			c -= particle;*/
			j++;
			
			T = make_triangle(a, b, c);
			/*
			if ( intersect3D_RayTriangle( make_ray(particle, gravity), make_triangle(a, b, c), &zdist ) == 1)
				if (zdist < minimum_zdist)
					minimum_zdist = zdist;
			*/
			zdist = Intersect(a, T.n, particle, gravity);
			I = particle + zdist * gravity;
			//return ((double4)(particle.x, particle.y, particle.z + 50, 50));
			bary = Barycentric(I, a, b, c);
			if (bary.x <= 1 && bary.y <= 1 && bary.z <= 1 && bary.x >= DBL_EPSILON && bary.y >= DBL_EPSILON && bary.z >= DBL_EPSILON)
			{
				if (zdist < minimum_zdist)
					minimum_zdist = zdist;
			}

		}
		fce += flen + 1;
		i++;
	}
	//return ((double4)(particle.x, particle.y, particle.z + 30, 30));
	if (minimum_zdist == DBL_MAX)
		//return (ret);
		return ((double4)(particle.x, particle.y, particle.z + 30, DBL_MAX));
	///ret = particle + (gravity * minimum_zdist); /// Original
	ret.x += 0;//gravity.x * minimum_zdist;
	ret.y += 0;//gravity.y * minimum_zdist;
	ret.z += minimum_zdist;//gravity.z * minimum_zdist;
	ret.w = minimum_zdist;//_length(ret - particle);
	//ret.w = sqrt(_length(ret - particle));
	return (ret);
}

//void 			cloud_fall(__global struct s_model *model_ptr, __global double *cloud, uint2 cdim) // Original
void 			cloud_fall(__global struct s_model *model_ptr, __global double *cloud, struct s_option option, uint2 cdim, __global double *zbuffer, __global uchar *picture) // Debug
{
	double4			gravity = (double4)(0,0,1,0); /* Fall in Z :: put in const memory */
	double4			point;
	double4			touch;
	double4			first_hit;
	__global struct s_model *arg_models;
	size_t 		next_model;
	struct s_model model;
    int         i;
	uint2		dim;
	uint 		addr;
	uint 		cnpix;
	uint 		gaddr;
	uint 		k;
	uint 		global_addr;
	uint 		global_size;
	uint 		local_addr;
	uint 		local_size;
	uint 		group_addr;
	
	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);
	
	//cnpix = (cdim.x * cdim.y); // Original
	cnpix = 869 * 869;
	k = -1;
	while ( (addr = (++k * global_size) + global_addr) < cnpix )
	{
		gaddr = addr * 4;
		point.x = cloud[gaddr];
		point.y = cloud[gaddr + 1];
		point.z = cloud[gaddr + 2];
		///cloud[gaddr + 3] = DBL_MAX; // (already done at set_cloud_from_picture)
		point.w = 0;
		
		first_hit.x = 0;
		first_hit.y = 0;
		first_hit.z = 0;
		first_hit.w = DBL_MAX;
		
		i = 0;
		arg_models = model_ptr;
		model = *arg_models;
		next_model = model.next_model;
		//while (arg_models && next_model != 0) /// Original
		//while (next_model != 0 && ++i < option.max_model)
		//first_hit = (double4)(point.x, point.y, point.z + 4, 4);
		///if (local_addr == 0)
			///while (i < option.max_model)
			while (i < 1)
			{
				model = *arg_models;
				next_model = model.next_model;
				//_debug_picture_(zbuffer, picture); // Debug
				//return ;
				///model = *arg_models;
				if (model.active == 1 && model.nf != 0)
				{
					///touch = fall(arg_models, point, gravity); // Original
					touch = fall(arg_models, point, gravity, zbuffer, picture); // Test
					//touch = (double4)(point.x, point.y, point.z + 10, 4);
					if (touch.w < first_hit.w)
					{
						first_hit = touch;
					}
				}
				next_model = model.next_model;
				i++;
				if (next_model == 0)
					i = option.max_model;
				arg_models = (__global struct s_model *)(((__global uchar *)arg_models) + next_model); // Test
			}
		cloud[gaddr] = first_hit.x;
		cloud[gaddr + 1] = first_hit.y;
		cloud[gaddr + 2] = first_hit.z;
		cloud[gaddr + 3] = first_hit.w;
	}
	//barrier(CLK_GLOBAL_MEM_FENCE);
}

/// MAIN ///
__kernel void rasterize(__global struct s_cam *camera,
                        __global double4 *sun_pos,
                        __global uchar *picture,
						__global double *zbuffer,
						__global double4 *arg_tri,
						//__global uchar *arg_models,
                        __global uchar4 *backbuffer,
						__global struct s_srf *surface_buffer, // TEST Vertex Shader
						__global double *cloud,
						__global struct s_option *option)
{
	__global s_backbuffer *pb;
	__global struct s_model *models;
	struct s_cam 	cam;
	struct s_option opt;
	__global double4 	*p;
	double4 	sun;
	double2 	picdimdiv;

	p = sun_pos;
	sun = *p;
	pb = (__global s_backbuffer *)picture; //
	//models = (__global struct s_model *)arg_models; //
	cam = *camera;
	opt = *option;

	picdimdiv.x = (double)((double)pb->dim.x / opt.picdiv.x);
	picdimdiv.y = (double)((double)pb->dim.y / opt.picdiv.y);
	///picdimdiv = pb->dim;
	
	reset_zbuffer(zbuffer, cam.sdim);

	if (opt.display_cloud == 1)
		draw_cloud_to_zbuffer(cloud, picture, opt, cam, zbuffer, pb->dim, picdimdiv);
		///draw_cloud_to_zbuffer(cloud, picture, opt, cam, zbuffer, pb->dim);
	if (opt.display_model == 1)
	{
		/*void 		draw_model_stack(struct s_option option, struct s_cam camera, __global double4 *arg_tri, __global struct s_srf *surface_global_buffer,
							__global double *zbuffer, __global uchar *picture, double4 sun_pos, uint2 cdim)*/
		//draw_model_stack(opt, cam, arg_tri, surface_buffer, zbuffer, picture, *sun_pos, cam.sdim);//
		OLDdraw_model_stack(opt, cam, arg_tri, zbuffer, picture, sun, cam.sdim);
	}
	put_zbuffer_to_backbuffer(cam, zbuffer, backbuffer);
	barrier(CLK_GLOBAL_MEM_FENCE);
}