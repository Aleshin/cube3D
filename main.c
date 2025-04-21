/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:19:00 by saleshin          #+#    #+#             */
/*   Updated: 2025/04/05 20:19:13 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "cub3d.h"

void	fill_cols(int i, t_data *data, int **map)
{
	size_t	j;

	j = 0;
	while (j < data->cols)
	{
		map[i][j] = data->map[i][j] - '0';
		if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
			|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			map[i][j] = 0;
		j++;
	}
}

int	**convert_char_map_to_int(t_data data)
{
	int		**int_map;
	size_t	i;

	int_map = malloc(sizeof(int *) * data.rows);
	if (!int_map)
		return (NULL);
	i = 0;
	while (i < data.rows)
	{
		int_map[i] = malloc(sizeof(int) * data.cols);
		if (!int_map[i])
		{
			while (i > 0)
				free(int_map[--i]);
			return (free(int_map), NULL);
		}
		fill_cols(i, &data, int_map);
		i++;
	}
	return (int_map);
}

int	main(int argc, char **argv)
{
	t_game	game_data;
	t_data	data;

	input_data_init(&data);
	if (!parser(argc, argv, &data))
	{
		free_data(&data);
		return (1);
	}
	init_game(&game_data, data);
	set_player_direction(&game_data, &data.me);
	set_colors(&game_data, &data);
	free_data(&data);
	mlx_loop_hook(game_data.mlx, render, &game_data);
	mlx_hook(game_data.win, 2, 1L << 0, key_press, &game_data);
	mlx_hook(game_data.win, 3, 1L << 1, key_release, &game_data);
	mlx_hook(game_data.win, 17, 0, close_win, &game_data);
	mlx_loop(game_data.mlx);
	return (0);
}
