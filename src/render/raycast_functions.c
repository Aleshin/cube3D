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
#include "cube3d.h"

void	init_ray(t_data *data, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = data->dirX + data->planeX * camera_x;
	ray->ray_dir_y = data->dirY + data->planeY * camera_x;
	ray->map_x = (int)data->px;
	ray->map_y = (int)data->py;
}

void	init_steps(t_data *data, t_ray *ray, t_dda *dda)
{
	if (ray->ray_dir_x == 0)
		dda->delta_x = 1e30;
	else
		dda->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		dda->delta_y = 1e30;
	else
		dda->delta_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_x = (data->px - ray->map_x) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_x = (ray->map_x + 1.0 - data->px) * dda->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_y = (data->py - ray->map_y) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_y = (ray->map_y + 1.0 - data->py) * dda->delta_y;
	}
}

void	perform_dda(t_data *data, t_ray *ray, t_dda *dda)
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

void	cast_ray(t_data *data, int x, t_ray *ray)
{
	t_dda	dda;

	init_ray(data, x, ray);
	init_steps(data, ray, &dda);
	perform_dda(data, ray, &dda);
	calculate_projection(ray);
	calculate_texture(data, ray);
}
