/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btdatacmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 16:03:35 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/23 14:22:42 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

int		ft_btdatacmp(void *data1, void *data2, int (*f[SCN])(void *, void *))
{
	int		i;
	int		ret;

	if (!(data1 && data2 && f))
		return (0);
	i = 0;
	while (i < SCN)
	{
		if (!f[i])
			return (0);
		if ((ret = f[i](data1, data2)) != 0)
			return (ret);
		i++;
	}
	return (0);
}
