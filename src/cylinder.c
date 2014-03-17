/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 18:04:01 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/17 16:41:08 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"
#include <stdio.h>

static t_cylinder	*ft_init_cylinder(void)
{
	t_cylinder	*new;

	if ((new = (t_cylinder*)malloc(sizeof(t_cylinder))) == NULL)
		return (NULL);
	new->origin = (t_vector*) malloc(sizeof(t_vector));;
	new->axis = (t_vector*) malloc(sizeof(t_vector));;
	new->rayon = 0;
	return (new);
}

static void		ft_update_cylinder(t_prim *prim, t_token *tok1, t_token *tok2)
{
	double		*x;
	double		*y;
	double		*z;

	if (ft_strequ(tok1->value, "name"))
		prim->name = ft_strdup(tok2->value);
	else if (ft_strequ(tok1->value, "origin"))
	{
		x = &(((t_cylinder*)(prim->data))->origin->x);
		y = &(((t_cylinder*)(prim->data))->origin->y);
		z = &(((t_cylinder*)(prim->data))->origin->z);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "axis"))
	{
		x = &(((t_cylinder*)(prim->data))->axis->x);
		y = &(((t_cylinder*)(prim->data))->axis->y);
		z = &(((t_cylinder*)(prim->data))->axis->z);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "rayon"))
		((t_cylinder*)(prim->data))->rayon = ft_atoi(tok2->value);
	else if (ft_strequ(tok1->value, "color"))
		((t_cylinder*)(prim->data))->color = ft_atoi(tok2->value);
}

t_prim			*ft_parse_cylinder(t_list **tokens)
{
	t_prim		*prim;
	t_token		*token;
	t_token		*token2;

printf("ft_parse_cylinder\n");
	prim = ft_init_prim(CYLINDER);
	prim->data = ft_init_cylinder();
	while (*tokens && ((t_token*)((*tokens)->data))->type != PRIM_TYPE)
	{
		token = (t_token*)ft_listpop(tokens);
		if (!token || token->type != PRIM_NAME)
			ft_ferror(ERR_SYN);
		token2 = (t_token*)ft_listpop(tokens);
		if (!token2 || token2->type != PRIM_VALUE)
			ft_ferror(ERR_SYN);
		ft_update_cylinder(prim, token, token2);
		ft_free_token(&token);
		ft_free_token(&token2);
	}
	return (prim);
}

/*
** Must return the distance of the intersection between the camera c and the
** rayon r.
*/
double			ft_inter_cylinder(t_vector *dir, t_vector *origin,
									void *data)
{
	double		a;
	double		b;
	double		c;
	t_cylinder	*cylinder;

	if (dir == NULL || origin == NULL || data == NULL)
		return (0);
	cylinder = (t_cylinder*)data;
	a = pow(dir->x, 2) + pow(dir->z, 2);
	b = 2 * ((dir->x * (origin->x - cylinder->origin->x))
		+ (dir->z * (origin->z - cylinder->origin->z)));
	c = pow(origin->x - cylinder->origin->x, 2)
		+ pow(origin->z - cylinder->origin->z, 2)
		- pow(cylinder->rayon, 2);
	return (ft_get_smaller_dist(a, b, c));
}
