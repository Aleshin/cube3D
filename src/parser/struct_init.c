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
	data->NO = NULL; // Path to the texture file
	data->SO = NULL;
	data->WE = NULL;
	data->EA = NULL;
	data->ceiling = -2; // 0 to 255
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
	// Free texture paths
	free(data->NO);
	free(data->SO);
	free(data->WE);
	free(data->EA);
	// Free the map
	while (i < data->map_size)
	{
		free(data->map[i]);
		data->map[i] = NULL;
		i++;
	}
	free(data->map);
	data->map = NULL;
}
