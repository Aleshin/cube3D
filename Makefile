CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP
INCLUDES	= -Iinclude -Isrc -Ilibft -Iminilibx-linux
LDFLAGS		= -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm
RM			= rm -f

NAME		= cub3D

SRC = main.c \
	  src/render/render_frame.c src/render/draw_utils.c src/render/raycast_init.c \
	  src/render/raycast_functions.c src/input/key_control.c src/input/movement.c \
	  src/input/rotate.c src/textures/textures_utils.c src/init.c \
	  src/parser/get_next_line.c src/parser/helper_input.c src/parser/helper_errors.c \
	  src/parser/struct_init.c src/parser/flood_fill.c src/parser/handle_map.c \
	  src/parser/parser.c src/parser/helpers_map.c src/parser/helper_color.c \
	  src/parser/helper_parser.c \
	  src/converter/player_converter.c src/converter/colors_converter.c

OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

all: libs $(NAME)

libs:
	@$(MAKE) -C libft
	@$(MAKE) -C minilibx-linux

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP)

clean:
	@$(MAKE) -C libft clean
	@$(MAKE) -C minilibx-linux clean
	$(RM) $(OBJ) $(DEP)

fclean: clean
	@$(MAKE) -C libft fclean
	@$(MAKE) -C minilibx-linux clean
	$(RM) $(NAME)

re: fclean all

bonus:
	@echo "No bonus part implemented."

.PHONY: all clean fclean re libs bonus
