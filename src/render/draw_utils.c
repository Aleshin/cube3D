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

void draw_textured_line(t_data *data, int x, int drawStart, int drawEnd, int texX, double step, double texPos) {
    for (int y = drawStart; y < drawEnd; y++) {
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        int color = data->wall.data[TEX_WIDTH * texY + texX];
        my_mlx_pixel_put(data, x, y, color);
    }
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int render(t_data *data) {
    struct timeval curr;
    gettimeofday(&curr, NULL);

    double seconds = (curr.tv_sec - data->prev_time.tv_sec)
                   + (curr.tv_usec - data->prev_time.tv_usec) / 1000000.0;
    data->frame_time = seconds;
    data->prev_time = curr;

    handle_movement(data);           // движение каждый кадр
    render_frame(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}
