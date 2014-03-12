/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:15:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/12 21:29:34 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h>

char	*print_vector(t_vector *vect)
{
	char *str = (char*) malloc(sizeof(char) * 100);
	sprintf(str, "x:%f y:%f z:%f\n", vect->x, vect->y, vect->z);
	return (str);
}

static void	convert_to_radian(double angle)
{
	return (angle / 180 * PI);
}

static void	rotate_single_x(t_vector *v, double sine, double cosine)
{
	double	buf_y;
	double	buf_z;

	buf_y = v->y;
	buf_z = v->z;
	v->y = buf_y * cosine - buf_z * sine;
	v->z = buf_y * sine - buf_z * cosine;
}

static void	rotate_cam_x(t_vcam *cam, double angle)
{
	double		sine;
	double		cosine;

	sine = sin(angle);
	cosine = cos(angle);
	rotate_single_x(cam->up, sine, cosine);
	rotate_single_x(cam->dir, sine, cosine);
}

void		rotate_cam(t_vcam *cam, double a_x, double a_y, double a_z)
{
	a_x = ;
	printf("avant vector y %s vecotr z %s\n", print_vector(cam->up), print_vector(cam->dir));
	rotate_cam_x(cam, a_x);
	printf("apres vector y %s vecotr z %s\n", print_vector(cam->up), print_vector(cam->dir));
	a_y = 0;
	a_z = 0;
}
