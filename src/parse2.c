/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:36 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/12 20:41:38 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"

t_prim		*ft_init_prim(int type)
{
	t_prim	*prim;

	if ((!(prim = (t_prim*)malloc(sizeof(t_prim)))))
		ft_ferror(ERR_MALLOC);
	ft_bzero(prim, sizeof(t_prim));
	prim->type = type;
	return (prim);
}

void		ft_set_coord(char *str, double *x, double *y, double *z)
{
	*x = ft_atoi(str);
	while (*str && *str != ',')
		++str;
	++str;
	*y = ft_atoi(str);
	while (*str && *str != ',')
		++str;
	++str;
	*z = ft_atoi(str);
}

void		ft_free_token(t_token **token)
{
	free((*token)->value);
	(*token)->value = NULL;
	free(*token);
	*token = NULL;
}
