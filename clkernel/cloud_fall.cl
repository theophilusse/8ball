#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define DBL_HIT_EPSILON 0x1.0p-51
#define DBL_EPSILON 0x1.0p-52
//#define LOCAL_SIZE   256
#define LOCAL_SIZE   256

	///#define _length(v) (sqrt(fabs((v.x * v.x) + (v.y * v.y) + (v.z * v.z))))
	double 			_length(double4 v)
	{
		return (sqrt(fabs((v.x * v.x) + (v.y * v.y) + (v.z * v.z))));
	}
	///#define _dot(a, b) (a.x * b.x + a.y * b.y + a.z * b.z)
	double 			_dot(double4 a, double4 b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}
	

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
/*
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
}                       t_model;*/
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
    }                       t_option;

	double4           unit_vec(double4 v)
	{
		double 		l;

		l = _length(v);

		//if (l <= DBL_EPSILON || l == 0)
		/*if (l <= 1) // Dont do this
			return (v * l);*/
		return (v / l);
	}

	double4            cross_prod3(double4 a, double4 b)
	{
		double4 		r;

		r.x = a.y * b.z - a.z * b.y;
		r.y = a.z * b.x - a.x * b.z;
		r.z = a.x * b.y - a.y * b.x;
		r.w = 0;
		return (r);
	}

	struct s_triangle       make_triangle(double4 v1, double4 v2, double4 v3)
	{
		double4		cross;
		struct s_triangle       T;

		T.v0 = v1;
		T.v1 = v2;
		T.v2 = v3;
		T.u = T.v1 - T.v0;
		T.v = T.v2 - T.v0;
		cross = cross_prod3(T.u, T.v);
		//T.n = unit_vec(cross);
		T.n = cross;
		return (T);
	}

	
/*char 		sumof(__local uint *data) // Not work :(
{
	uint 	addr;
	uint 	n;
	uint 	va;
	uint 	vb;
	uint 	to;
	uint 				local_id;
	uint 	v;
	
	local_id = get_local_id(0);

	to = 128; // Half Buf size
	while (to > 1 && to < 128)
	{
		if (local_id < to)
		{
			addr = (local_id * 2);
			v = data[addr] + data[addr + 1];
			data[local_id] = v;
		}
		to /= 2;
	}
	barrier(CLK_LOCAL_MEM_FENCE);
}

void 			BubbleSort(__local double *data) // Did not work :(
{
	double 			va;
	double 			vb;
	char 			shift;
	uint 			sum;
	__local uint 	swp[LOCAL_SIZE];
	uint 			addr;
	uint 				local_id;
	
	local_id = get_local_id(0);
	
	swp[local_id] = 0;
	sum = 1;
	while (sum > 0)
	{
		shift = shift == 1 ? 0 : 1;
		addr = (local_id * 2) + shift;
		swp[local_id] = 0;
		if (addr < LOCAL_SIZE)
		{
			va = data[addr];
			vb = data[addr + 1];
			if (vb < va)
			{
				swp[local_id] = 1;
				data[addr] = vb;
				data[addr + 1] = va;
			}
		}
		sumof(swp);
		sum = swp[0];
	}
}*/

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
	barycenter = (double4)(0,0,0,0);
	/*if (denom != 0)
	{*/
		barycenter.x = (d11 * d20 - d01 * d21) / denom;
		barycenter.y = (d00 * d21 - d01 * d20) / denom;
		barycenter.z = 1.0f - barycenter.x - barycenter.y;
	//}
	return (barycenter);
}

double Intersect(double4 planeP, double4 planeN, double4 rayP, double4 rayD)
{
	/*
    double dota;
    double dotb;
	double t;

	//d = _dot(planeP, -planeN);
	//dota = _dot(planeP, -planeN);
	dota = _dot(planeP, planeN);
	//dotb = _dot(rayD, planeN);
	//dotb = (rayD.z * planeN.z + rayD.y * planeN.y + rayD.x * planeN.x);
	dotb = -(rayD.z * planeN.z + rayD.y * planeN.y + rayD.x * planeN.x); // Good ?
	t = 0;
	/// KEEP
	if (dotb > 0)
	//if (dotb > 0) // Work
	{
		//t = -(dota + rayP.z * planeN.z + rayP.y * planeN.y + rayP.x * planeN.x) / dotb;
		t = (dota + rayP.z * planeN.z + rayP.y * planeN.y + rayP.x * planeN.x) / dotb; // Good ?
		if (t < DBL_EPSILON)
			t = 0;
	}
	//return (t); /// Original shit
	*/
	
	//t = -(_dot(planeN, rayP) + _dot(planeN, rayP)) / _dot(planeN, rayD); 
	//float t = - (dot(N, orig) + D) / dot(N, dir); 
	
	/**
	double D;
	double t;
	
	D = _dot(planeN, planeP); 
	if (D == 0)
		return (0);
	t = (_dot(planeP - rayP, planeN) + D) / _dot(rayD, planeN); 
	**/
	
	double denom;
	double dist;
	double t;

	//t = 0;
	//t = _dot(rayD, planeN); // zero
	//t = _dot(planeN, rayP); // zero
	t = _length(planeN);
	denom = _dot(rayD, planeN);
	dist = -_dot(planeN, rayP);
	//dist = 7;
	//if (denom != 0)
		//t = -(dot(rayP, planeN) + dist) / denom;
		//t = -(dot(rayP, planeN) + dist);
		//t = denom; // Zero ??
	/*if (t < 0)
		t = 0;*/
	return (t);
}

/*double 		minval(__local double *val, uint arraySize)
{
	uint 		i;
	double 		v;
	double 		min;

	min = DBL_MAX;
	i = arraySize;
	while (i > 0)
	{
		i--;
		v = val[i];
		if (v < min)
			min = v;
		else
			min = min;
	}
	return (min);
}*/

double 		minval(__local double *val, uint arraySize)
{
	double 		va;
	double 		vb;
	double 		vc;
	uint 		core;
	uint 		modul;
	uint 		local_id = get_local_id(0);
	uint 		addr;

	/** zdist = minval(minimum_zdist, LOCAL_SIZE); /// Keep **/
	core = arraySize;
	modul = arraySize * 2;
	//while (core > 1)
	core /= 2;
	while (core > 1)
	{
		addr = local_id * 2;
		if (local_id < core) // good
		{
			va = val[addr];
			///va = val[addr % modul]; // bad
			vb = val[addr + 1];
			//vb = val[(addr + 1) % modul]; // bad
			vc = vb < va ? vb : va;
			val[local_id] = vc;
			//val[local_id % modul] = vc;
		}
		core /= 2;
		barrier(CLK_LOCAL_MEM_FENCE);
	}
	//barrier(CLK_LOCAL_MEM_FENCE);
	return (val[0]);
}

//int 			fall(uint ntriangle, __global double *triangle, double4 particle, double4 gravity, __local double4 *touch) // Test
//int 			fall(uint nvertices, __global double *triangle, double4 particle, double4 gravity, double4 *touch, __global double *cloud_debug) // Debug

double 			fall(double4 particle, double4 gravity, uint nvertices, double4 a, double4 b, double4 c, __global double *cloud_debug) // Test private triangles
//double 			fall(double4 particle, double4 gravity, uint nvertices, __local double4 *triangle, __global double *cloud_debug) // Test local triangles
///double 			fall(double4 particle, double4 gravity, uint nvertices, __global double4 *triangle, __global double *cloud_debug) // Test global triangles
{
	__local double4			ret;
	double4					bary;
	double4					I;
	double4           		n;
	/*double4           		a; // LOCAL MODE
	double4           		b; // LOCAL MODE
	double4           		c; // LOCAL MODE*/
	double4           		u;
	double4           		v;
	double4 			tmp;
	double4 			tnorm;
	double4 w;
	double4 wa;
	double4 wb;
	double4 D;
	double 					priv_minimum_zdist; //
	double 					zdist;
	double denom;
	double num;
	//struct s_triangle 		T; // Optional
	uint 				global_size;
	uint 				global_id;
	uint 				local_size;
	uint 				local_id;
	uint 				num_groups;
	uint 				group_id;
	
	global_size = get_global_size(0);
	global_id = get_global_id(0);
	local_size = get_local_size(0);
	local_id = get_local_id(0);
	num_groups = get_num_groups(0);
	group_id = get_group_id(0);

	uint 		addr;
	uint 		k = 0;

	ret = particle;
	k = 0;
	zdist = 0;
	addr = local_id * 3;
	barrier(CLK_LOCAL_MEM_FENCE);
	/*a = triangle[addr];
	b = triangle[addr + 1];
	c = triangle[addr + 2];*/
	/*u = a - c;
	v = b - c;*/ // Original
	u = c - a;
	v = c - b;

		tmp = cross_prod3(u, v);
		tnorm = unit_vec(tmp);
		
		w = a - particle;
		denom = _dot(gravity, tnorm);
		///denom = _dot(gravity, -gravity); // Debug
		num = _dot(w, tnorm);
		///num = _dot(w, -gravity);
		//if (denom > 0)
		if (denom != 0)
			zdist = num / denom;

		/** zdist = Intersect(a, tnorm, particle, gravity);**/ // KEEP
		I = (double4)(0,0,0,0) + (particle + zdist * gravity); // No cast test
		//I = particle + (zdist * gravity); // No cast test
		/**zdist *= Barycentric(I, a, b, c, &bary);**/

		/***** bary.x problem ******/
		bary = Barycentric(I, a, b, c); // Keep

		if (bary.x >= 1 + DBL_HIT_EPSILON)
			zdist = 0;
		 if (bary.y >= 1 + DBL_HIT_EPSILON)
			zdist = 0;
		if (bary.z >= 1 + DBL_HIT_EPSILON)
			zdist = 0;
		if (bary.x <= 0)
			zdist = 0;
		if (bary.y <= 0)
			zdist = 0;
		if (bary.z <= 0)
			zdist = 0;
		if ( addr + 2 <= nvertices ) // Test Local memory /////////////
			zdist = 0;
	///barrier(CLK_LOCAL_MEM_FENCE); /// 
	///if (zdist > 0)
	///if (zdist < DBL_EPSILON)
	if (zdist == 0)
		return (DBL_MAX);
	return (zdist);
}

//void 			cloud_fall(__global struct s_model *model_ptr, __global double *cloud, uint2 cdim) // Original
void 			NEWpicture_fall(__global double4 *triangle, __global double4 *cloud, uint2 cdim, uint2 prange) // Debug
{
	double4			priv_triangle[3]; // local_size * 3
	__local	double4			triangle_group[LOCAL_SIZE * 3]; // local_size * 3
	////__local double 			minimum_zdist[LOCAL_SIZE]; //
	__local double 			minimum_zdist[16][LOCAL_SIZE]; //
	double4				gravity = (double4)(0, 0, 1, 1); /* Fall in Z :: put in const memory */
	// double4				gravity = (double4)(0, 0, 100, 100); /* Fall in Z :: put in const memory */
	double4 			nvertices;
	//__local double4	point; // Old
	double4				point;
	double			touch;
	///double					hit; /// DIV <= 16
	double					hit[32]; //[inc / num_groups]; /// DIV <= 16
	double 					zdist;
	uint2		dim;
	uint 		addr;
	uint 		cnpix;
	uint 		gaddr;
	uint 		i;
	uint 		k;
	uint 				global_size;
	uint 				global_id;
	uint 				local_size;
	uint 				local_id;
	uint 				num_groups;
	uint 				group_id;
	uint				prea;
	uint				preb;
	uint 		div;
	uint 		verticesleft;
	uint 		verticesleft_clamp;
	
	global_size = get_global_size(0);
	global_id = get_global_id(0);
	local_size = get_local_size(0);
	local_id = get_local_id(0);
	num_groups = get_num_groups(0);
	group_id = get_group_id(0);
	
	nvertices = *triangle;
	triangle++;
	div = (uint)ceil(nvertices.x / local_size); // Test
	prange.y = prange.y >= (cdim.x * cdim.y) ? (cdim.x * cdim.y) : prange.y;
	/** uint range = prange.x - prange.y; **/
	cnpix = (cdim.x * cdim.y); // Original
	barrier(CLK_LOCAL_MEM_FENCE);
	i = 0;
	while (i < 16)
	{
		minimum_zdist[i][local_id] = DBL_MAX;
		hit[k] = DBL_MAX;
		i++;
	}
	verticesleft = nvertices.x;
	i = 0;
	while (i < div)
	{
		///hit = DBL_MAX;
		prea = (local_id * 3);
		preb = ((local_id * 3) + (local_size * i));
		barrier(CLK_GLOBAL_MEM_FENCE);
		if (preb < (uint)nvertices.x) // copy to local fail here ?
		{
			priv_triangle[0] = triangle[preb];
			priv_triangle[1] = triangle[preb + 1];
			priv_triangle[2] = triangle[preb + 2];
		}
		k = 0;
		addr = group_id + prange.x;
		verticesleft_clamp = verticesleft <= LOCAL_SIZE ?  verticesleft : LOCAL_SIZE;
		while ( addr < prange.y && addr < cnpix ) // Original
		//while ( k < 1 ) // 16
		{
			barrier(CLK_LOCAL_MEM_FENCE);
			if (preb < (uint)nvertices.x) // copy to local fail here ?
			{
				point = cloud[addr];
				touch = fall(point, gravity, verticesleft_clamp, priv_triangle[0], priv_triangle[1], priv_triangle[2], (__global double *)cloud); // Test private triangles
				//barrier(CLK_LOCAL_MEM_FENCE);
				if (touch < hit[k])
					hit[k] = touch;
			}
			k++;
			addr = (k * num_groups) + group_id + prange.x;
		}
		verticesleft -= verticesleft <= LOCAL_SIZE ?  verticesleft : LOCAL_SIZE;
		i++;
	}
	addr = group_id + prange.x;
	barrier(CLK_GLOBAL_MEM_FENCE);
	k = 0;
	while ( addr < prange.y && addr < cnpix )
	{
		barrier(CLK_LOCAL_MEM_FENCE);
		minimum_zdist[k][local_id] = hit[k];
		barrier(CLK_LOCAL_MEM_FENCE);
		zdist = minval(minimum_zdist[k], LOCAL_SIZE); /// Keep
		if (zdist == DBL_MAX)
			zdist = 0;
		if (local_id == 0)
			cloud[addr] = point + gravity * zdist; // Keep
		k++;
		addr = (k * num_groups) + group_id + prange.x;
	}
}

void 			picture_fall(__global double4 *triangle, __global double4 *cloud, uint2 cdim, uint2 prange) // Debug
{
	double4			priv_triangle[3]; // local_size * 3
	__local	double4			triangle_group[LOCAL_SIZE * 3]; // local_size * 3
	__local double 			minimum_zdist[LOCAL_SIZE]; //
	double4				gravity = (double4)(0, 0, 1, 1); /* Fall in Z :: put in const memory */
	// double4				gravity = (double4)(0, 0, 100, 100); /* Fall in Z :: put in const memory */
	double4 			nvertices;
	//__local double4	point; // Old
	double4				point;
	__local double4			touch;
	double2					hit; /// DIV <= 16
	double 					zdist;
	uint2		dim;
	uint 		addr;
	uint 		cnpix;
	uint 		gaddr;
	uint 		i;
	uint 		k;
	uint 				global_size;
	uint 				global_id;
	uint 				local_size;
	uint 				local_id;
	uint 				num_groups;
	uint 				group_id;
	uint				prea;
	uint				preb;
	uint 		div;
	uint 		verticesleft;
	uint 		verticesleft_clamp;
	
	global_size = get_global_size(0);
	global_id = get_global_id(0);
	local_size = get_local_size(0);
	local_id = get_local_id(0);
	num_groups = get_num_groups(0);
	group_id = get_group_id(0);
	
	nvertices = *triangle;
	triangle++;
	//div = (uint)ceil(nvertices.x / local_size); // Test ////////////// IMP. FOR GEOMETRY
	div = (uint)ceil(nvertices.x / local_size); // Test ////////////// IMP. FOR GEOMETRY
	prange.y = prange.y >= (cdim.x * cdim.y) ? (cdim.x * cdim.y) : prange.y;
	/** uint range = prange.x - prange.y; **/
	cnpix = (cdim.x * cdim.y); // Original

	k = 0;
	addr = group_id + prange.x;
	barrier(CLK_GLOBAL_MEM_FENCE);
	point = cloud[addr];
	while ( addr < prange.y && addr < cnpix )
	{
		hit = DBL_MAX;
		i = 0;
		verticesleft = (uint)nvertices.x;
		while (i < div)
		{
			prea = (local_id * 3);
			///preb = ((local_id * 3) + (local_size * i)) % (uint)nvertices.x;
			preb = ((local_id * 3) + (local_size * i));
			barrier(CLK_LOCAL_MEM_FENCE);
			//if (preb < (uint)nvertices.x) // copy to local fail here ?
			//{
			/*
			triangle_group[prea] = triangle[preb];
			triangle_group[prea + 1] = triangle[preb + 1];
			triangle_group[prea + 2] = triangle[preb + 2];
			*/
			priv_triangle[0] = triangle[preb % verticesleft];
			priv_triangle[1] = triangle[(preb + 1) % verticesleft];
			priv_triangle[2] = triangle[(preb + 2) % verticesleft];
			if (preb < (uint)nvertices.x) // copy to local fail here ?
			{
				priv_triangle[0] = (double4)(5,0,0,0); // Test
				priv_triangle[1] = (double4)(4,0,0,0); // Test
				priv_triangle[2] = (double4)(3,0,0,0); // Test
			}
			verticesleft_clamp = verticesleft <= LOCAL_SIZE ?  verticesleft : LOCAL_SIZE;
			hit.x = fall(point, gravity, verticesleft_clamp, priv_triangle[0], priv_triangle[1], priv_triangle[2], (__global double *)cloud); // Test private triangles
			//hit.x = fall(point, gravity, verticesleft_clamp, triangle_group, (__global double *)cloud); // Test local triangles
			///hit.x = fall(point, gravity, verticesleft_clamp, triangle + local_size * i, (__global double *)cloud); // Test global triangles
			//hit.x = triangle_group[prea].x;
			if (hit.x < hit.y)
			//if (hit.x > hit.y)
				hit.y = hit.x;
			verticesleft -= verticesleft <= LOCAL_SIZE ?  verticesleft : LOCAL_SIZE;
			//verticesleft -= LOCAL_SIZE;
			i++;
			barrier(CLK_LOCAL_MEM_FENCE);
		}
		minimum_zdist[local_id] = hit.y;
		zdist = minval(minimum_zdist, LOCAL_SIZE); /// Keep
		if (zdist == DBL_MAX)
			zdist = 0;
		if (local_id == 0)
			///cloud[addr] = priv_triangle[1]; // Private mem OK
			///cloud[addr] = (double4)(triangle_group[0].x, triangle_group[0].y, triangle_group[0].z, triangle_group[1].x); // Local mem fail
			///cloud[addr] = (double4)(triangle[1].x, triangle[1].y, triangle[1].z, triangle[2].y); // Global mem OK
			cloud[addr] = point + gravity * zdist; // Keep
		k++;
		addr = (k * num_groups) + group_id + prange.x;
		barrier(CLK_GLOBAL_MEM_FENCE);
		point = cloud[addr];
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
}


void 			set_cloud_from_picture(__global s_backbuffer *picture, __global double4 *cloud, struct s_option opt) /* RT not implemented */// Original
{
	struct t_backbuffer pb;
	double4		point;
	double 		scale_factor = 0.01;
	double 		pavg;
	double 		depth;
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
	__global uchar *pixels;

	pb = *picture;
	pixels = ((__global uchar *)&picture->pixels);
	global_addr = get_global_id(0);
	global_size = get_global_size(0);
	local_addr = get_local_id(0);
	local_size = get_local_size(0);
	group_addr = get_num_groups(0);

	uint index;
	dim = pb.dim; /// Original
	/*
		depth = (double)pb.dim.x / opt.picdiv.x;
		dim.x = (uint)depth;
		depth = (double)pb.dim.y / opt.picdiv.y;
		dim.y = (uint)depth;
	*/
	///dim = ((double2)pb.dim / opt.picdiv;
	npix = dim.x * dim.y;
	gnpix = npix * 4;
	
	uint cadr;
	uint pitch;
	uint bpp;
	pitch = pb.pitch;
	bpp = pitch / dim.x;
	k = -1;
	while ((index = (++k * global_size) + global_addr) < npix )
	{
		///coord.y = ( index / dim.x );
		coord.y = ( index / dim.x );
		coord.x = ( index % dim.x );
		/*if ( (coord.x < dim.x && coord.x > 0) && // BUG , MOD
			(coord.y < dim.y && coord.y > 0) )
		{*/
			depth = 0;//global_addr;//10; // Debug
			adr = ((coord.y * pitch) + coord.x * bpp); // TEST
			///adr = ((coord.y * pitch) + coord.x * 4); // TEST
			cadr = ((coord.y * dim.x) + coord.x); // TEST

			pavg = ( pixels[ adr ] + pixels[ adr + 1 ] + pixels[ adr + 2 ] ); /// 24bpp no div
			
			point.x = (double)(coord.x * opt.scale_factor) - ((dim.x / 2) * opt.scale_factor);
			point.y = (double)((dim.y / 2) * opt.scale_factor) - (coord.y * opt.scale_factor);
			//point.z = (double)coord.z * scale_factor;
			//point.z = (double)pavg * 0.001;
			point.z = opt.scale_factor;
			point.w = (double)0;

			if (cadr < npix)
				cloud[cadr] = point;
		//}
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
}

__kernel void cloud_fall(
                        __global uchar *picture,
						__global double4 *arg_tri,
						__global double4 *cloud,
						__global struct s_option *option)
{
	__global s_backbuffer *pb;
	struct s_option opt;
	__global double4 	*p;

	pb = (__global s_backbuffer *)picture; //
	opt = *option;

	if (opt.set_cloud == 1) /// Bug here
		set_cloud_from_picture(pb, cloud, opt);
	//picture_fall(arg_tri, cloud, pb->dim, opt.pixels_range); // Debug
	barrier(CLK_GLOBAL_MEM_FENCE);
}