/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:42:22 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/26 19:52:33 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "RTv1.h"
# include "libft.h"

void	ft_print_scene_infos(t_scene *scene);
void	ft_print_tokens(t_list *tokens);
void	ft_print_sphere_infos(t_prim *sphere);
void	ft_print_light_infos(t_prim *light);
void	ft_print_cam_infos(t_prim *cam);
void	ft_put_vector(t_vector *v);

#endif
