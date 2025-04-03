#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <sys/time.h>

#define WIDTH 640
#define HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define MAP_WIDTH 6
#define MAP_HEIGHT 5
#define FOV 0.66
#define MOVE_SPEED 0.005
#define ROT_SPEED 0.003

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1},
    {1,1,1,1,1,1}
};

typedef struct s_tex {
    void *img;
    int *data;
    int bpp;
    int line_length;
    int endian;
}   t_tex;

typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
    int keys[65536]; // Состояние всех клавиш

    struct timeval prev_time;
    double frame_time;

    t_tex wall;

    double px, py;
    double dirX, dirY;
    double planeX, planeY;
}   t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    char *dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_textured_line(t_data *data, int x, int drawStart, int drawEnd, int texX, double step, double texPos) {
    for (int y = drawStart; y < drawEnd; y++) {
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        int color = data->wall.data[TEX_WIDTH * texY + texX];
        my_mlx_pixel_put(data, x, y, color);
    }
}

int close_win(void *param) {
    t_data *data = (t_data *)param;

    if (data->img)
        mlx_destroy_image(data->mlx, data->img);

    if (data->wall.img)
        mlx_destroy_image(data->mlx, data->wall.img);

    if (data->win)
        mlx_destroy_window(data->mlx, data->win);

    exit(0);
}

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
            if (map[mapY][mapX] > 0) hit = 1;
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

int key_press(int keycode, t_data *data)
{
    data->keys[keycode] = 1;
    if (keycode == XK_Escape)
        return close_win(data);
    return (0);
}

int key_release(int keycode, t_data *data)
{
    data->keys[keycode] = 0;
    return (0);
}

void handle_movement(t_data *data)
{
    // Вперёд
    if (data->keys[XK_w]) {
        if (map[(int)(data->py)][(int)(data->px + data->dirX * MOVE_SPEED)] == 0)
            data->px += data->dirX * MOVE_SPEED;
        if (map[(int)(data->py + data->dirY * MOVE_SPEED)][(int)(data->px)] == 0)
            data->py += data->dirY * MOVE_SPEED;
    }

    // Назад
    if (data->keys[XK_s]) {
        if (map[(int)(data->py)][(int)(data->px - data->dirX * MOVE_SPEED)] == 0)
            data->px -= data->dirX * MOVE_SPEED;
        if (map[(int)(data->py - data->dirY * MOVE_SPEED)][(int)(data->px)] == 0)
            data->py -= data->dirY * MOVE_SPEED;
    }

    // Поворот влево
    if (data->keys[XK_a]) {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(ROT_SPEED) - data->dirY * sin(ROT_SPEED);
        data->dirY = oldDirX * sin(ROT_SPEED) + data->dirY * cos(ROT_SPEED);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(ROT_SPEED) - data->planeY * sin(ROT_SPEED);
        data->planeY = oldPlaneX * sin(ROT_SPEED) + data->planeY * cos(ROT_SPEED);
    }

    // Поворот вправо
    if (data->keys[XK_d]) {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(-ROT_SPEED) - data->dirY * sin(-ROT_SPEED);
        data->dirY = oldDirX * sin(-ROT_SPEED) + data->dirY * cos(-ROT_SPEED);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(-ROT_SPEED) - data->planeY * sin(-ROT_SPEED);
        data->planeY = oldPlaneX * sin(-ROT_SPEED) + data->planeY * cos(-ROT_SPEED);
    }
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

int main() {
    t_data data;

    data.px = 2.5;
    data.py = 2.5;
    data.dirX = -1;
    data.dirY = 0;
    data.planeX = 0;
    data.planeY = FOV;
    gettimeofday(&data.prev_time, NULL);

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3D with texture");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length, &data.endian);

    // Загрузка текстуры
    int w, h;
    data.wall.img = mlx_xpm_file_to_image(data.mlx, "greystone.xpm", &w, &h);
    data.wall.data = (int *)mlx_get_data_addr(data.wall.img, &data.wall.bpp, &data.wall.line_length, &data.wall.endian);

    mlx_loop_hook(data.mlx, render, &data);
    mlx_hook(data.win, 2, 1L << 0, key_press, &data);    // KeyPress
    mlx_hook(data.win, 3, 1L << 1, key_release, &data);  // KeyRelease
    mlx_hook(data.win, 17, 0, close_win, &data);
    mlx_loop(data.mlx);
}
