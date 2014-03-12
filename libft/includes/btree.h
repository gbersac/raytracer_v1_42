/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 18:22:15 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/10 14:50:44 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H
# define SCN 5

typedef struct			s_node
{
	void				*data;
	struct s_node		*right;
	struct s_node		*left;
}						t_node;

typedef int (*t_srtft)(void *, void *);

t_node	*ft_btaddnode(t_node **btree, void *key, int (*f[SCN])(void *, void *));
t_node	*ft_btinitnode(void *data);
int		ft_btcountnode(t_node *tree);
int		ft_btdatacmp(void *data1, void *data2, int (*f[SCN])(void *, void *));
void	ft_btputinfixe(t_node *tree, int *options);
void	ft_btclear(t_node **tree);

#endif /* !BTREE_H */
