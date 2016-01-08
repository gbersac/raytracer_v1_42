/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 21:37:59 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/26 19:58:07 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_free_win(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	ft_free_scene(win->scene);
	free(win);
}

void		ft_free_scene(t_scene *scene)
{
	int		i;

	if (scene->cam)
		ft_free_prim(scene->cam);
	if (scene->light)
		ft_free_prim(scene->light);
	i = 0;
	while (scene->primitives[i])
	{
		ft_free_prim(scene->primitives[i]);
		++i;
	}
	free(scene->primitives);
	free(scene);
}

void		ft_free_prim(t_prim *prim)
{
	if (prim->name)
		free(prim->name);
	if (prim->data)
		free(prim->data);
	free(prim);
}
