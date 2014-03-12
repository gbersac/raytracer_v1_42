/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btaddnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 18:33:36 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/10 15:29:52 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "btree.h"

t_node	*ft_btaddnode(t_node **btree, void *data, t_srtft *sf)
{
	t_node		*new_node;
	t_node		*current_node;
	t_node		*tmp_node;

	new_node = ft_btinitnode(data);
	if (!(btree && sf && new_node))
		return (NULL);
	if (!*btree)
		return (*btree = new_node);
	current_node = *btree;
	while (current_node)
	{
		tmp_node = current_node;
		if (ft_btdatacmp(data, current_node->data, sf) > 0)
		{
			current_node = current_node->right;
			if (!current_node)
				tmp_node->right = new_node;
			continue ;
		}
		current_node = current_node->left;
		if (!current_node)
			tmp_node->left = new_node;
	}
	return (*btree);
}
