/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 16:27:17 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/14 16:31:09 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	ft_get_smaller_dist(double x, double y, double z)
{
	double		det;
	double		d1;
	double		d2;

	det = pow(y, 2) - 4 * x * z;
	if (det < 0)
		return (-1);
	d1 = (-y + sqrt(det)) / 2 * x;
	d2 = (-y - sqrt(det)) / 2 * x;
	if (d1 > d2)
		return (d2);
	return (d1);
}
