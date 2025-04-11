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
#include "./libft/libft.h"
#include "game.h"
#include "parser.h"

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

void	print_int_map(int **map, size_t rows, size_t cols)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("%d", map[i][j]);
			if (j < cols - 1)
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
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
	// Print parsed data info
	// printf("Data from input:\n");
	// printf("path to north %s\n", data.NO);
	// printf("path to south %s\n", data.SO);
	// printf("path to east %s\n", data.EA);
	// printf("path to west %s\n", data.WE);
	// printf("Floor color %d, celiling color %d\n", data.floor, data.ceiling);
	// printf("Map size rows %zu, cols %zu\n", data.rows, data.cols);
	// printf("Position direction %c, coord [%d].[%d]\n",
	// 	data.me.dir, data.me.pos.x, data.me.pos.y);
	// Convert char map to int map and print it
	//game logic placeholder
	init_game(&game_data, data);
	print_int_map(game_data.map,game_data.height, game_data.width);
	mlx_loop_hook(game_data.mlx, render, &game_data);
	mlx_hook(game_data.win, 2, 1L << 0, key_press, &game_data);
	mlx_hook(game_data.win, 3, 1L << 1, key_release, &game_data);
	mlx_hook(game_data.win, 17, 0, close_win, &game_data);
	mlx_loop(game_data.mlx);
	free_data(&data);
	return (0);
}
