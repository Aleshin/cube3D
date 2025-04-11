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

#include "game.h"

void	rotate_left(t_game *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED)
		- data->dir_y * sin(ROT_SPEED);
	data->dir_y = old_dir_x * sin(ROT_SPEED)
		+ data->dir_y * cos(ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(ROT_SPEED)
		- data->plane_y * sin(ROT_SPEED);
	data->plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->plane_y * cos(ROT_SPEED);
}

void	rotate_right(t_game *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-ROT_SPEED)
		- data->dir_y * sin(-ROT_SPEED);
	data->dir_y = old_dir_x * sin(-ROT_SPEED)
		+ data->dir_y * cos(-ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-ROT_SPEED)
		- data->plane_y * sin(-ROT_SPEED);
	data->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->plane_y * cos(-ROT_SPEED);
}
