/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:37:59 by saleshin          #+#    #+#             */
/*   Updated: 2025/04/05 21:38:02 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cube3d.h"

void	init_player(t_data *data)
{
	data->px = 2.5;
	data->py = 2.5;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = FOV;
	gettimeofday(&data->prev_time, NULL);
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D with texture");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img,
			&data->bpp, &data->line_length, &data->endian);
}

void	load_textures(t_data *data)
{
	int	w;
	int	h;

	data->wall.img = mlx_xpm_file_to_image(data->mlx,
			"greystone.xpm", &w, &h);
	data->wall.data = (int *)mlx_get_data_addr(data->wall.img,
			&data->wall.bpp, &data->wall.line_length, &data->wall.endian);
}

void	init_map(t_data *data)
{
	int temp[MAP_HEIGHT][MAP_WIDTH] = {
		{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1}
	};

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
			data->map[y][x] = temp[y][x];
	}
}
