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

#include "cube3d.h"

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < (int)(sizeof(t_data) / sizeof(int)))
	{
		((int *)data)[i] = 0;
		i++;
	}
	init_player(data);
	init_window(data);
	init_map(data);
	load_textures(data);
}

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

void	init_map(t_data *data)
{
	int	temp[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1}
	};
	int	y;
	int	x;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			data->map[y][x] = temp[y][x];
			x++;
		}
		y++;
	}
	data->textures.north.path = ft_strdup("src/textures/colorstone.xpm");
	data->textures.south.path = ft_strdup("src/textures/colorstone.xpm");
	data->textures.east.path = ft_strdup("src/textures/greystone.xpm");
	data->textures.west.path = ft_strdup("src/textures/greystone.xpm");
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	i = 0;
	while (s[i])
		i++;
	copy = malloc(i + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
