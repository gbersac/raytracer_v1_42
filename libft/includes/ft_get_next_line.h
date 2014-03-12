/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 16:30:00 by rfrey             #+#    #+#             */
/*   Updated: 2014/01/13 01:13:01 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 256
# define MAX_FD_NBR 10

int				ft_get_next_line(int const fd, char **line);

#endif /* !GET_NEXT_LINE_H */
