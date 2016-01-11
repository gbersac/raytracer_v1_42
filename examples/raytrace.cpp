#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

#include "Raytrace.h"

bool init(char* inputName, scene &my_scene)
{
	int nbMat, nbSphere, nbLight;
	int i;
	ifstream sceneFile(inputName);
	if (!sceneFile)
		return  false;
	sceneFile >> my_scene.sizex >> my_scene.sizey;
	sceneFile >> nbMat >> nbSphere >> nbLight;
	my_scene.matTab.resize(nbMat);
	my_scene.sphTab.resize(nbSphere);
	my_scene.lgtTab.resize(nbLight);
	for (i=0; i < nbMat; i++)
		sceneFile >> my_scene.matTab[i];
	for (i=0; i < nbSphere; i++)
		sceneFile >> my_scene.sphTab[i];
	for (i=0; i < nbLight; i++)
		sceneFile >> my_scene.lgtTab[i];
	return true;
}

void	header_file(ofstream *imageFile, scene &my_scene)
{
	// Ajout du header TGA
	imageFile->put(0).put(0);
	imageFile->put(2);        /* RGB non compresse */

	imageFile->put(0).put(0);
	imageFile->put(0).put(0);
	imageFile->put(0);

	imageFile->put(0).put(0); /* origine X */
	imageFile->put(0).put(0); /* origine Y */

	imageFile->put((my_scene.sizex & 0x00FF)).put((my_scene.sizex & 0xFF00) / 256);
	imageFile->put((my_scene.sizey & 0x00FF)).put((my_scene.sizey & 0xFF00) / 256);
	imageFile->put(24);       /* 24 bit bitmap */
	imageFile->put(0);
	// fin du header TGA
}

bool	hitSphere(const t_ray *r, const sphere &s, float &t)
{
// intersection rayon/sphere
	t_vector dist = sub_pt_pt(&s.pos, &r->start);
	float B = mul_vec_vec(&r->dir, &dist);
	float D = B*B - mul_vec_vec(&dist, &dist) + s.size * s.size;
	if (D < 0.0f)
		return false;
	float t0 = B - sqrtf(D);
	float t1 = B + sqrtf(D);
	bool retvalue = false;
	if ((t0 > 0.1f) && (t0 < t))
	{
		t = t0;
		retvalue = true;
	}
	if ((t1 > 0.1f) && (t1 < t))
	{
		t = t1;
		retvalue = true;
	}
	return retvalue;
}

t_intersec		*intersect_sphere(t_ray *view_ray, scene &my_scene)
{
	float		t = 20000.0;
	int			currentSphere= -1;
	t_intersec	*to_return;

	for (unsigned int i = 0; i < my_scene.sphTab.size(); ++i)
	{
		if (hitSphere(view_ray, my_scene.sphTab[i], t))
		{
			currentSphere = i;
		}
	}
	to_return = (t_intersec*)malloc(sizeof(t_intersec));
	to_return->currentSphere = currentSphere;
	to_return->t = t;
	return (to_return);
}

t_vector	vec_normal(t_point *vec, t_point *pt)
{
	t_vector	n;
	double		temp;

	n = sub_pt_pt(vec, pt);
	temp = mul_vec_vec(&n, &n);
	if (temp == 0.0)
	{
		n.x = 0.;
		n.y = 0.;
		n.z = 0.;
		return (n); // TODO undefined behavior ???
	}
	temp = 1.0 / sqrtf(temp);
	n = mul_scalar_vec(temp, &n);
	return (n);
}

void		light(scene *my_scene, t_vector *n, t_point *newStart, double coef, material currentMat, float *red, float *green, float *blue)
{
	unsigned int		j;

	j = 0;
	while (j < my_scene->lgtTab.size())
	{
		t_light current = my_scene->lgtTab[j];
		t_vector dist = sub_pt_pt(&current.pos, newStart);
		if (mul_vec_vec(n, &dist) <= 0.0)
		{
			++j;
			continue ;
		}
		float t = sqrtf(mul_vec_vec(&dist, &dist));
		if (t <= 0.0)
		{
			++j;
			continue ;
		}
		t_ray lightRay;
		lightRay.start = *newStart;
		lightRay.dir = mul_scalar_vec((1/t), &dist);
		// calcul des ombres
		bool inShadow = false;
		for (unsigned int i = 0; i < my_scene->sphTab.size(); ++i) {
			if (hitSphere(&lightRay, my_scene->sphTab[i], t)) {
				inShadow = true;
				break;
			}
		}
		if (!inShadow) {
			// lambert
			float lambert = mul_vec_vec(&lightRay.dir, n) * coef;
 			*red += lambert * current.red * currentMat.red;
			*green += lambert * current.green * currentMat.green;
			*blue += lambert * current.blue * currentMat.blue;
		}
		++j;
	}
}

bool	draw(char* outputName, scene &my_scene)
{
	ofstream imageFile(outputName,ios_base::binary);
	if (!imageFile)
		return false;
	header_file(&imageFile, my_scene);

	// balayage
	int			x;
	int			y;
	int			color;
	t_vector	ray;
	t_vector	n_ray;

	y = 0;
	while (y < my_scene.sizey)
	{
		x = 0;
		while (x < my_scene.sizex)
		{
			float red = 0, green = 0, blue = 0;
			double coef = 1.0;
			int level = 0;
			// lancer de rayon
			t_ray view_ray = { {double(x), double(y), -10000.0f}, { 0.0f, 0.0f, 1.0f}};
			while ((coef > 0.0) && (level <= 10))
			{
				t_intersec *intersec_res = intersect_sphere(&view_ray, my_scene);
				int currentSphere = intersec_res->currentSphere;
				double t = intersec_res->t;
				// recherche de l'intersection la plus proche
				if (currentSphere == -1)
					break;

				t_vector t_mul_dir = mul_scalar_vec(t, &view_ray.dir);
				t_point newStart = add_pt_vec(&view_ray.start, &t_mul_dir);
				// la normale au point d'intersection
				t_vector n = vec_normal(&newStart, &my_scene.sphTab[currentSphere].pos);

				material currentMat = my_scene.matTab[my_scene.sphTab[currentSphere].material];

				// calcul de la valeur d'éclairement au point
				light(&my_scene, &n, &newStart, coef, currentMat, &red, &green, &blue);

				// on itére sur la prochaine reflexion
				coef *= currentMat.reflection;
				float reflet = 2.0 * mul_vec_vec(&view_ray.dir, &n);
				view_ray.start = newStart;
				t_vector reflet_mul_n = mul_scalar_vec(reflet, &n);
				view_ray.dir = sub_vec_vec(&view_ray.dir, &reflet_mul_n);

				level++;
			}
			imageFile
					.put((unsigned char)min(blue*255.0f,255.0f))
					.put((unsigned char)min(green*255.0f, 255.0f))
					.put((unsigned char)min(red*255.0f, 255.0f));
			++x;
		}
		++y;
	}
	return true;
}

int		main(int argc, char* argv[]) {
	if  (argc < 3)
		return -1;
	scene my_scene;
	if (!init(argv[1], my_scene))
		return -1;
	if (!draw(argv[2], my_scene))
		return -1;
	return 0;
}
