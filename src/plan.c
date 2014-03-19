/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:54 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/19 20:15:05 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "rotation.h"
#include "load_file.h"
//
#include <stdio.h>

static t_plan	*ft_init_plan(void)
{
	t_plan	*plan;

	if ((!(plan = (t_plan*)malloc(sizeof(t_plan)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(plan, sizeof(t_plan));
	return (plan);
}

static t_vector	ft_get_normal(double x_rot, double y_rot, double z_rot)
{
	t_vector		n;
	t_rotate_arg	arg;

	arg.a_x = x_rot;
	arg.a_y = y_rot;
	arg.a_z = z_rot;
	init_rotation_trigo(&arg);
	n.x = 0;
	n.y = 1;
	n.z = 0;
	rotate_vector(&n, &arg);
	printf("vector normal au plan %s\n", print_vector(&n));
	return (n);
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
	t_plan		*p;

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
	p = (t_plan*)(prim->data);
	p->normal = ft_get_normal(p->rot_x, p->rot_y, p->rot_z);
	printf("vector normal plan %s\n", print_vector(&p->normal));
	return (prim);
}

double			ft_inter_plan(t_vector *r, t_vector *c, void *data)
{
	t_plan		*p;
	t_vector	n;
	double		d;
	double		a;
	double		b;

	p = (t_plan*)data;
	n = p->normal;
	d = -(n.x * p->x0 + n.y * p->y0 + n.z * p->z0);
	a = n.x * (c->x - p->x0) + n.y * (c->y - p->y0) + n.z * (c->z - p->z0) + d;
	b = n.x * r->x + n.y * r->y + n.z * r->z;

	// printf("vector normal plan %s\n", print_vector(&p->normal));
	return (-(a / b));
}
