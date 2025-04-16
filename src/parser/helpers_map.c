/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:38:38 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 20:02:01 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	valid_char(char *line, int *pos)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N'
			&& *line != 'S' && *line != 'W' && *line != 'E'
			&& !ft_isspace(*line))
		{
			printf("Wrong char %c\n", *line);
			return (0);
		}
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			(*pos)++;
		line++;
	}
	return (1);
}

int	map_chars_ok(const t_data data)
{
	size_t	i;
	int		pos;

	i = 0;
	pos = 0;
	if (data.rows < 3)
		return (0);
	while (i < data.rows)
	{
		if (is_empty_or_whitespace(data.map[i]))
		{
			printf("Error empty line inside a map\n");
			return (0);
		}
		if (!valid_char(data.map[i], &pos))
		{
			printf("Error not allowed characters\n");
			return (0);
		}
		i++;
	}
	if (pos > 1 || pos < 1)
		printf("Error position is not correct\n");
	return (pos == 1);
}

char	*trim_trailing_spaces(const char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && ft_isspace(str[len - 1]))
		len--;
	return (ft_substr(str, 0, len));
}

static int	grow_map(t_data *data)
{
	size_t		i;
	char		**new_map;

	if (!data || !data->map)
		return (0);
	new_map = (char **)malloc(sizeof(char *) * (data->map_size * 2));
	if (!new_map)
		return (0);
	i = 0;
	while (i < data->rows)
	{
		new_map[i] = data->map[i];
		i++;
	}
	while (i < data->map_size * 2)
		new_map[i++] = NULL;
	free(data->map);
	data->map = new_map;
	data->map_size *= 2;
	return (1);
}

int	store_raw_map(t_data *data, char *line)
{
	size_t	len;
	char	*trimmed_line;

	if (!data || !line || !data->inside)
		return (0);
	trimmed_line = trim_trailing_spaces(line);
	if (!trimmed_line)
		return (0);
	len = ft_strlen(trimmed_line);
	if (data->rows >= data->map_size)
	{
		if (!grow_map(data))
			return (free(trimmed_line), 0);
	}
	data->map[data->rows] = (char *)malloc(len + 1);
	if (!data->map[data->rows])
		return (free(trimmed_line), 0);
	ft_strlcpy(data->map[data->rows], trimmed_line, len + 1);
	free(trimmed_line);
	data->rows++;
	return (1);
}
