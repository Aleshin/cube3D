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

void	load_single_texture(void *mlx, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, tex->path, &tex->width, &tex->height);
	if (!tex->img)
	{
		perror("Failed to load texture");
		exit(EXIT_FAILURE);
	}
	tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
}

void	load_textures(t_game *data)
{
	load_single_texture(data->mlx, &data->textures.north);
	load_single_texture(data->mlx, &data->textures.south);
	load_single_texture(data->mlx, &data->textures.east);
	load_single_texture(data->mlx, &data->textures.west);
}

t_tex	*get_wall_tex(t_game *data, int side,
			double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (&data->textures.west);
		else
			return (&data->textures.east);
	}
	else
	{
		if (ray_dir_y > 0)
			return (&data->textures.north);
		else
			return (&data->textures.south);
	}
}

void	calculate_texture(t_game *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->py + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->px + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	ray->step = 1.0 * TEX_HEIGHT / (ray->draw_end - ray->draw_start);
	ray->tex_pos = (ray->draw_start - HEIGHT / 2
			+ (ray->draw_end - ray->draw_start) / 2) * ray->step;
}
