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
#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
# include "game.h"

void	set_player_direction(t_game *game, t_player *player);
int		**convert_char_map_to_int(t_data data);
void	set_colors(t_game *game, t_data *colors);
#endif
