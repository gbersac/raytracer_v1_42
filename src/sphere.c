/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:54 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/13 22:40:18 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"

static double	ft_dist_sphere(double x, double y, double z)
{
	double		det;
	double		d1;
	double		d2;

	det = pow(y, 2) - 4 * x * z;
	if (det < 0)
		return (-1);
	d1 = (-y + sqrt(det)) / 2 * x;
	d2 = (-y - sqrt(det)) / 2 * x;
	if (d1 > d2)
		return (d2);
	return (d1);
}

static t_sphere	*ft_init_sphere(void)
{
	t_sphere	*sphere;

	if ((!(sphere = (t_sphere*)malloc(sizeof(t_sphere)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(sphere, sizeof(t_sphere));
	return (sphere);
}

static void		ft_update_sphere(t_prim *prim, t_token *tok1, t_token *tok2)
{
	double		*x;
	double		*y;
	double		*z;

	if (ft_strequ(tok1->value, "name"))
		prim->name = ft_strdup(tok2->value);
	else if (ft_strequ(tok1->value, "origin"))
	{
		x = &(((t_sphere*)(prim->data))->x0);
		y = &(((t_sphere*)(prim->data))->y0);
		z = &(((t_sphere*)(prim->data))->z0);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "rotation"))
	{
		x = &(((t_sphere*)(prim->data))->rot_x);
		y = &(((t_sphere*)(prim->data))->rot_y);
		z = &(((t_sphere*)(prim->data))->rot_z);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "rayon"))
		((t_sphere*)(prim->data))->rayon = ft_atoi(tok2->value);
	else if (ft_strequ(tok1->value, "color"))
		((t_sphere*)(prim->data))->color = ft_atoi(tok2->value);
}

t_prim			*ft_parse_sphere(t_list **tokens)
{
	t_prim		*prim;
	t_token		*token;
	t_token		*token2;

	prim = ft_init_prim(SPHERE);
	prim->data = ft_init_sphere();
	while (*tokens && ((t_token*)((*tokens)->data))->type != PRIM_TYPE)
	{
		token = (t_token*)ft_listpop(tokens);
		if (!token || token->type != PRIM_NAME)
			ft_ferror(ERR_SYN);
		token2 = (t_token*)ft_listpop(tokens);
		if (!token2 || token2->type != PRIM_VALUE)
			ft_ferror(ERR_SYN);
		ft_update_sphere(prim, token, token2);
		ft_free_token(&token);
		ft_free_token(&token2);
	}
	return (prim);
}

double			ft_inter_sphere(t_vector *r, t_vector *c, void *data)
{
	double		x;
	double		y;
	double		z;
	t_sphere	*s;

	s = (t_sphere*)data;
	x = pow(r->x, 2) + pow(r->y, 2) + pow(r->z, 2);
	y = r->x * (c->x - s->x0) + r->y * (c->y - s->y0) + r->z * (c->z - s->z0);
	y *= 2;
	z = pow(c->x - s->x0, 2) + pow(c->y - s->y0, 2) + pow(c->z - s->z0, 2);
	z -= pow(s->rayon, 2);
	return (ft_dist_sphere(x, y, z));
}
