/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:23:10 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/15 00:20:49 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *ndl, size_t len)
{
	size_t	c;
	size_t	b;

	c = 0;
	if (*ndl == '\0')
		return ((char *)hs);
	if (len == 0)
		return (NULL);
	while (hs[c] && c < len)
	{
		b = 0;
		while (hs[c + b] && ndl[b] && hs[c + b] == ndl[b] && (c + b) < len)
		{
			b++;
		}
		if (ndl[b] == '\0')
		{
			return ((char *)&hs[c]);
		}
		c++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	const char *haystack = "Hello, world!";
	const char *needle = "world";
	size_t len = 0;
	char *result = ft_strnstr(haystack, needle, len);
	printf("%s\n", result);
}*/