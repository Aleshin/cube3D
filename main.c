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
//#include "game.h"
#include "parser.h"


int	**convert_char_map_to_int(t_data data)
{
	int		**int_map;
	size_t	i, j;

	int_map = malloc(sizeof(int *) * data.rows);
	if (!int_map)
		return (NULL);
	i = 0;
	while (i < data.rows)
	{
		int_map[i] = malloc(sizeof(int) * data.cols);
		if (!int_map[i])
		{
			// Free previously allocated rows on error
			while (i > 0)
				free(int_map[--i]);
			free(int_map);
			return (NULL);
		}
		j = 0;
		while (j < data.cols)
		{
			// Convert char to int (example: '1' -> 1, '0' -> 0, etc.)
			int_map[i][j] = data.map[i][j] - '0';
			if(data.map[i][j] == 'N' || data.map[i][j] == 'S'
				|| data.map[i][j] == 'E' || data.map[i][j] == 'W')
				int_map[i][j] = 0;
			j++;
		}
		i++;
	}
	return (int_map);
}

void	print_int_map(int **map, size_t rows, size_t cols)
{
	size_t i, j;

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
	//t_game	game_data;
	t_data	data;
	input_data_init(&data);

	if (!parser(argc, argv, &data))
	{
		free_data(&data);
		return (1);
	}

	//init_game(&game_data);
	// mlx_loop_hook(game_data.mlx, render, &game_data);
	// mlx_hook(game_data.win, 2, 1L << 0, key_press, &game_data);
	// mlx_hook(game_data.win, 3, 1L << 1, key_release, &game_data);
	// mlx_hook(game_data.win, 17, 0, close_win, &game_data);
	// mlx_loop(game_data.mlx);
	printf("Data from input:\npath to north %s\npath to south %s\npath to east %s\npath to west %s\n", data.NO, data.SO, data.EA, data.WE);
	printf("Floor color %d, celiling color %d\n", data.floor, data.ceiling);
	printf("Map size rows %zu, cols %zu\n", data.rows, data.cols);
	printf("Position direction %c, coord [%d].[%d]\n", data.me.dir, data.me.pos.x, data.me.pos.y);
	int **map = convert_char_map_to_int(data);
	print_int_map(map, data.rows, data.cols); //check
	return (0);
}
