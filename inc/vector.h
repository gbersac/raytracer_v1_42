/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 23:47:48 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/13 17:07:56 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>

typedef struct		e_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

t_vector	*ft_vector_create(double x, double y, double z);
t_vector	*ft_vector_add(t_vector *v1, t_vector *v2);
t_vector	*ft_vector_sub(t_vector *v1, t_vector *v2);
double		ft_vector_norm(t_vector *v);
t_vector	*ft_vector_normalize(t_vector *v);
double		ft_vector_dot_product(t_vector *v1, t_vector *v2);
t_vector	*ft_cross_product(t_vector *v1, t_vector *v2);

#endif /* !VECTOR_H */
