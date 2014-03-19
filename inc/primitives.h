/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 23:00:35 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/19 20:02:50 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

typedef enum		e_prim_type
{
	SPHERE,
	CAM,
	LIGHT,
	PLAN,
	CYLINDER,
	CONE
}					t_prim_type;

typedef struct		s_light
{
	double			x0;
	double			y0;
	double			z0;
	double			rot_x;
	double			rot_y;
	double			rot_z;
}					t_light;

typedef struct		s_camera
{
	double			x0;
	double			y0;
	double			z0;
	double			rot_x;
	double			rot_y;
	double			rot_z;
}					t_cam;

typedef struct		s_plan
{
	double			x0;
	double			y0;
	double			z0;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	int				color;
	t_vector		normal;
}					t_plan;

typedef struct		s_cylinder
{
	t_vector		*origin;
	t_vector		*rotation;
	double			rayon;
	int				color;
}					t_cylinder;

typedef struct		s_sphere
{
	double			x0;
	double			y0;
	double			z0;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	int				color;
	double			rayon;
}					t_sphere;

typedef struct		s_cone
{
	double			x0;
	double			y0;
	double			z0;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	int				color;
	double			angle;
}					t_cone;

typedef struct		s_primitive
{
	t_prim_type		type;
	char			*name;
	void			*data;
}					t_prim;

#endif /* !PRIMITIVES_H */
