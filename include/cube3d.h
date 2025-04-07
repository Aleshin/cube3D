/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:21:00 by saleshin          #+#    #+#             */
/*   Updated: 2025/04/06 20:21:00 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUBE3D_H
# define CUBE3D_H

/* ────── System Includes ────── */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx.h"

/* ────── Game Settings ────── */
# define WIDTH 1280
# define HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAP_WIDTH 6
# define MAP_HEIGHT 5
# define FOV 0.66
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.03

/* ────── Texture Structures ────── */
typedef struct s_tex
{
	char	*path;
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_tex;

typedef struct s_textures
{
	t_tex	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
}	t_textures;

/* ────── Raycasting ────── */
typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		side;
	double	perp_wall_dist;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_ray;

typedef struct s_dda
{
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
}	t_dda;

/* ────── Drawing ────── */
typedef struct s_draw
{
	int		x;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_draw;

/* ────── Game State ────── */
typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				keys[65536];
	struct timeval	prev_time;
	double			frame_time;

	t_textures		textures;

	double			px;
	double			py;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				map[MAP_HEIGHT][MAP_WIDTH];
}	t_data;

/* ────── Init ────── */
void	init_data(t_data *data);
void	init_map(t_data *data);
void	init_player(t_data *data);
void	init_window(t_data *data);

/* ────── Input ────── */
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	handle_movement(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	strafe_left(t_data *data);
void	strafe_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

/* ────── Rendering ────── */
int		render(t_data *data);
void	render_frame(t_data *data);
void	cast_ray(t_data *data, int x, t_ray *ray);
void	draw_wall(t_data *data, int x, t_ray *ray);
void	draw_textured_line(t_data *data, t_tex *tex, t_draw *d);
void	draw_ceiling(t_data *data, int x, int draw_start, int color);
void	draw_floor(t_data *data, int x, int draw_end, int color);

/* ────── Raycasting ────── */
void	init_ray(t_data *data, int x, t_ray *ray);
void	init_steps(t_data *data, t_ray *ray, t_dda *dda);
void	perform_dda(t_data *data, t_ray *ray, t_dda *dda);
void	calculate_projection(t_ray *ray);
void	calculate_texture(t_data *data, t_ray *ray);

/* ────── Textures ────── */
void	load_textures(t_data *data);
void	load_single_texture(void *mlx, t_tex *tex);
t_tex	*get_wall_tex(t_data *data, int side,
			double ray_dir_x, double ray_dir_y);

/* ────── Utils ────── */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		close_win(void *param);
char	*ft_strdup(const char *s);

#endif
