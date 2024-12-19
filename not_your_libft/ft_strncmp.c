/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:23:14 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 01:26:13 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			counter;
	unsigned char	*str1;
	unsigned char	*str2;

	counter = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[counter] || str2[counter]) && (counter < n))
	{
		if (str1[counter] > str2[counter])
		{
			return (str1[counter] - str2[counter]);
		}
		if (str1[counter] < str2[counter])
		{
			return (str1[counter] - str2[counter]);
		}
		counter++;
	}
	return (0);
}
