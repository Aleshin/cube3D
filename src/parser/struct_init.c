/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:40:04 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:40:08 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_texture_and_colors(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->ceiling = -2;
	data->floor = -2;
}

static void	init_map_and_player(t_data *data)
{
	size_t	i;

	i = 0;
	data->map_size = 2;
	data->map = (char **)malloc(sizeof(char *) * data->map_size);
	if (!data->map)
	{
		data->map = NULL;
		return ;
	}
	while (i < data->map_size)
	{
		data->map[i] = NULL;
		i++;
	}
	data->me.dir = ' ';
	data->me.pos.x = 0;
	data->me.pos.y = 0;
}

void	input_data_init(t_data *data)
{
	if (!data)
		return ;
	init_texture_and_colors(data);
	data->filled = 0;
	data->rows = 0;
	data->cols = 0;
	data->inside = 0;
	init_map_and_player(data);
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data)
		return ;
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	while (i < data->map_size)
	{
		free(data->map[i]);
		data->map[i] = NULL;
		i++;
	}
	free(data->map);
	data->map = NULL;
}
