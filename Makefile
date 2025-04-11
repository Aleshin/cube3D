NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = main.c \
	src/render/render_frame.c src/render/draw_utils.c src/render/raycast_init.c \
	src/render/raycast_functions.c src/input/key_control.c src/input/movement.c \
	src/input/rotate.c src/textures/textures_utils.c src/init.c \
	src/parser/get_next_line.c src/parser/helper_input.c src/parser/helper_errors.c \
	src/parser/struct_init.c src/parser/flood_fill.c src/parser/handle_map.c src/parser/parser.c \
	src/converter/player_converter.c
OBJ = $(SRC:.c=.o)

MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES = -Iinclude -Isrc -I$(MLX_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
