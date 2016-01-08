/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 21:47:06 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/26 19:59:46 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		ft_get_start_ray(t_win *win)
{
	t_vector	r;

	r = ft_vec_product(*win->vcam->dir, VP_DIST);
	r = ft_vec_add(r, ft_vec_product(*win->vcam->up, VP_HEIGHT / 2.0));
	r = ft_vec_sub(r, ft_vec_product(*win->vcam->right, VP_WIDTH / 2.0));
	return (r);
}
