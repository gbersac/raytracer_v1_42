/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:15:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/13 17:57:19 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h>

char	*print_vector(t_vector *vect)
{
	char *str = (char*) malloc(sizeof(char) * 100);
	sprintf(str, "{x:%f y:%f z:%f}", vect->x, vect->y, vect->z);
	return (str);
}

double		convert_to_radian(double angle)
{
	return (angle / 180 * PI);
}

/*static*/ void	rotate_single_x(t_vector *v, double sine, double cosine)
{
	double	buf_y;
	double	buf_z;

	buf_y = v->y;
	buf_z = v->z;
	v->y = buf_y * cosine - buf_z * sine;
	v->z = buf_y * sine + buf_z * cosine;
}

/*static*/ void	rotate_cam_x(t_vcam *cam, double angle)
{
	double		sine;
	double		cosine;

	if (angle == 0)
		return ;
	sine = sin(angle);
	cosine = cos(angle);
	rotate_single_x(cam->up, sine, cosine);
	rotate_single_x(cam->dir, sine, cosine);
}

/*static*/ void	rotate_single_y(t_vector *v, double sine, double cosine)
{
	double	buf_x;
	double	buf_z;

	buf_x = v->x;
	buf_z = v->z;
	v->x = buf_x * cosine + buf_z * sine;
	v->z = buf_z * cosine - buf_x * sine;
}

/*static*/ void	rotate_cam_y(t_vcam *cam, double angle)
{
	double		sine;
	double		cosine;

	if (angle == 0)
		return ;
	sine = sin(angle);
	cosine = cos(angle);
	rotate_single_y(cam->right, sine, cosine);
	rotate_single_y(cam->dir, sine, cosine);
}

/*static*/ void	rotate_single_z(t_vector *v, double sine, double cosine)
{
	double	buf_x;
	double	buf_y;

	buf_x = v->x;
	buf_y = v->y;
	v->x = buf_x * cosine - buf_y * sine;
	v->y = buf_x * sine + buf_y * cosine;
}

/*static*/ void	rotate_cam_z(t_vcam *cam, double angle)
{
	double		sine;
	double		cosine;

	if (angle == 0)
		return ;
	sine = sin(angle);
	cosine = cos(angle);
	rotate_single_z(cam->right, sine, cosine);
	rotate_single_z(cam->up, sine, cosine);
}

void		rotate_cam(t_vcam *cam, double a_x, double a_y, double a_z)
{
	a_x = -convert_to_radian(a_x);
	a_y = convert_to_radian(a_y);
	a_z = convert_to_radian(a_z);
	rotate_cam_x(cam, a_x);
	rotate_cam_y(cam, a_y);
	rotate_cam_z(cam, a_z);
}

// void		rotate_cam(t_vcam *cam, double a_x, double a_y, double a_z)
// {
// 	a_x = -convert_to_radian(a_x);
// 	a_y = convert_to_radian(a_y);
// 	a_z = convert_to_radian(a_z);
// 	printf("@@@rotation through x %f\n", a_x);
// 	printf("avant vector y %s vector z %s\n", print_vector(cam->up), print_vector(cam->dir));
// 	rotate_cam_x(cam, a_x);
// 	printf("apres vector y %s vector z %s\n", print_vector(cam->up), print_vector(cam->dir));
// 	printf("@@@rotation through y %f\n", a_y);
// 	printf("avant vector x %s vector z %s\n", print_vector(cam->right), print_vector(cam->dir));
// 	rotate_cam_y(cam, a_y);
// 	printf("apres vector x %s vector z %s\n", print_vector(cam->right), print_vector(cam->dir));
// 	printf("@@@rotation through z %f\n", a_z);
// 	printf("avant vector x %s vector y %s\n", print_vector(cam->right), print_vector(cam->up));
// 	rotate_cam_z(cam, a_z);
// 	printf("apres vector x %s vector y %s\n", print_vector(cam->right), print_vector(cam->up));
// 	printf("result x %s y %s z %s\n", print_vector(cam->right), print_vector(cam->up), print_vector(cam->up));
// }
