/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:42:39 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/26 19:55:28 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_FILE_H
# define LOAD_FILE_H

typedef t_prim		*(*t_parse_prim)(t_list **);

typedef struct		s_parse_prim_array
{
	t_prim_type		type;
	t_parse_prim	func;
}					t_parse_prim_array;

typedef enum		e_token_type
{
	PRIM_TYPE, PRIM_NAME, PRIM_VALUE
}					t_token_type;

typedef struct		s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

t_scene				*ft_load_scene(char *filepath);
t_scene				*ft_parse_scene(t_list **tokens);
void				ft_set_coord(char *str, double *x, double *y, double *z);
void				ft_free_token(t_token **token);
t_prim				*ft_init_prim(int type);
t_prim				*ft_parse_light(t_list **tokens);
t_prim				*ft_parse_cam(t_list **tokens);
t_prim				*ft_parse_sphere(t_list **tokens);
t_prim				*ft_parse_plan(t_list **tokens);
t_prim				*ft_parse_cone(t_list **tokens);
t_prim				*ft_parse_cylinder(t_list **tokens);

#endif
