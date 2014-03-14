/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:30 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/14 16:54:14 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"

static t_parse_prim	ft_get_parse_prim_func(t_prim_type type)
{
	unsigned int			i;
	t_parse_prim_array		tab[] = {
									{CAM, ft_parse_cam},
									{LIGHT, ft_parse_light},
									{SPHERE, ft_parse_sphere},
									{PLAN, ft_parse_plan},
									{CYLINDER, ft_parse_cylinder},
									{CONE, ft_parse_cone},
									};

	i = 0;
	while (i < sizeof(tab) / sizeof(t_parse_prim_array))
	{
		if (type == tab[i].type)
			return (tab[i].func);
		++i;
	}
	return (NULL);
}

static t_parse_prim	ft_get_parse_func(char *str)
{
	if (ft_strequ(str, "sphere"))
		return (ft_get_parse_prim_func(SPHERE));
	else if (ft_strequ(str, "camera"))
		return (ft_get_parse_prim_func(CAM));
	else if (ft_strequ(str, "light"))
		return (ft_get_parse_prim_func(LIGHT));
	else if (ft_strequ(str, "plan"))
		return (ft_get_parse_prim_func(PLAN));
	else if (ft_strequ(str, "cone"))
		return (ft_get_parse_prim_func(CONE));
	else if (ft_strequ(str, "cylinder"))
		return (ft_get_parse_prim_func(CYLINDER));
	else
		return (NULL);
}

static void			ft_set_primitives_scene(t_list *prim2, t_scene *scene)
{
	int				i;
	int				size;

	size = ft_listcnt(prim2);
	if ((!(scene->primitives = (t_prim**)malloc(sizeof(t_prim*) * (size + 1)))))
		ft_ferror(ERR_MALLOC);
	i = 0;
	while (prim2)
	{
		scene->primitives[i] = (t_prim*)ft_listpop(&prim2);
		++i;
	}
	scene->primitives[i] = NULL;
}

static t_scene		*ft_get_scene(t_list **prims)
{
	t_prim			*prim;
	t_list			*prim2;
	t_scene			*scene;

	if ((!(scene = (t_scene*)malloc(sizeof(t_scene)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(scene, sizeof(t_scene));
	prim2 = NULL;
	while (*prims)
	{
		prim = (t_prim*)ft_listpop(prims);
		if (prim->type == CAM)
			scene->cam = prim;
		else if (prim->type == LIGHT)
			scene->light = prim;
		else
			ft_listpushfront(&prim2, prim);
	}
	ft_set_primitives_scene(prim2, scene);
	return (scene);
}

t_scene				*ft_parse_scene(t_list **tokens)
{
	t_token			*token;
	t_list			*prims;
	t_parse_prim	parse_func;

	prims = NULL;
	while (*tokens)
	{
		token = (t_token*)ft_listpop(tokens);
		if (token->type != PRIM_TYPE)
			ft_ferror(ft_itoa(token->type));
		parse_func = ft_get_parse_func(token->value);
		if (parse_func)
			ft_listpushfront(&prims, parse_func(tokens));
		else
			ft_ferror(ERR_UNKNOW_PRIM_TYPE);
		ft_free_token(&token);
	}
	return (ft_get_scene(&prims));
}
