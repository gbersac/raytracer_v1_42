/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:54 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/13 17:07:55 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"

static t_plan	*ft_init_plan(void)
{
	t_plan	*plan;

	if ((!(plan = (t_plan*)malloc(sizeof(t_plan)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(plan, sizeof(t_plan));
	return (plan);
}

static void		ft_update_plan(t_prim *prim, t_token *tok1, t_token *tok2)
{
	double		*x;
	double		*y;
	double		*z;

	if (ft_strequ(tok1->value, "name"))
		prim->name = ft_strdup(tok2->value);
	else if (ft_strequ(tok1->value, "origin"))
	{
		x = &(((t_plan*)(prim->data))->x0);
		y = &(((t_plan*)(prim->data))->y0);
		z = &(((t_plan*)(prim->data))->z0);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "rotation"))
	{
		x = &(((t_plan*)(prim->data))->rot_x);
		y = &(((t_plan*)(prim->data))->rot_y);
		z = &(((t_plan*)(prim->data))->rot_z);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "color"))
		((t_plan*)(prim->data))->color = ft_atoi(tok2->value);
}

t_prim			*ft_parse_plan(t_list **tokens)
{
	t_prim		*prim;
	t_token		*token;
	t_token		*token2;

	prim = ft_init_prim(PLAN);
	prim->data = ft_init_plan();
	while (*tokens && ((t_token*)((*tokens)->data))->type != PRIM_TYPE)
	{
		token = (t_token*)ft_listpop(tokens);
		if (!token || token->type != PRIM_NAME)
			ft_ferror(ERR_SYN);
		token2 = (t_token*)ft_listpop(tokens);
		if (!token2 || token2->type != PRIM_VALUE)
			ft_ferror(ERR_SYN);
		ft_update_plan(prim, token, token2);
		ft_free_token(&token);
		ft_free_token(&token2);
	}
	return (prim);
}
/*
static t_vector	*ft_get_normal(t_plan *plan)
{
	t_vector	*ret;

	++plan; // useless
	ret = ft_vec_create(0, 1, 0);
	return (ret);
}
*/
double			ft_inter_plan(t_vector *r, t_vector *c, void *data)
{
	t_vector	*n;
	t_plan		*p;
	double		a;
	double		b;
	double		t;

	p = (t_plan*)data;
	n = ft_get_normal(p);
	a = n->x * (c->x - p->x0) + n->y * (c->y - p->y0);
	t_vector *n2 = ft_vec_sub(ft_vec_create(0, 0, 0), n);
	a = a + n->z * (c->z - p->z0) + ft_vec_dot_product(n2, ft_vec_create(p->x0, p->y0, p->z0)); // D = 0    what is D ???
	b = n->x * r->x + n->y * r->y + n->z * r->z;
	t = - (a / b);
	if ( t > 0)
		return (t);
	return (-1);
}
