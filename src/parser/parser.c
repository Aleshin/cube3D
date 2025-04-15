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

static char	*move_to_val(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace(*str))
		str++;
	while (*str && !ft_isspace(*str))
		str++;
	while (ft_isspace(*str))
		str++;
	return (str);
}

static int	check_identifier(char *str, t_data *data)
{
	char	*type;
	void	*target;

	if (!str || !data)
		return (0);
	type = get_type(str);
	if (!type)
		return (0);
	target = get_texture_or_color(type, data);
	if (!target)
	{
		free(type);
		return (0);
	}
	str = move_to_val(str);
	if (ft_strcmp(type, "F") == 0 || ft_strcmp(type, "C") == 0)
	{
		if (*(int *)target != -2)
			return (print_err("Duplicated identifier", type, -1));
		*(int *)target = set_color(str);
		if (*(int *)target == -1)
			return (-1);
	}
	else
	{
		if (*(char **)target != NULL)
			return (print_err("Duplicated identifier", type, -1));
		*(char **)target = trim_trailing_spaces(str);
		if (!*(char **)target)
			return (-1);
	}
	free(type);
	return (1);
}

static int	parse_line(char *str, t_data *data)
{
	int	result;

	if (!str || !data)
		return (0);
	if (map_begin(str))
	{
		if (data->filled < 6)
			return (print_err("Map must be last", str, 0));
		return (handle_map(data, str));
	}
	result = check_identifier(str, data);
	if (result == 1)
		return (++data->filled, 1);
	else if (result == -1)
		return (0);
	return (print_err("Unrecognised input", str, 0));
}

int	parser(int argc, char **argv, t_data *data)
{
	int		fd;
	char	*file;
	char	*line;

	file = get_filename(argc, argv);
	if (!file)
		return (0);
	fd = err_open(file);
	if (fd == -1)
		return (0);
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
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (!map_ok(data))
		return (0);
	close(fd);
	return (1);
}
