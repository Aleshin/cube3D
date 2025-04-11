/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:49:14 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/11 18:49:17 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_cols(int i, t_data *data, int **map)
{
	size_t	j;

	j = 0;
	while (j < data->cols)
	{
		map[i][j] = data->map[i][j] - '0';
		if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
			|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			map[i][j] = 0;
		j++;
	}
}

//returns 
int	**convert_char_map_to_int(t_data data)
{
	int		**int_map;
	size_t	i;

	int_map = malloc(sizeof(int *) * data.rows);
	if (!int_map)
		return (NULL);
	i = 0;
	while (i < data.rows)
	{
		int_map[i] = malloc(sizeof(int) * data.cols);
		if (!int_map[i])
		{
			while (i > 0)
				free(int_map[--i]);
			return (free(int_map), NULL);
		}
		fill_cols(i, &data, int_map);
		i++;
	}
	return (int_map);
}

/// DElETE LATER, it is only for check
void	print_int_map(int **map, size_t rows, size_t cols)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (int)rows)
	{
		j = 0;
		while (j < (int)cols)
		{
			printf("%d", map[i][j]);
			if (j < (int)cols - 1)
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
}
