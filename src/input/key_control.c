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

int	key_press(int keycode, t_game *data)
{
	data->keys[keycode] = 1;
	if (keycode == XK_Escape)
		return (close_win(data));
	return (0);
}

int	key_release(int keycode, t_game *data)
{
	data->keys[keycode] = 0;
	return (0);
}

int	close_win(void *param)
{
	t_game	*data;

	data = (t_game *)param;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->textures.north.img)
		mlx_destroy_image(data->mlx, data->textures.north.img);
	if (data->textures.south.img)
		mlx_destroy_image(data->mlx, data->textures.south.img);
	if (data->textures.east.img)
		mlx_destroy_image(data->mlx, data->textures.east.img);
	if (data->textures.west.img)
		mlx_destroy_image(data->mlx, data->textures.west.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

void	handle_movement(t_game *data)
{
	if (data->keys[XK_w])
		move_forward(data);
	if (data->keys[XK_s])
		move_backward(data);
	if (data->keys[XK_a])
		strafe_left(data);
	if (data->keys[XK_d])
		strafe_right(data);
	if (data->keys[XK_Left])
		rotate_left(data);
	if (data->keys[XK_Right])
		rotate_right(data);
}
