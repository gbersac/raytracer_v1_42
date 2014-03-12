/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:14 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/12 21:44:05 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "debug.h"
#include "load_file.h"

int			main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		ft_ferror(ERR_PARAM);
	else
	{
		scene = ft_load_scene(argv[1]);
		ft_print_scene_infos(scene);
		ft_render_scene(scene);
	}
	return (0);
}

void		ft_quit(t_win *win)
{
	ft_free_win(win);
	exit(EXIT_SUCCESS);
}

void		ft_ferror(char *message)
{
	if (!message)
		message = ERR_UNDEF;
	ft_putendl(message);
	exit(EXIT_FAILURE);
}
