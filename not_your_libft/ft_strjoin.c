/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:53:00 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 13:54:17 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	counter;
	size_t	bounter;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	counter = 0;
	while (counter < ft_strlen(s1))
	{
		str[counter] = s1[counter];
		counter++;
	}
	bounter = 0;
	while (bounter < ft_strlen(s2))
	{
		str[counter + bounter] = s2[bounter];
		bounter++;
	}
	str[counter + bounter] = '\0';
	return (str);
}
/*#include <stdio.h>

int	main(void)
{
	char *s1 = "";
	char *s2 = "World";
	char *str = ft_strjoin(s1, s2);
	printf("%s\n", str);
}*/
