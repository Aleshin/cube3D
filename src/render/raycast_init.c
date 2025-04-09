/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:00:00 by saleshin          #+#    #+#             */
/*   Updated: 2025/04/07 17:00:00 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_deltas(t_ray *ray, t_dda *dda)
{
	if (ray->ray_dir_x == 0)
		dda->delta_x = 1e30;
	else
		dda->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		dda->delta_y = 1e30;
	else
		dda->delta_y = fabs(1 / ray->ray_dir_y);
}

static void	init_step_x(t_game *data, t_ray *ray, t_dda *dda)
{
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
}

static void	init_step_y(t_game *data, t_ray *ray, t_dda *dda)
{
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

void	init_steps(t_game *data, t_ray *ray, t_dda *dda)
{
	init_deltas(ray, dda);
	init_step_x(data, ray, dda);
	init_step_y(data, ray, dda);
}
