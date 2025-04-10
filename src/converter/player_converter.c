/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_converter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:19:00 by saleshin          #+#    #+#             */
/*   Updated: 2025/04/05 20:19:13 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	set_dir_north(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = -1;
	game->plane_x = 0.66;
	game->plane_y = 0;
}

static void	set_dir_south(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = 1;
	game->plane_x = -0.66;
	game->plane_y = 0;
}

static void	set_dir_east(t_game *game)
{
	game->dir_x = 1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0.66;
}

static void	set_dir_west(t_game *game)
{
	game->dir_x = -1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = -0.66;
}

void	set_player_direction(t_game *game, t_player *player)
{
	game->px = player->pos.x;
	game->py = player->pos.y;
	if (player->dir == 'N')
		set_dir_north(game);
	else if (player->dir == 'S')
		set_dir_south(game);
	else if (player->dir == 'E')
		set_dir_east(game);
	else if (player->dir == 'W')
		set_dir_west(game);
}
