/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 20:41:04 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/14 21:12:12 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "load_file.h"

static t_token	*ft_init_token(int type, char *value)
{
	t_token		*token;

	if ((!(token = (t_token*)malloc(sizeof(t_token)))))
		ft_ferror(ERR_MALLOC);
	token->type = type;
	token->value = value;
	return (token);
}

static void		ft_add_type_token(t_list **tokens, char *line)
{
	t_token		*token;
	int			pos;
	char		*str;

	pos = 0;
	while (line[pos])
		++pos;
	if ((!(str = ft_strsub(line, 0, pos))))
		ft_ferror(ERR_MALLOC);
	token = ft_init_token(PRIM_TYPE, str);
	ft_listpushback(tokens, token);
}

static void		ft_add_field_token(t_list **tokens, char *line)
{
	t_token		*token;
	int			pos;
	int			pos2;
	char		*str;

	pos = 3;
	while (line[pos] && line[pos] != ':')
		++pos;
	if ((!(str = ft_strsub(line, 3, pos - 3))))
		ft_ferror(ERR_MALLOC);
	token = ft_init_token(PRIM_NAME, str);
	ft_listpushback(tokens, token);
	++pos;
	while (line[pos] && (line[pos] == ' '|| line[pos] == '\t'))
		++pos;
	pos2 = 0;
	while (line[pos2])
		++pos2;
	if ((!(str = ft_strsub(line, pos, pos2 - pos))))
		ft_ferror(ERR_MALLOC);
	token = ft_init_token(PRIM_VALUE, str);
	ft_listpushback(tokens, token);
}

static t_list	*ft_tokenize_file(int fd)
{
	char		*line;
	t_list		*tokens;
	int			ret;

	tokens = NULL;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		if (ft_strequ(line, "") || line[0] == '#')
		{
			free(line);
			continue ;
		}
		else if (ft_isalpha(line[0]))
			ft_add_type_token(&tokens, line);
		else if (ft_strnequ(line, "\t- ", 3))
			ft_add_field_token(&tokens, line);
		else
			ft_ferror(ERR_FILE_FORMAT);
		free(line);
	}
	if (ret == -1)
		ft_ferror(ERR_FREAD);
	return (tokens);
}

t_scene			*ft_load_scene(char *filepath)
{
	t_scene		*scene;
	t_list		*tokens;
	int			fd;

	tokens = NULL;
	if ((fd = open(filepath, O_RDONLY)) == -1)
		ft_ferror(ERR_FOPEN);
	tokens = ft_tokenize_file(fd);
	close(fd);
	scene = ft_parse_scene(&tokens);
	if (!scene->cam)
		ft_ferror(ERR_NO_CAM);
	if (!scene->light)
		ft_ferror(ERR_NO_LIGHT);
	return (scene);
}
