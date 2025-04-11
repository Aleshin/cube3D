/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:22:53 by saleshin          #+#    #+#             */
/*   Updated: 2025/04/05 21:22:57 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	render_frame(t_game *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(data, x, &ray);
		draw_ceiling(data, x, ray.draw_start, data->color_ceiling);
		draw_wall(data, x, &ray);
		draw_floor(data, x, ray.draw_end, data->color_floor);
		x++;
	}
}

int	render(t_game *data)
{
	struct timeval	curr;
	double			seconds;

	gettimeofday(&curr, NULL);
	seconds = (curr.tv_sec - data->prev_time.tv_sec)
		+ (curr.tv_usec - data->prev_time.tv_usec) / 1000000.0;
	data->frame_time = seconds;
	data->prev_time = curr;
	handle_movement(data);
	render_frame(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
