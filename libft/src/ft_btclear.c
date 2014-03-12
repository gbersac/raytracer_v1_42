/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btclear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/09 23:52:09 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/12 16:36:14 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "btree.h"

void	ft_btclear(t_node **tree)
{
	if (!tree)
		return ;
	if (!*tree)
		return ;
	ft_btclear(&((*tree)->left));
	ft_btclear(&((*tree)->right));
	free(*tree);
	*tree = NULL;
}
