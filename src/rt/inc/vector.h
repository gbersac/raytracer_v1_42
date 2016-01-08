/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 23:47:48 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/26 19:56:14 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

t_vector			*ft_vec_create(double x, double y, double z);
t_vector			ft_vec_add(t_vector v1, t_vector v2);
t_vector			ft_vec_sub(t_vector v1, t_vector v2);
double				ft_vec_norm(t_vector v);
t_vector			ft_vec_normalize(t_vector v);
double				ft_vec_dot_product(t_vector v1, t_vector v2);
t_vector			ft_vec_cross_product(t_vector v1, t_vector v2);
t_vector			ft_vec_product(t_vector v1, double n);
char				*print_vector(t_vector *vect);
t_vector			*ft_vec_cpy(t_vector *vec);
t_vector			invert_vector(t_vector *vec);

#endif
