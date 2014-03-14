/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 14:42:45 by gbersac           #+#    #+#             */
/*   Updated: 2014/03/14 18:23:35 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

#include "vector.h"

typedef struct	s_rotate_arg
{
	/*vector which have to be rotate*/
	t_vector	*v_x;
	t_vector	*v_y;
	t_vector	*v_z;
	/*rotation angle according to the x, y, z angle*/
	double		a_x;
	double		a_y;
	double		a_z;
	/*calcul trigo*/
	double		cosx;
	double		cosy;
	double		cosz;
	double		sinx;
	double		siny;
	double		sinz;
}				t_rotate_arg;

#endif /*ROTATION_H*/
