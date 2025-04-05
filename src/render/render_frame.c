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

void render_frame(t_data *data) {
    int ceiling_color = 0xA8A8B8; // тёмно-синий
    int floor_color = 0x5A5A5A;   // тёмно-серый

    for (int x = 0; x < WIDTH; x++) {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        int mapX = (int)data->px;
        int mapY = (int)data->py;

        double sideDistX, sideDistY;
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX, stepY, hit = 0, side;

        if (rayDirX < 0) { stepX = -1; sideDistX = (data->px - mapX) * deltaDistX; }
        else { stepX = 1; sideDistX = (mapX + 1.0 - data->px) * deltaDistX; }
        if (rayDirY < 0) { stepY = -1; sideDistY = (data->py - mapY) * deltaDistY; }
        else { stepY = 1; sideDistY = (mapY + 1.0 - data->py) * deltaDistY; }

        while (hit == 0) {
            if (sideDistX < sideDistY) { sideDistX += deltaDistX; mapX += stepX; side = 0; }
            else { sideDistY += deltaDistY; mapY += stepY; side = 1; }
            if (data->map[mapY][mapX] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        double wallX;
        if (side == 0)
            wallX = data->py + perpWallDist * rayDirY;
        else
            wallX = data->px + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)TEX_WIDTH);
        if (side == 0 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;

        double step = 1.0 * TEX_HEIGHT / lineHeight;
        double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

        // потолок
        for (int y = 0; y < drawStart; y++)
            my_mlx_pixel_put(data, x, y, ceiling_color);

        // стена (текстура)
        draw_textured_line(data, x, drawStart, drawEnd, texX, step, texPos);

        // пол
        for (int y = drawEnd; y < HEIGHT; y++)
            my_mlx_pixel_put(data, x, y, floor_color);
    }
}
