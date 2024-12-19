/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:14:29 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 14:19:13 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (!dst)
		return (ft_strlen(src));
	while (src[counter] && counter < size - 1)
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
	return (ft_strlen(src));
}
/*#include <stdio.h>
int	main(void)
{
	char dest[10] = "BRO";
	char src[] = "WSUP";

	// Set size to 1 to copy only the first character
	printf("Length of src: %zu\n", ft_strlcpy(dest, src, 1));
	printf("Destination after copy: '%s'\n", dest);

	return (0);
}*/
