NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP

SRC_DIR		= src
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

LIBFT		= $(LIBFT_DIR)/libft.a
MLX_LIB		= $(MLX_DIR)/libmlx.a

LIBFT_SRC	= $(wildcard $(LIBFT_DIR)/*.c)
MLX_SRC		= $(wildcard $(MLX_DIR)/*.c)

MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INCLUDES	= -Iinclude -I$(SRC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

SRC			= main.c \
			src/render/render_frame.c \
			src/render/draw_utils.c \
			src/render/raycast_init.c \
			src/render/raycast_functions.c \
			src/input/key_control.c \
			src/input/movement.c \
			src/input/rotate.c \
			src/textures/textures_utils.c \
			src/init.c \
			src/parser/get_next_line.c \
			src/parser/helper_input.c \
			src/parser/helper_errors.c \
			src/parser/struct_init.c \
			src/parser/flood_fill.c \
			src/parser/handle_map.c \
			src/parser/parser.c \
			src/converter/player_converter.c \
			src/converter/colors_converter.c

OBJ			= $(SRC:.c=.o)
DEP			= $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

$(LIBFT): $(LIBFT_SRC)
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB): $(MLX_SRC)
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ) $(DEP)
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
