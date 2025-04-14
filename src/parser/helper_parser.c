/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:39:45 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:48 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	map_begin(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '1' && *str != '0' && *str != 'N' && *str != 'S'
			&& *str != 'E' && *str != 'W' && !ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	handle_map(t_data *data, char *str)
{
	if (data->filled < 6)
		return (print_err("Map should be last", NULL, 0));
	data->inside = 1;
	if (store_raw_map(data, str))
		return (1);
	return (0);
}

void	init_ptrs(t_data *data, void **targets, char **ids)
{
	targets[0] = &(data->NO);
	targets[1] = &(data->SO);
	targets[2] = &(data->WE);
	targets[3] = &(data->EA);
	targets[4] = &(data->floor);
	targets[5] = &(data->ceiling);
	ids[0] = "NO";
	ids[1] = "SO";
	ids[2] = "WE";
	ids[3] = "EA";
	ids[4] = "F";
	ids[5] = "C";
}

int	parse_line(char *str, t_data *data)
{
	int		result;
	int		i;
	void	*targets[6];
	char	*ids[6];
	char	*start;

	start = str;
	if (!str || !data)
		return (0);
	while (ft_isspace(*str))
		str++;
    init_ptrs(data, targets, ids);
	i = 0;
	while (i < 6)
	{
		result = check_identifier(str, targets[i], ids[i]);
		if (result == 1)
			return (data->filled++, 1);
		if (result == -1)
			return (0);
		i++;
	}
	if (map_begin(str))
		return (handle_map(data, start));
	else
		return (print_err("Unrecognized input", str, 0));
	return (0);
}
