/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 23:46:48 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/13 15:20:56 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vector.h"

t_vector	*ft_vector_create(double x, double y, double z)
{
	t_vector	*vector;

	if ((!(vector = (t_vector*)malloc(sizeof(t_vector)))))
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector	*ft_vector_add(t_vector *v1, t_vector *v2)
{
	t_vector	*res;

	res = ft_vector_create(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (res);
}

t_vector	*ft_vector_sub(t_vector *v1, t_vector *v2)
{
	t_vector	*res;

	res = ft_vector_create(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (res);
}

double		ft_vector_norm(t_vector *v)
{
	double		res;

	res = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
	return (res);
}

t_vector	*ft_vector_normalize(t_vector *v)
{
	double		norm;
	t_vector	*res;

	norm = ft_vector_norm(v);
	res = ft_vector_create(v->x / norm, v->y / norm, v->z / norm);
	return (res);
}
