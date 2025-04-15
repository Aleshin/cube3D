/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:39:04 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:08 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	err_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nFailed to open file\n");
		return (-1);
	}
	return (fd);
}

void	print_err_exit(char *str)
{
	if (!str)
		exit (0);
	printf("Error\n");
	printf("%s", str);
	exit (0);
}

int	print_err(char *str, char *id, int err)
{
	if (!str)
		return (0);
	printf("\033[1;31mError\n%s\033[0m\n", str);
	if (id)
		printf("\033[1;31m%s\033[0m\n", id);
	return (err);
}

char	*print_err_ptr(char *str)
{
	printf("\033[1;31mError\n%s\033[0m\n", str);
	return (NULL);
}
