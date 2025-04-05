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

int	key_press(int keycode, t_data *data)
{
	data->keys[keycode] = 1;
	if (keycode == XK_Escape)
		return (close_win(data));
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	data->keys[keycode] = 0;
	return (0);
}

int	close_win(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->wall.img)
		mlx_destroy_image(data->mlx, data->wall.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
