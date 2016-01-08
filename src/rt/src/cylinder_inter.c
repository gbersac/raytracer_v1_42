/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 21:40:29 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/26 19:57:58 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "rotation.h"

void		init_rotate_arg(t_rotate_arg *arg, t_cylinder *cyl)
{
	t_vcam	*cam;

	cam = ft_get_cam_vector(NULL);
	arg->a_x = cyl->rotation->x;
	arg->a_y = cyl->rotation->y;
	arg->a_z = cyl->rotation->z;
}

t_vector	reorient_vector(t_vector *dir_ref, t_cylinder *cyl)
{
	t_rotate_arg	arg;
	t_vector		dir;

	init_rotate_arg(&arg, cyl);
	init_rotation_trigo(&arg);
	dir.x = dir_ref->x;
	dir.y = dir_ref->y;
	dir.z = dir_ref->z;
	rotate_vector(&dir, &arg);
	return (dir);
}

double		ft_inter_cylinder(t_vector *dir_ref, t_vector *origin_ref,
				void *data)
{
	double			a;
	double			b;
	double			c;
	t_vector		dir;
	t_vector		origin;
	t_cylinder		*cylinder;

	cylinder = (t_cylinder*)data;
	dir = reorient_vector(dir_ref, cylinder);
	origin = ft_vec_sub(*origin_ref, *(cylinder->origin));
	a = pow(dir.x, 2) + pow(dir.z, 2);
	b = 2 * ((dir.x * origin.x)
			+ (dir.z * origin.z));
	c = pow(origin.x, 2)
			+ pow(origin.z, 2)
			- pow(cylinder->rayon, 2);
	return (ft_get_smaller_dist(a, b, c));
}
