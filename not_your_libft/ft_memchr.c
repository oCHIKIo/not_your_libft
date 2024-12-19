/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:06:18 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 11:33:29 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*str;
	unsigned char		ch;
	size_t				counter;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	counter = 0;
	while (counter < n)
	{
		if (str[counter] == ch)
			return (&str[counter]);
		counter++;
	}
	return (NULL);
}
