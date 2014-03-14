/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 22:51:09 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/14 18:40:02 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"

static t_cone	*ft_init_cone(void)
{
	t_cone	*cone;

	if ((!(cone = (t_cone*)malloc(sizeof(t_cone)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(cone, sizeof(t_cone));
	return (cone);
}

static void		ft_update_cone(t_prim *prim, t_token *tok1, t_token *tok2)
{
	double		*x;
	double		*y;
	double		*z;

	if (ft_strequ(tok1->value, "name"))
		prim->name = ft_strdup(tok2->value);
	else if (ft_strequ(tok1->value, "origin"))
	{
		x = &(((t_cone*)(prim->data))->x0);
		y = &(((t_cone*)(prim->data))->y0);
		z = &(((t_cone*)(prim->data))->z0);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "rotation"))
	{
		x = &(((t_cone*)(prim->data))->rot_x);
		y = &(((t_cone*)(prim->data))->rot_y);
		z = &(((t_cone*)(prim->data))->rot_z);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "angle"))
		((t_cone*)(prim->data))->angle = ft_atoi(tok2->value);
	else if (ft_strequ(tok1->value, "color"))
		((t_cone*)(prim->data))->color = ft_atoi(tok2->value);
}

t_prim			*ft_parse_cone(t_list **tokens)
{
	t_prim		*prim;
	t_token		*token;
	t_token		*token2;

	prim = ft_init_prim(CONE);
	prim->data = ft_init_cone();
	while (*tokens && ((t_token*)((*tokens)->data))->type != PRIM_TYPE)
	{
		token = (t_token*)ft_listpop(tokens);
		if (!token || token->type != PRIM_NAME)
			ft_ferror(ERR_SYN);
		token2 = (t_token*)ft_listpop(tokens);
		if (!token2 || token2->type != PRIM_VALUE)
			ft_ferror(ERR_SYN);
		ft_update_cone(prim, token, token2);
		ft_free_token(&token);
		ft_free_token(&token2);
	}
	return (prim);
}

double			ft_inter_cone(t_vector *r, t_vector *c, void *data)
{
	double		x;
	double		y;
	double		z;
	t_cone		*p;
	p = (t_cone*)data;
/*
	x = pow(r->x, 2) * p->angle + pow(r->z, 2) * p->angle - pow(r->y, 2);
	y = 2 * ((r->x * (c->x - p->x0) * p->angle)
		+ (r->z * (c->z - p->z0) * p->angle)
		- (r->y * (c->y - p->y0)));
	z = pow(c->x - p->x0, 2) * p->angle
		+ pow(c->z - p->z0, 2) * p->angle
		- pow(c->y - p->y0, 2);
*/
	x = pow(r->x, 2) - pow(r->y, 2) * pow(p->angle, 2) + pow(r->z, 2);
	return (ft_get_smaller_dist(x, y, z));
}
