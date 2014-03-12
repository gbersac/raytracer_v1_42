/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:40:46 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/13 18:50:45 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"
#include "debug.h"
#include "stdio.h"

void			ft_print_scene_infos(t_scene *scene)
{
	int			i;

	printf(">>>>> DESCRIPTION DE LA SCENE <<<<<\n\n");
	printf("-----   camera    -----\n\n");
	if (scene->cam)
		ft_print_cam_infos(scene->cam);
	printf("\n-----   lumiere   -----\n\n");
	if (scene->light)
		ft_print_light_infos(scene->light);
	printf("\n----- primitives  -----\n\n");
	i = 0;
	while (scene->primitives[i])
	{
		if (scene->primitives[i]->type == SPHERE)
			ft_print_sphere_infos(scene->primitives[i]);
		printf("\n");
		++i;
	}
}

void			ft_print_tokens(t_list *tokens)
{
	t_list*		token;
	char		*type;

	printf("\n---- TOKEN_TYPE : ---- %10s ----\n\n", "TOKEN_VALUE");
	token = tokens;
	while (token)
	{
		if (((t_token*)token->data)->type == PRIM_TYPE)
			type = ">>>>> PRIM_TYPE";
		else if (((t_token*)token->data)->type == PRIM_NAME)
			type = "PRIM_NAME";
		else if (((t_token*)token->data)->type == PRIM_VALUE)
			type = "PRIM_VALUE";
		else
			type = "ERROR";
		printf("%15s : %15s\n", type, ((t_token*)token->data)->value);
		token = token->next;
	}
	printf("\n");
}

void			ft_print_sphere_infos(t_prim *sphere)
{
	t_sphere	*data;

	data = (t_sphere*)sphere->data;
	printf("SPHERE   : \"%s\"\n", sphere->name);
	printf("origine  : %7.1f, %7.1f, %7.1f\n", data->x0, data->y0, data->z0);
	printf("rotation : %7.1f, %7.1f, %7.1f\n", data->rot_x, data->rot_y, data->rot_z);
	printf("rayon    : %7.1f\n", data->rayon);
	printf("color    : %7d\n", data->color);
}

void			ft_print_cam_infos(t_prim *cam)
{
	t_cam	*data;

	data = (t_cam*)cam->data;
	printf("CAMERA   : \"%s\"\n", cam->name);
	printf("origine  : %7.1f, %7.1f, %7.1f\n", data->x0, data->y0, data->z0);
	printf("rotation : %7.1f, %7.1f, %7.1f\n", data->rot_x, data->rot_y, data->rot_z);
}

void			ft_print_light_infos(t_prim *light)
{
	t_light	*data;

	data = (t_light*)light->data;
	printf("CAMERA   : \"%s\"\n", light->name);
	printf("origine  : %7.1f, %7.1f, %7.1f\n", data->x0, data->y0, data->z0);
	printf("rotation : %7.1f, %7.1f, %7.1f\n", data->rot_x, data->rot_y, data->rot_z);
}

void			ft_put_vector(t_vector *v)
{
	printf("v.x = %10.3f\n", v->x);
	printf("v.y = %10.3f\n", v->y);
	printf("v.z = %10.3f\n", v->z);
}
