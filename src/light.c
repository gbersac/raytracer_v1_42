/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:40:55 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/26 19:58:38 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "load_file.h"

static void		ft_update_light(t_prim *prim, t_token *tok1, t_token *tok2)
{
	double		*x;
	double		*y;
	double		*z;

	if (ft_strequ(tok1->value, "name"))
		prim->name = ft_strdup(tok2->value);
	else if (ft_strequ(tok1->value, "origin"))
	{
		x = &(((t_light*)(prim->data))->x0);
		y = &(((t_light*)(prim->data))->y0);
		z = &(((t_light*)(prim->data))->z0);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "rotation"))
	{
		x = &(((t_light*)(prim->data))->rot_x);
		y = &(((t_light*)(prim->data))->rot_y);
		z = &(((t_light*)(prim->data))->rot_z);
		ft_set_coord(tok2->value, x, y, z);
	}
}

static t_light	*ft_init_light(void)
{
	t_light		*light;

	if ((!(light = (t_light*)malloc(sizeof(t_light)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(light, sizeof(t_light));
	return (light);
}

t_prim			*ft_parse_light(t_list **tokens)
{
	t_prim		*prim;
	t_token		*token;
	t_token		*token2;

	prim = ft_init_prim(LIGHT);
	prim->data = ft_init_light();
	while (*tokens && ((t_token*)((*tokens)->data))->type != PRIM_TYPE)
	{
		token = (t_token*)ft_listpop(tokens);
		if (!token || token->type != PRIM_NAME)
			ft_ferror(ERR_SYN);
		token2 = (t_token*)ft_listpop(tokens);
		if (!token2 || token2->type != PRIM_VALUE)
			ft_ferror(ERR_SYN);
		ft_update_light(prim, token, token2);
		ft_free_token(&token);
		ft_free_token(&token2);
	}
	return (prim);
}
