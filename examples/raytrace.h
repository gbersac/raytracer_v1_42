typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef t_vector	t_point;

istream & operator >> ( istream &inputFile,  t_vector& v )
{
	return inputFile >> v.x >> v.y >> v.z ;
}

t_point	add_vec(const t_vector *p, const t_vector *v)
{
	t_vector p2={p->x + v->x, p->y + v->y, p->z + v->z };
	return (p2);
}

t_point	sub_pt_vec(const t_point *p, const t_vector *v){
	t_point p2={p->x - v->x, p->y - v->y, p->z - v->z};
	return (p2);
}

t_vector sub_pt_pt(const t_point *p1, const t_point *p2){
	t_vector v={p1->x - p2->x, p1->y - p2->y, p1->z - p2->z};
	return (v);
}

t_vector mul_scalar_vec(double c, const t_vector *v)
{
	t_vector v2 = {v->x *c, v->y * c, v->z * c };
	return (v2);
}

t_vector sub_vec_vec(const t_vector *v1, const t_vector *v2){
	t_vector v = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
	return (v);
}

double mul_vec_vec(const t_vector *v1, const t_vector *v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

struct material
{
	double red, green, blue, reflection;
};
istream & operator >> ( istream &inputFile, material& mat )
{
	return inputFile >> mat.red >> mat.green >> mat.blue >> mat.reflection;
}

struct sphere
{
	t_point pos;
	double size;
	int material;
};
istream & operator >> ( istream &inputFile, sphere& sph )
{
	return inputFile >> sph.pos >> sph.size >> sph.material;
}

typedef struct	s_light
{
	t_point pos;
	double red, green, blue;
}				t_light;

istream & operator >> ( istream &inputFile, t_light& lig )
{
	return inputFile >> lig.pos >> lig.red >> lig.green >> lig.blue;
}

typedef struct	s_ray
{
	t_point start;
	t_vector dir;
}				t_ray;

struct scene
{
	vector<material> matTab;
	vector<sphere>   sphTab;
	vector<t_light>    lgtTab;
	int sizex, sizey;
};

typedef struct	s_intersec
{
	int		currentSphere;
	double	t;
}				t_intersec;
