/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 22:32:00 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/19 18:23:52 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "debug.h"
//
#include <stdio.h>

static t_inter	ft_get_inter_func(t_prim_type type)
{
	t_inter		f;

	f = NULL;
	if (type == SPHERE)
		f = ft_inter_sphere;
	else if (type == PLAN)
		f = ft_inter_plan;
	else if (type == CYLINDER)
		f = ft_inter_cylinder;
	else if (type == CONE)
		f = ft_inter_cone;
	else
		ft_ferror("Error : No function found for this primitive.");
	return (f);
}

int				ft_get_color_pritive(t_prim *data)
{
	int		to_return;

	if (data == NULL || data->data == NULL)
		return (0);
	to_return = 0;
	if (data->type == SPHERE)
		to_return = ((t_sphere*)data->data)->color;
	else if (data->type == PLAN)
		to_return = ((t_plan*)data->data)->color;
	else if (data->type == CYLINDER)
		to_return = ((t_cylinder*)data->data)->color;
	else if (data->type == CONE)
		to_return = ((t_cone*)data->data)->color;
	return (to_return);
}

int				ft_get_color(t_win *win, t_vector *ray, t_vector *cam)
{
	int		color;
	int		i;
	double	tmp_d;
	double	short_d;
	t_inter	f;

	short_d = -1;
	color = COLOR_BACKGROUND;
	i = 0;
	while (win->scene->primitives[i])
	{
		f = ft_get_inter_func(win->scene->primitives[i]->type);
		tmp_d = f(ray, cam, (win->scene->primitives[i]->data));
		if ((tmp_d >= 0 && tmp_d < short_d) || (short_d == -1 && tmp_d >= 0))
		{
			short_d = tmp_d;
			color = ft_get_color_pritive(win->scene->primitives[i]);
		}
		++i;
	}
	return (color);
}
