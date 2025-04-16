/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:19:08 by emikhayl          #+#    #+#             */
/*   Updated: 2023/09/18 19:37:24 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

//returns 0 if strings are equal, positive if 1st string is 
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
