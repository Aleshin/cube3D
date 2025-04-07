NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	src/render/render_frame.c \
	src/render/draw_utils.c \
	src/render/raycast_init.c \
	src/render/raycast_functions.c \
	src/input/key_control.c \
	src/input/movement.c \
	src/input/rotate.c \
	src/textures/textures_utils.c \
	src/init.c
OBJ = $(SRC:.c=.o)

MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES = -Iinclude -Isrc -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
