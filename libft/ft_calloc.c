/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:14:49 by emikhayl          #+#    #+#             */
/*   Updated: 2023/09/26 22:26:59 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*contiguously allocates enough space for count objects that are size bytes of
memory each and returns a pointer to the allocated memory. The allocated 
memory is filled with bytes of value zero.*/

#include <stddef.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
