/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:43:46 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 14:59:40 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	counter;

	counter = ft_strlen(s);
	while (counter >= 0)
	{
		if (s[counter] == (char)c)
		{
			return ((char *)&s[counter]);
		}
		counter--;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[counter]);
	}
	return (NULL);
}
