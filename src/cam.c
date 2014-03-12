/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:40:37 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/12 20:40:41 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"

static void		ft_update_cam(t_prim *prim, t_token *tok1, t_token *tok2)
{
	double		*x;
	double		*y;
	double		*z;

	if (ft_strequ(tok1->value, "name"))
		prim->name = ft_strdup(tok2->value);
	else if (ft_strequ(tok1->value, "origin"))
	{
		x = &(((t_cam*)(prim->data))->x0);
		y = &(((t_cam*)(prim->data))->y0);
		z = &(((t_cam*)(prim->data))->z0);
		ft_set_coord(tok2->value, x, y, z);
	}
	else if (ft_strequ(tok1->value, "rotation"))
	{
		x = &(((t_cam*)(prim->data))->rot_x);
		y = &(((t_cam*)(prim->data))->rot_y);
		z = &(((t_cam*)(prim->data))->rot_z);
		ft_set_coord(tok2->value, x, y, z);
	}
}

static t_cam	*ft_init_cam(void)
{
	t_cam		*cam;

	if ((!(cam = (t_cam*)malloc(sizeof(t_cam)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(cam, sizeof(t_cam));
	return (cam);
}

t_prim			*ft_parse_cam(t_list **tokens)
{
	t_prim		*prim;
	t_token		*token;
	t_token		*token2;

	prim = ft_init_prim(CAM);
	prim->data = ft_init_cam();
	while (*tokens && ((t_token*)((*tokens)->data))->type != PRIM_TYPE)
	{
		token = (t_token*)ft_listpop(tokens);
		if (!token || token->type != PRIM_NAME)
			ft_ferror(ERR_SYN);
		token2 = (t_token*)ft_listpop(tokens);
		if (!token2 || token2->type != PRIM_VALUE)
			ft_ferror(ERR_SYN);
		ft_update_cam(prim, token, token2);
		ft_free_token(&token);
		ft_free_token(&token2);
	}
	return (prim);
}
