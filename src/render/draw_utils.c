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

void	draw_textured_line(t_data *data, t_tex *tex, t_draw *d)
{
	int	y;
	int	tex_y;
	int	color;

	y = d->draw_start;
	while (y < d->draw_end)
	{
		tex_y = (int)d->tex_pos & (tex->height - 1);
		d->tex_pos += d->step;
		color = tex->data[tex->width * tex_y + d->tex_x];
		my_mlx_pixel_put(data, d->x, y, color);
		y++;
	}
}

void	draw_wall(t_data *data, int x, t_ray *ray)
{
	t_draw	d;
	t_tex	*tex;

	tex = get_wall_tex(data, ray->side, ray->ray_dir_x, ray->ray_dir_y);
	d.x = x;
	d.draw_start = ray->draw_start;
	d.draw_end = ray->draw_end;
	d.tex_x = ray->tex_x;
	d.step = ray->step;
	d.tex_pos = ray->tex_pos;
	draw_textured_line(data, tex, &d);
}

void	draw_ceiling(t_data *data, int x, int draw_start, int color)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void	draw_floor(t_data *data, int x, int draw_end, int color)
{
	int	y;

	y = draw_end;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
