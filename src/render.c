/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:44 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/19 19:24:14 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "debug.h"
//
#include <stdio.h>

static void		ft_raytracing(t_win *win)
{
	int			x;
	int			y;
	int			color;
	t_vector	ray;
	t_vector	n_ray;

	ray = ft_get_start_ray(win);
	y = 0;
	while (y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			ray = ft_vec_add(ray, ft_vec_product(*win->vcam->right, X_RATIO));
			n_ray = ft_vec_normalize(ray);
			color = ft_get_color(win, &n_ray, win->vcam->orig);
			ft_put_pix_to_img(win, x, y, color);
			++x;
		}
		ray = ft_vec_sub(ray, ft_vec_product(*win->vcam->right, x * X_RATIO));
		ray = ft_vec_sub(ray, ft_vec_product(*win->vcam->up, Y_RATIO));
		++y;
	}
}

static t_win	*ft_init_win(t_scene *scene)
{
	t_win		*w;

	if ((!(w = (t_win*)malloc(sizeof(t_win)))))
		ft_ferror(ERR_MALLOC);
	if ((!(w->mlx = mlx_init())))
		ft_ferror(ERR_MLX_INIT);
	w->height = WIN_HEIGHT;
	w->width = WIN_WIDTH;
	w->title = WIN_TITLE;
	if ((!(w->win = mlx_new_window(w->mlx, w->width, w->height, w->title))))
		ft_ferror(ERR_MLX_WIN_INIT);
	if ((!(w->img = mlx_new_image(w->mlx, w->width, w->height))))
		ft_ferror(ERR_MLX_IMG_INIT);
	w->img_addr = mlx_get_data_addr(w->img, &w->bpp, &w->size_line, &w->endian);
	w->scene = scene;
	w->vcam = ft_get_cam_vector((t_cam*)(w->scene->cam->data));
	return (w);
}

void			ft_render_scene(t_scene *scene)
{
	t_win		*win;

	win = ft_init_win(scene);
	ft_raytracing(win);
	mlx_key_hook(win->win, ft_key_handle, win);
	mlx_expose_hook(win->win, ft_put_image, win);
	mlx_loop(win->mlx);
}

t_vcam			*ft_get_cam_vector(t_cam *cam)
{
	static t_vcam		*vcam = NULL;

	if (vcam == NULL && cam != NULL)
	{
		if ((!(vcam = (t_vcam*)malloc(sizeof(t_vcam)))))
			ft_ferror(ERR_MALLOC);
		vcam->orig = ft_vec_create(cam->x0, cam->y0, cam->z0);
		vcam->right = ft_vec_create(1, 0, 0);
		vcam->up = ft_vec_create(0, 1, 0);
		vcam->dir = ft_vec_create(0, 0, 1);
		rotate_cam(vcam, cam->rot_x, cam->rot_y, cam->rot_z);
	}
	return (vcam);
}
