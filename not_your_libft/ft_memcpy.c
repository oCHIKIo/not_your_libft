/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:47:49 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/11 22:58:36 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t length)
{
	char	*sr;
	char	*dt;
	size_t	counter;

	if (!dest && !src)
	{
		return (NULL);
	}
	sr = (char *)src;
	dt = (char *)dest;
	counter = 0;
	while (counter < length)
	{
		dt[counter] = sr[counter];
		counter++;
	}
	return (dt);
}
