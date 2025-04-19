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

//0 is err
static int	parse_line(char *str, t_data *data)
{
	int	result;

	if (!str || !data)
		return (0);

	if (data->inside || map_begin(str))
	{
		if (data->filled < 6)
			return (print_err("Map must be last", str, 0));
		return (handle_map(data, str));
	}

	result = check_identifier(str, data);
	if (result == 1)
	{
		data->filled++;
		return (1);
	}
	else if (result == -1)
		return (0);
	return (print_err("Unrecognised input", str, 0));
}

//0 is errr
int	read_line(char *line, t_data *data, int *fd)
{
	while (line)
	{
		if (is_empty_or_whitespace(line) && data->inside == 0)
		{
			free(line);
			line = get_next_line(*fd);
			continue ;
		}
		if (!parse_line(line, data))
		{
			free(line);
			return 0;
		}
		free(line);
		line = get_next_line(*fd);
	}
	return (1);
}

//err is 0
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
	
	if(!read_line(line, data, &fd))
		return (0);
	if (!map_ok(data))
		return (0);
	close(fd);
	return (1);
}
