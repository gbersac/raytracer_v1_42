/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 14:43:01 by rfrey             #+#    #+#             */
/*   Updated: 2013/11/25 20:23:25 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int				ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (*s1 == '\0' && *s2 == '\0')
		return (0);
	if (*s1 == *s2)
	{
		s1++;
		s2++;
		return (ft_strcmp(s1, s2));
	}
	return (*s1 - *s2);
}
