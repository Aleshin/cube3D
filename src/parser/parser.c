/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:39:45 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:48 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

//if (check_identifier(str, &(data->NO), "NO"))
int	check_identifier(char *str, void *target, char *id)
{
	size_t	id_len;
	int		*color_target;
	char	**path_target;

	id_len = ft_strlen(id);
	if (ft_strncmp(str, id, id_len) != 0 || !ft_isspace(str[id_len]))
		return (0);
	str += id_len;
	while (ft_isspace(*str))
		str++;
	if (id[0] == 'F' || id[0] == 'C')
	{
		color_target = (int *)target;
		if (*color_target != -2)
			return (print_err("Duplicated identifier", id, -1));
		*color_target = set_color(str);
		if (*color_target == -1)
			return (-1);
	}
	else
	{
		path_target = (char **)target;
		if (*path_target != NULL)
			return (print_err("Duplicated identifier", id, -1));
		*path_target = trim_trailing_spaces(str);
		if (!*path_target)
			return (-1);
	}
	return (1);
}

int	parser(int argc, char **argv, t_data *data)
{
	int		fd;
	char	*file;
	char	*line;

	file = get_filename(argc, argv);
	if (!file)
	{
		return (0);
	}
	fd = err_open(file);
	if (fd == -1)
	{
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_or_whitespace(line) && data->inside == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!parse_line(line, data))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!map_ok(data))
	{
		print_input(*data);
		return (0);
	}
	close(fd);
	return (1);
}
