/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:44 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/14 22:46:33 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "debug.h"

static t_vector	*ft_get_ray_vector(t_win *win, double x, double y)
{
	t_vector	*ray;
	t_vector	*cam;
	t_vector	*ray_dir;

	ray = ft_vector_create(x - WIDTH / 2.0, y - HEIGTH / 2.0, 2 * WIDTH);
	cam = ft_get_cam_vector((t_cam*)(win->scene->cam->data));
	ray = ft_vector_sub(ray, cam);
	ray_dir = ft_vector_normalize(ray);
	free(ray);
	free(cam);
	return (ray_dir);
}

static void		ft_raytracing(t_win *win)
{
	int			x;
	int			y;
	t_vector	*ray_dir;
	t_vector	*cam;
	int			color;

	cam = ft_get_cam_vector((t_cam*)(win->scene->cam->data));
	x = 0;
	while (x < win->width)
	{
		y = 0;
		while (y < win->heigth)
		{
			ray_dir = ft_get_ray_vector(win, x, y);
			color = ft_get_color(win, ray_dir, cam);
			ft_put_pix_to_img(win, x, y, color);
			free(ray_dir);
			++y;
		}
		++x;
	}
	free(cam);
}

static t_win	*ft_init_win(t_scene *scene)
{
	t_win		*w;

	if ((!(w = (t_win*)malloc(sizeof(t_win)))))
		ft_ferror(ERR_MALLOC);
	if ((!(w->mlx = mlx_init())))
		ft_ferror(ERR_MLX_INIT);
	w->heigth = WIN_HEIGTH;
	w->width = WIN_WIDTH;
	w->title = WIN_TITLE;
	if ((!(w->win = mlx_new_window(w->mlx, w->width, w->heigth, w->title))))
		ft_ferror(ERR_MLX_WIN_INIT);
	if ((!(w->img = mlx_new_image(w->mlx, w->width, w->heigth))))
		ft_ferror(ERR_MLX_IMG_INIT);
	w->img_addr = mlx_get_data_addr(w->img, &w->bpp, &w->size_line, &w->endian);
	w->scene = scene;
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

t_vector		*ft_get_cam_vector(t_cam *cam)
{
	t_vector	*camera;

	camera = ft_vector_create(cam->x0, cam->y0, cam->z0);
	return (camera);
}
