/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 23:47:48 by rfrey             #+#    #+#             */
/*   Updated: 2014/03/14 14:57:39 by gbersac          ###   ########.fr       */
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

t_vector	*ft_vec_create(double x, double y, double z);
t_vector	ft_vec_add(t_vector v1, t_vector v2);
t_vector	ft_vec_sub(t_vector v1, t_vector v2);
double		ft_vec_norm(t_vector v);
t_vector	ft_vec_normalize(t_vector v);
double		ft_vec_dot_product(t_vector v1, t_vector v2);
t_vector	ft_vec_cross_product(t_vector v1, t_vector v2);
t_vector	ft_vec_product(t_vector v1, double n);

#endif /* !VECTOR_H */
