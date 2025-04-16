/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:39:04 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:08 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

char	**free_matrix(char **arr_of_words, int col)
{
	int	i;

	i = 0;
	while (i < col && arr_of_words[i])
	{
		free(arr_of_words[i]);
		i++;
	}
	free(arr_of_words);
	return (NULL);
}

static int	check_atoi(char **arr, int colors[3], int i)
{
	colors[i] = ft_atoi(arr[i]);
	if (colors[i] == -1)
	{
		free_matrix(arr, 3);
		return (print_err("Only unsigned int allowed", NULL, -1));
	}
	else if (colors[i] == -2)
	{
		free_matrix(arr, 3);
		return (print_err("Number out of range (0-255)", NULL, -1));
	}
	return (0);
}

int	colors_arr(int colors[3], char *str)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(str, ',');
	if (!arr)
		return (print_err("Split failed", NULL, -1));
	while (arr[i])
	{
		if (i >= 3)
		{
			free_matrix(arr, 3);
			return (print_err("3 parameters [R,G,B] expected", NULL, -1));
		}
		colors[i] = ft_atoi(arr[i]);
		if (check_atoi(arr, colors, i) == -1)
			return (-1);
		i++;
	}
	if (i != 3)
	{
		free_matrix(arr, 3);
		return (print_err("3 parameters [R,G,B] expected", NULL, -1));
	}
	return (free_matrix(arr, 3), 0);
}

//returns int color or -1 in case of error
int	set_color(char *str)
{
	int		colors[3];

	if (colors_arr(colors, str) == -1)
		return (-1);
	return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
}

// void	print_input(t_data data)
// {
// 	size_t	i;

// 	// printf("PRINT DATA IN FILLED STRUCT\n");
// 	// printf("NO '%s'\n", data.NO);
// 	// printf("SO '%s'\n", data.SO);
// 	// printf("WE '%s'\n", data.WE);
// 	// printf("EA '%s'\n", data.EA);
// 	// printf("Filled %d \n", data.filled);
// 	// printf("Floor %d\n", data.floor);
// 	// printf("Ceiling %d\n", data.ceiling);
// 	printf("MAP---------->\n");
// 	i = 0;
// 	while (i < data.rows)
// 	{
// 		printf("%s\n", data.map[i]);
// 		i++;
// 	}
// }
