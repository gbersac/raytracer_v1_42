/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 23:46:48 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/12 19:40:09 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vector.h"

t_vector	*ft_vec_create(double x, double y, double z)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector	ft_vec_add(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vector	ft_vec_sub(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

double		ft_vec_norm(t_vector v)
{
	double		res;

	res = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (res);
}

t_vector	ft_vec_normalize(t_vector v)
{
	double		norm;
	t_vector	res;

	norm = ft_vec_norm(v);
	res.x = v.x / norm;
	res.y = v.y / norm;
	res.z = v.z / norm;
	return (res);
}
