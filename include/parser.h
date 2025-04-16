/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:29:42 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:38:19 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

/* STRUCTS */
typedef struct s_point
{
	int		x;
	int		y;
}	t_point;

typedef struct s_player
{
	char	dir;
	t_point	pos;
}	t_player;

typedef struct s_data
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceiling;
	int			filled;
	int			inside;
	size_t		rows;
	size_t		cols;
	size_t		map_size;
	char		**map;
	t_player	me;
}	t_data;

/* ERRORS helper_errors.c*/
int		print_err(char *str, char *id, int err);
char	*print_err_ptr(char *str);
int		err_open(char *file);

/* GET_NEXT_LINE */
char	*get_next_line(int fd);

/* STRUCT INIT */
void	input_data_init(t_data *data);
void	free_data(t_data *data);

/* PARSING */
char	*get_filename(int arg, char **argv);
int		is_empty_or_whitespace(char *str);
int		ft_isspace(char c);
void	*get_texture_or_color(char *type, t_data *data);
char	*get_type(char *str);
char	**free_matrix(char **arr_of_words, int col);
int		check_identifier(char *str, t_data *data);
int		set_color(char *str);
int		parser(int argc, char **argv, t_data *data);

/* MAP CHECK */
int		store_raw_map(t_data *data, char *line);
int		normalize_map(t_data *data);
int		trim_empty_lines(t_data *data);
char	*trim_trailing_spaces(const char *str);
int		map_chars_ok(const t_data data);
int		map_ok(t_data *data);
int		handle_map(t_data *data, char *str);
int		map_begin(char *str);

#endif
