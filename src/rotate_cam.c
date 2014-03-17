/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:15:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/17 17:02:22 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "rotation.h"
//
#include <stdio.h>

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

/*
** Angle are supposed to be measured in degree.
*/
void			init_rotation_trigo(t_rotate_arg *arg)
{
	arg->a_x = -convert_to_radian(arg->a_x);
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

/*
** void			rotate_reference(t_rotate_arg *arg)
** {
** 	arg->cosx = cos(arg->a_x);
** 	arg->cosy = cos(arg->a_y);
** 	arg->cosz = cos(arg->a_z);
** 	arg->sinx = sin(arg->a_x);
** 	arg->siny = sin(arg->a_y);
** 	arg->sinz = sin(arg->a_z);
** 	printf("@@@rotation de z %f\n", arg->a_z);
** 	printf("avant z %s\n", print_vector(arg->v_z));
** 	rotate_vector(arg->v_z, arg);
** 	printf("apres z %s\n", print_vector(arg->v_z));
** 	printf("@@@rotation de y %f\n", arg->a_y);
** 	printf("avant y %s\n", print_vector(arg->v_y));
** 	rotate_vector(arg->v_y, arg);
** 	printf("apres y %s\n", print_vector(arg->v_y));
** 	printf("@@@rotation de x %f\n", arg->a_x);
** 	printf("avant x %s\n", print_vector(arg->v_x));
** 	rotate_vector(arg->v_x, arg);
** 	printf("apres x %s\n", print_vector(arg->v_x));
** 	printf("@@@result : x %s y %s z %s\n", print_vector(arg->v_x), print_vector(arg->v_y), print_vector(arg->v_z));
** }
*/
