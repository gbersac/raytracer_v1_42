/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 16:27:17 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/14 23:08:42 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	ft_get_smaller_dist(double x, double y, double z)
{
	double		d;
	double		d1;
	double		d2;

	d = pow(y, 2) - 4 * x * z;
	if (d < 0)
		return (-1);
	d1 = (-y + sqrt(d)) / 2.0 * x;
	d2 = (-y - sqrt(d)) / 2.0 * x;
	if (d1 > d2)
		return (d2);
	return (d1);
}
