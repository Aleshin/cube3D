// cub3d.h
#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
# include "game.h"

void	set_player_direction(t_game *game, t_player *player);
int	**convert_char_map_to_int(t_data data);

#endif
