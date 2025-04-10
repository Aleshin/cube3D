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
	return (0);
}
