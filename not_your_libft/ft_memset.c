/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:20:12 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/11 21:59:10 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t length)
{
	size_t			counter;
	unsigned char	*ptr;

	counter = 0;
	ptr = dest;
	while (counter < length)
	{
		ptr[counter] = (unsigned char)c;
		counter++;
	}
	return (dest);
}
