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

void	set_colors(t_game *game, t_data *colors)
{
	game->color_floor = colors->floor;
	game->color_ceiling = colors->ceiling;
}
