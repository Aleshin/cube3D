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

void	move_forward(t_game *data)
{
	if (data->map[(int)(data->py)]
		[(int)(data->px + data->dir_x * MOVE_SPEED)] == 0)
		data->px += data->dir_x * MOVE_SPEED;
	if (data->map[(int)(data->py + data->dir_y * MOVE_SPEED)]
		[(int)(data->px)] == 0)
		data->py += data->dir_y * MOVE_SPEED;
}

void	move_backward(t_game *data)
{
	if (data->map[(int)(data->py)]
		[(int)(data->px - data->dir_x * MOVE_SPEED)] == 0)
		data->px -= data->dir_x * MOVE_SPEED;
	if (data->map[(int)(data->py - data->dir_y * MOVE_SPEED)]
		[(int)(data->px)] == 0)
		data->py -= data->dir_y * MOVE_SPEED;
}

void	strafe_left(t_game *data)
{
	if (data->map[(int)(data->py)]
		[(int)(data->px - data->plane_x * MOVE_SPEED)] == 0)
		data->px -= data->plane_x * MOVE_SPEED;
	if (data->map[(int)(data->py - data->plane_y * MOVE_SPEED)]
		[(int)(data->px)] == 0)
		data->py -= data->plane_y * MOVE_SPEED;
}

void	strafe_right(t_game *data)
{
	if (data->map[(int)(data->py)]
		[(int)(data->px + data->plane_x * MOVE_SPEED)] == 0)
		data->px += data->plane_x * MOVE_SPEED;
	if (data->map[(int)(data->py + data->plane_y * MOVE_SPEED)]
		[(int)(data->px)] == 0)
		data->py += data->plane_y * MOVE_SPEED;
}
