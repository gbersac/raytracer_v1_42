/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:42:15 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/19 18:41:20 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "ft_get_next_line.h"
# include "list.h"
# include "error.h"
# include "vector.h"
# include "primitives.h"
# define WIN_TITLE			"RTv1"
# define WIN_WIDTH			1600
# define WIN_HEIGHT			1200
# define KEY_ESC			65307
# define COLOR_BACKGROUND	0x000000
# define VP_DIST			1.0
# define VP_HEIGHT			0.35
# define VP_WIDTH			0.5
# define X_RATIO			VP_WIDTH / (double)WIN_WIDTH
# define Y_RATIO			VP_HEIGHT / (double)WIN_HEIGHT
# define PI					3.14159265359

typedef double(*t_inter)(t_vector *ray, t_vector *cam, void *data);

typedef struct		s_vcam
{
	t_vector		*orig;
	t_vector		*dir; /*z*/
	t_vector		*up; /*y*/
	t_vector		*right; /*x*/
}					t_vcam;

typedef struct		s_scene
{
	t_prim			*cam;
	t_prim			*light;
	t_prim			**primitives;
}					t_scene;

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	char			*title;
	void			*img;
	char			*img_addr;
	int				bpp;
	int				size_line;
	int				endian;
	t_scene			*scene;
	t_vcam			*vcam;
}					t_win;

void		ft_ferror(char *message);
void		ft_render_scene(t_scene *scene);
void		ft_free_prim(t_prim *prim);
void		ft_free_scene(t_scene *scene);
void		ft_put_pix_to_img(t_win *win, int x, int y, int color);
void		ft_quit(t_win *win);
void		ft_free_win(t_win *win);
int			ft_key_handle(int key, t_win *win);
int			ft_put_image(t_win *win);
t_vector	ft_get_start_ray(t_win *win);
t_vcam		*ft_get_cam_vector(t_cam *cam);
int			ft_get_color(t_win *win, t_vector *ray, t_vector *cam);
double		ft_get_smaller_dist(double x, double y, double z);
void		rotate_cam(t_vcam *cam, double a_x, double a_y, double a_z);

/*intersection primitive*/
double		ft_inter_sphere(t_vector *r, t_vector *c, void *data);
double		ft_inter_cone(t_vector *r, t_vector *c, void *data);
double		ft_inter_plan(t_vector *r, t_vector *c, void *data);
double		ft_inter_cylinder(t_vector *dir, t_vector *origin, void *data);

#endif /* !RTV1_H */
