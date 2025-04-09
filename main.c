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

#include "game.h"

int	main(void)
{
	t_game	game_data;

	init_game(&game_data);
	mlx_loop_hook(game_data.mlx, render, &game_data);
	mlx_hook(game_data.win, 2, 1L << 0, key_press, &game_data);
	mlx_hook(game_data.win, 3, 1L << 1, key_release, &game_data);
	mlx_hook(game_data.win, 17, 0, close_win, &game_data);
	mlx_loop(game_data.mlx);
	return (0);
}
