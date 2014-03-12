/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 21:49:40 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/12 21:57:25 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		ft_put_pix_to_img(t_win *win, int x, int y, int color)
{
	char	*pix_addr;
	int		opp;
	int		i;

	opp = win->bpp / 8;
	i = opp;
	pix_addr = win->img_addr + y * win->size_line + x * opp;
	color = mlx_get_color_value(win->mlx, color);
	while (i)
	{
		pix_addr[3] = (unsigned char)0x00;
		pix_addr[2] = (unsigned char)((color / 65536) % 256);
		pix_addr[1] = (unsigned char)((color / 256) % 256);
		pix_addr[0] = (unsigned char)(color % 256);
		--i;
	}
}
