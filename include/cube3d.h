#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx.h"

// Настройки окна и карты
# define WIDTH 640
# define HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAP_WIDTH 6
# define MAP_HEIGHT 5
# define FOV 0.66
# define MOVE_SPEED 0.005
# define ROT_SPEED 0.003

// Структуры
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
    int keys[65536];

    struct timeval prev_time;
    double frame_time;

    t_tex wall;

    double px, py;
    double dirX, dirY;
    double planeX, planeY;
    int map[MAP_HEIGHT][MAP_WIDTH];
}   t_data;

// Прототипы основных функций
void	init_map(t_data *data);
int     render(t_data *data);
int     close_win(void *param);
int     key_press(int keycode, t_data *data);
int     key_release(int keycode, t_data *data);
void    handle_movement(t_data *data);
void    render_frame(t_data *data);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

void	init_player(t_data *data);
void	init_window(t_data *data);
void	load_textures(t_data *data);

#endif
