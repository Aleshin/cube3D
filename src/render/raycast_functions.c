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

void	init_ray(t_game *data, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * camera_x;
	ray->ray_dir_y = data->dir_y + data->plane_y * camera_x;
	ray->map_x = (int)data->px;
	ray->map_y = (int)data->py;
}

void	perform_dda(t_game *data, t_ray *ray, t_dda *dda)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (dda->side_x < dda->side_y)
		{
			dda->side_x += dda->delta_x;
			ray->map_x += dda->step_x;
			ray->side = 0;
		}
		else
		{
			dda->side_y += dda->delta_y;
			ray->map_y += dda->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] > 0)
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = dda->side_x - dda->delta_x;
	else
		ray->perp_wall_dist = dda->side_y - dda->delta_y;
}

void	calculate_projection(t_ray *ray)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	cast_ray(t_game *data, int x, t_ray *ray)
{
	t_dda	dda;

	init_ray(data, x, ray);
	init_steps(data, ray, &dda);
	perform_dda(data, ray, &dda);
	calculate_projection(ray);
	calculate_texture(data, ray);
}
