/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btcountnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/06 15:59:33 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/12 16:25:16 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

int		ft_btcountnode(t_node *tree)
{
	if (!tree)
		return (0);
	else
		return (1 + ft_btcountnode(tree->left) + ft_btcountnode(tree->right));
}
