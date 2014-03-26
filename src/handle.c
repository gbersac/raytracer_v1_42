/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 21:34:13 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/26 19:58:15 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_key_handle(int key, t_win *win)
{
	if (key == KEY_ESC)
		ft_quit(win);
	return (0);
}

int		ft_put_image(t_win *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	return (0);
}
