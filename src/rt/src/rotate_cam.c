/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:15:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/26 20:00:08 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "rotation.h"

double			convert_to_radian(double angle)
{
	return (angle / 180.0 * PI);
}

void			rotate_vector(t_vector *vec, t_rotate_arg *a)
{
	double	buf_x;
	double	buf_y;
	double	buf_z;

	buf_x = vec->x;
	buf_y = vec->y;
	buf_z = vec->z;
	vec->x = buf_x * a->cosy * a->cosz -
			buf_y * a->cosy * a->sinz +
			buf_z * a->siny;
	vec->y = buf_x * (a->cosx * a->sinz + a->sinx * a->siny * a->cosz) +
			buf_y * (a->cosx * a->cosz - a->sinx * a->siny * a->sinz) -
			buf_z * (a->sinx * a->cosy);
	vec->z = buf_x * (a->sinx * a->sinz - a->cosx * a->siny * a->cosz) +
			buf_y * (a->sinx * a->cosz + a->cosx * a->siny * a->sinz) +
			buf_z * (a->cosx * a->cosy);
}

void			init_rotation_trigo(t_rotate_arg *arg)
{
	arg->a_x = convert_to_radian(arg->a_x);
	arg->a_y = convert_to_radian(arg->a_y);
	arg->a_z = convert_to_radian(arg->a_z);
	arg->cosx = cos(arg->a_x);
	arg->cosy = cos(arg->a_y);
	arg->cosz = cos(arg->a_z);
	arg->sinx = sin(arg->a_x);
	arg->siny = sin(arg->a_y);
	arg->sinz = sin(arg->a_z);
}

void			rotate_reference(t_rotate_arg *arg)
{
	init_rotation_trigo(arg);
	rotate_vector(arg->v_z, arg);
	rotate_vector(arg->v_y, arg);
	rotate_vector(arg->v_x, arg);
}

void			rotate_cam(t_vcam *cam, double a_x, double a_y, double a_z)
{
	t_rotate_arg	arg;

	arg.v_x = cam->right;
	arg.v_y = cam->up;
	arg.v_z = cam->dir;
	arg.a_x = a_x;
	arg.a_y = a_y;
	arg.a_z = a_z;
	rotate_reference(&arg);
}
