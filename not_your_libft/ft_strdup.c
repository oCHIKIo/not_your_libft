/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:05:35 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 12:40:14 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	length;
	size_t	counter;

	length = ft_strlen(str);
	ptr = malloc(sizeof(char) * (length + 1));
	if (!ptr)
	{
		return (NULL);
	}
	counter = 0;
	while (counter < length)
	{
		ptr[counter] = str[counter];
		counter++;
	}
	ptr[counter] = '\0';
	return (ptr);
}
