/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 23:47:26 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/18 23:26:06 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
double		ft_vec_dot_product(t_vector v1, t_vector v2)
{
	double	res;

	v1 = ft_vec_normalize(v1);
	v2 = ft_vec_normalize(v2);
	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

t_vector	ft_vec_cross_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

t_vector	ft_vec_product(t_vector v1, double n)
{
	t_vector	res;

	res.x = v1.x * n;
	res.y = v1.y * n;
	res.z = v1.z * n;
	return (res);
}

char			*print_vector(t_vector *vect)
{
	char *str = (char*) malloc(sizeof(char) * 100);
	sprintf(str, "{x:%f y:%f z:%f}", vect->x, vect->y, vect->z);
	return (str);
}

t_vector	*ft_vec_cpy(t_vector *vec)
{
	t_vector	*to_return;

	if (vec == NULL)
		return (NULL);
	to_return = (t_vector*) malloc(sizeof(t_vector));
	to_return->x = vec->x;
	to_return->y = vec->y;
	to_return->z = vec->z;
	return (to_return);
}
