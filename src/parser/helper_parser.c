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

int	map_begin(char *str)
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

int	handle_map(t_data *data, char *str)
{
	if (data->filled < 6)
		return (print_err("Map should be last", NULL, 0));
	data->inside = 1;
	if (store_raw_map(data, str))
		return (1);
	return (0);
}

char	*get_type(char *str)
{
	int		i;
	int		len;
	char	*type;

	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (ft_isspace(str[len]))
		len++;
	while (str[len + i] && !ft_isspace(str[len + i]))
		i++;
	type = malloc(sizeof(char) * (i + 1));
	if (!type)
		return (NULL);
	i = 0;
	while (str[len] && !ft_isspace(str[len]))
		type[i++] = str[len++];
	type[i] = '\0';
	return (type);
}

void	*get_texture_or_color(char *type, t_data *data)
{
	if (!type || !data)
		return (NULL);
	if (ft_strcmp(type, "NO") == 0)
		return (&(data->NO));
	if (ft_strcmp(type, "SO") == 0)
		return (&(data->SO));
	if (ft_strcmp(type, "WE") == 0)
		return (&(data->WE));
	if (ft_strcmp(type, "EA") == 0)
		return (&(data->EA));
	if (ft_strcmp(type, "F") == 0)
		return (&(data->floor));
	if (ft_strcmp(type, "C") == 0)
		return (&(data->ceiling));
	return (NULL);
}
