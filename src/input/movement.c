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

#include "cube3d.h"

void	move_forward(t_data *data)
{
	if (data->map[(int)(data->py)]
		[(int)(data->px + data->dirX * MOVE_SPEED)] == 0)
		data->px += data->dirX * MOVE_SPEED;
	if (data->map[(int)(data->py + data->dirY * MOVE_SPEED)]
		[(int)(data->px)] == 0)
		data->py += data->dirY * MOVE_SPEED;
}

void	move_backward(t_data *data)
{
	if (data->map[(int)(data->py)]
		[(int)(data->px - data->dirX * MOVE_SPEED)] == 0)
		data->px -= data->dirX * MOVE_SPEED;
	if (data->map[(int)(data->py - data->dirY * MOVE_SPEED)]
		[(int)(data->px)] == 0)
		data->py -= data->dirY * MOVE_SPEED;
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dirX;
	data->dirX = data->dirX * cos(ROT_SPEED)
		- data->dirY * sin(ROT_SPEED);
	data->dirY = old_dir_x * sin(ROT_SPEED)
		+ data->dirY * cos(ROT_SPEED);
	old_plane_x = data->planeX;
	data->planeX = data->planeX * cos(ROT_SPEED)
		- data->planeY * sin(ROT_SPEED);
	data->planeY = old_plane_x * sin(ROT_SPEED)
		+ data->planeY * cos(ROT_SPEED);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dirX;
	data->dirX = data->dirX * cos(-ROT_SPEED)
		- data->dirY * sin(-ROT_SPEED);
	data->dirY = old_dir_x * sin(-ROT_SPEED)
		+ data->dirY * cos(-ROT_SPEED);
	old_plane_x = data->planeX;
	data->planeX = data->planeX * cos(-ROT_SPEED)
		- data->planeY * sin(-ROT_SPEED);
	data->planeY = old_plane_x * sin(-ROT_SPEED)
		+ data->planeY * cos(-ROT_SPEED);
}

void	handle_movement(t_data *data)
{
	if (data->keys[XK_w])
		move_forward(data);
	if (data->keys[XK_s])
		move_backward(data);
	if (data->keys[XK_a])
		rotate_left(data);
	if (data->keys[XK_d])
		rotate_right(data);
}
