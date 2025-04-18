/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:37:59 by saleshin          #+#    #+#             */
/*   Updated: 2025/04/05 21:38:02 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *data, t_data input)
{
	int	i;

	i = 0;
	while (i < (int)(sizeof(t_game) / sizeof(int)))
	{
		((int *)data)[i] = 0;
		i++;
	}
	init_player(data);
	init_window(data);
	init_map(data, input);
	load_textures(data);
}

void	init_player(t_game *data)
{
	data->px = 2.5;
	data->py = 2.5;
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = FOV;
	data->textures.north.path = NULL;
	data->textures.south.path = NULL;
	data->textures.east.path = NULL;
	data->textures.west.path = NULL;
	gettimeofday(&data->prev_time, NULL);
}

void	init_window(t_game *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D with texture");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img,
			&data->bpp, &data->line_length, &data->endian);
}

void	init_map(t_game *data, t_data input)
{
	data->width = (int)input.cols;
	data->height = (int)input.rows;
	data->map = convert_char_map_to_int(input);
	if (!data->map)
	{
		printf("Error: failed to convert map\n");
		exit(0);
	}
	data->textures.north.path = ft_strdup(input.no);
	data->textures.south.path = ft_strdup(input.so);
	data->textures.east.path = ft_strdup(input.ea);
	data->textures.west.path = ft_strdup(input.we);
}
