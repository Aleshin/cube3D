/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                            :+:      :+:    :+:   */
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
# include <stdlib.h>        // Memory allocation, exit
# include <unistd.h>        // Write, read
# include <stdio.h>         // Printf, perror
# include <math.h>          // Math functions
# include <sys/time.h>      // gettimeofday
# include <X11/X.h>         // X11 definitions
# include <X11/keysym.h>    // Key symbols
# include "mlx.h"           // MiniLibX graphics library

/* ────── Game Settings ────── */
# define WIDTH 1280         // Window width
# define HEIGHT 720         // Window height
# define TEX_WIDTH 64       // Texture width
# define TEX_HEIGHT 64      // Texture height
# define MAP_WIDTH 6        // Map width
# define MAP_HEIGHT 5       // Map height
# define FOV 0.66           // Field of view plane factor
# define MOVE_SPEED 0.03    // Movement speed
# define ROT_SPEED 0.03     // Rotation speed

/* ────── Texture Structures ────── */
typedef struct s_tex
{
	char	*path;          // Path to the texture file
	void	*img;           // Pointer to the MLX image
	int		*data;          // Pointer to texture pixel data
	int		width;          // Texture width in pixels
	int		height;         // Texture height in pixels
	int		bpp;            // Bits per pixel
	int		line_length;    // Bytes per line
	int		endian;         // Endian format (0 or 1)
}	t_tex;

typedef struct s_textures
{
	t_tex	north;          // North wall texture
	t_tex	south;          // South wall texture
	t_tex	east;           // East wall texture
	t_tex	west;           // West wall texture
}	t_textures;

/* ────── Raycasting ────── */
typedef struct s_ray
{
	double	ray_dir_x;       // Ray direction X
	double	ray_dir_y;       // Ray direction Y
	int		map_x;           // Map X coordinate
	int		map_y;           // Map Y coordinate
	int		side;            // Hit side: 0 = X, 1 = Y
	double	perp_wall_dist;  // Perpendicular wall distance
	int		draw_start;      // Wall draw start Y
	int		draw_end;        // Wall draw end Y
	int		tex_x;           // Texture X coordinate
	double	step;            // Step for texture
	double	tex_pos;         // Starting texture position
}	t_ray;

typedef struct s_dda
{
	double	delta_x;     // Delta X distance
	double	delta_y;     // Delta Y distance
	double	side_x;      // Side distance X
	double	side_y;      // Side distance Y
	int		step_x;      // Step X direction
	int		step_y;      // Step Y direction
}	t_dda;

/* ────── Drawing ────── */
typedef struct s_draw
{
	int		x;           // Screen column X
	int		draw_start;  // Wall draw start Y
	int		draw_end;    // Wall draw end Y
	int		tex_x;       // Texture X coordinate
	double	step;        // Step size on texture
	double	tex_pos;     // Texture start position
}	t_draw;

/* ────── Game State ────── */
typedef struct s_game
{
	void			*mlx;           // MLX instance
	void			*win;           // Window pointer
	void			*img;           // Image buffer
	char			*addr;          // Image address
	int				bpp;            // Bits per pixel
	int				line_length;    // Bytes per line
	int				endian;         // Endian format
	int				keys[65536];    // Keys state array
	struct timeval	prev_time;      // Previous frame time
	double			frame_time;     // Time per frame
	t_textures		textures;       // Wall textures
	double			px;             // Player X position
	double			py;             // Player Y position
	double			dir_x;          // Direction vector X
	double			dir_y;          // Direction vector Y
	double			plane_x;        // Camera plane X
	double			plane_y;        // Camera plane Y
	int				map[MAP_HEIGHT][MAP_WIDTH]; // Map array
}	t_game;

/* ────── Init ────── */
void	init_game(t_game *data);          // Initialize the main game data structure
void	init_map(t_game *data);           // Initialize or load the game map
void	init_player(t_game *data);        // Set initial player position and direction
void	init_window(t_game *data);        // Initialize the game window with MLX

/* ────── Input ────── */
int		key_press(int keycode, t_game *data);    // Handle key press event
int		key_release(int keycode, t_game *data);  // Handle key release event
void	handle_movement(t_game *data);           // Process movement keys and update player
void	move_forward(t_game *data);              // Move player forward
void	move_backward(t_game *data);             // Move player backward
void	strafe_left(t_game *data);               // Move player to the left
void	strafe_right(t_game *data);              // Move player to the right
void	rotate_left(t_game *data);               // Rotate player's view left
void	rotate_right(t_game *data);              // Rotate player's view right

/* ────── Rendering ────── */
int		render(t_game *data);                             // Main rendering loop (hooked by MLX)
void	render_frame(t_game *data);                        // Render the full frame
void	cast_ray(t_game *data, int x, t_ray *ray);         // Cast a ray from player through the screen column
void	draw_wall(t_game *data, int x, t_ray *ray);        // Draw vertical wall slice for one ray
void	draw_textured_line(t_game *data, t_tex *tex, t_draw *d); // Draw a vertical line with texture
void	draw_ceiling(t_game *data, int x, int draw_start, int color); // Draw ceiling above the wall
void	draw_floor(t_game *data, int x, int draw_end, int color);     // Draw floor below the wall

/* ────── Raycasting ────── */
void	init_ray(t_game *data, int x, t_ray *ray);               // Initialize ray direction and position
void	init_steps(t_game *data, t_ray *ray, t_dda *dda);        // Calculate DDA steps and initial distances
void	perform_dda(t_game *data, t_ray *ray, t_dda *dda);       // Perform DDA to find wall hit
void	calculate_projection(t_ray *ray);                       // Calculate projected wall height
void	calculate_texture(t_game *data, t_ray *ray);            // Calculate texture coordinates

/* ────── Textures ────── */
void	load_textures(t_game *data);                            // Load all textures into memory
void	load_single_texture(void *mlx, t_tex *tex);             // Load one texture image
t_tex	*get_wall_tex(t_game *data, int side, double ray_dir_x,
			double ray_dir_y);                                // Return correct wall texture

/* ────── Utils ────── */
void	my_mlx_pixel_put(t_game *data, int x, int y, int color); // Draw a pixel into the image buffer
int		close_win(void *param);                                  // Close the game window and cleanup
char	*ft_strdup(const char *s);                                // Duplicate a string (libft)

#endif
