/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_check_id.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:39:04 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:08 by emikhayl         ###   ########.fr       */
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

static int	handle_color_id(char *type, char *str, int *target)
{
	if (*target != -2)
		return (print_err("Duplicated identifier", type, -1));
	*target = set_color(str);
	if (*target == -1)
		return (-1);
	return (1);
}

static int	handle_texture_id(char *type, char *str, char **target)
{
	if (*target != NULL)
		return (print_err("Duplicated identifier", type, -1));
	*target = trim_trailing_spaces(str);
	if (!*target)
		return (-1);
	return (1);
}

int	check_identifier(char *str, t_data *data)
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
		return (free(type), 0);
	str = move_to_val(str);
	if (ft_strcmp(type, "F") == 0 || ft_strcmp(type, "C") == 0)
	{
		if (handle_color_id(type, str, (int *)target) == -1)
			return (free(type), -1);
	}
	else
	{
		if (handle_texture_id(type, str, (char **)target) == -1)
			return (free(type), -1);
	}
	free(type);
	return (1);
}
