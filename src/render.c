/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:44 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/12 21:34:26 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "debug.h"
//
#include <stdio.h>

static t_vector	ft_get_ray_vector(t_win *win, double x, double y)
{
	t_vector	ray;
	t_vector	cam;

	cam.x = win->vcam->orig->x;
	cam.y = win->vcam->orig->y;
	cam.z = win->vcam->orig->z;

	ray.x = x - WIDTH / 2.0;
	ray.y = y - HEIGHT / 2.0,
	ray.z = 2 * WIDTH;
	ray = ft_vec_sub(ray, cam);
	ray = ft_vec_normalize(ray);
	return (ray);
}

/*
static t_vector	ft_get_ray_vector(t_win *win, double x, double y)
{
	t_vector	ray;
	t_vector	vp_upleft;
	t_vector	tmp;
	double		x_ind;
	double		y_ind;

	x_ind = VP_WIDTH / (double)win->width;
	y_ind = VP_HEIGHT / (double)win->height;
	vp_upleft = ft_vec_product(*win->vcam->dir, VP_DIST);
	vp_upleft = ft_vec_add(*win->vcam->orig, vp_upleft);
	tmp = ft_vec_product(*win->vcam->up, VP_HEIGHT / 2.0);
	vp_upleft = ft_vec_add(tmp, vp_upleft);
	tmp = ft_vec_product(*win->vcam->right, VP_WIDTH / 2.0);
	vp_upleft = ft_vec_sub(vp_upleft, tmp);
//printf("x : %f, x_ind : %f, x * x_ind %f\n", x, x_ind, x * x_ind);
	tmp = ft_vec_product(*win->vcam->right, x * x_ind);
	ray = ft_vec_add(vp_upleft, tmp);
	tmp = ft_vec_product(*win->vcam->up, y * y_ind);
	ray = ft_vec_sub(vp_upleft, tmp);
//printf("vec.x :%f\n", ray.x);
//printf("vec.y :%f\n", ray.y);
//printf("vec.z :%f\n", ray.z);
	ray = ft_vec_normalize(ray);
	return (ray);
}
*/
static void		ft_raytracing(t_win *win)
{
	int			x;
	int			y;
	t_vector	ray;
	int			color;

	x = 0;
	while (x < win->width)
	{
		y = 0;
		while (y < win->height)
		{
			ray = ft_get_ray_vector(win, x, y);
			color = ft_get_color(win, &ray, win->vcam->orig);
			ft_put_pix_to_img(win, x, y, color);
			++y;
		}
		++x;
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
	t_vcam		*vcam;

	if ((!(vcam = (t_vcam*)malloc(sizeof(t_vcam)))))
		ft_ferror(ERR_MALLOC);
	vcam->orig = ft_vec_create(cam->x0, cam->y0, cam->z0);
	vcam->right = ft_vec_create(1, 0, 0);
	vcam->up = ft_vec_create(0, 1, 0);
	vcam->dir = ft_vec_create(0, 0, 1);
	return (vcam);
}
