/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:50:05 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 14:01:43 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dest_size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	counter;

	dst_len = 0;
	src_len = 0;
	counter = 0;
	while (src[src_len])
		src_len++;
	if (dest_size == 0)
		return (src_len);
	while (dst[dst_len] && dst_len < dest_size)
		dst_len++;
	if (dst_len == dest_size)
		return (dest_size + src_len);
	while (src[counter] && (dst_len + counter) < (dest_size - 1))
	{
		dst[dst_len + counter] = src[counter];
		counter++;
	}
	dst[dst_len + counter] = '\0';
	return (dst_len + src_len);
}
