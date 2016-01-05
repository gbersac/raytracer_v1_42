/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 18:04:01 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/26 19:57:48 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "load_file.h"

t_cylinder		*ft_init_cylinder(void)
{
	t_cylinder	*new;

	if ((new = (t_cylinder*)malloc(sizeof(t_cylinder))) == NULL)
		return (NULL);
	new->origin = (t_vector*)malloc(sizeof(t_vector));
	new->rotation = (t_vector*)malloc(sizeof(t_vector));
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
	else if (ft_strequ(tok1->value, "rotation"))
	{
		x = &(((t_cylinder*)(prim->data))->rotation->x);
		y = &(((t_cylinder*)(prim->data))->rotation->y);
		z = &(((t_cylinder*)(prim->data))->rotation->z);
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
