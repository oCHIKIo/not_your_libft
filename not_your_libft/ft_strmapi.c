/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:57:28 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 14:40:05 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	unsigned int	counter;
	char			*ptr;

	if (!s || !f)
	{
		return (NULL);
	}
	counter = 0;
	length = ft_strlen(s);
	ptr = malloc(sizeof(char) * (length + 1));
	if (!ptr)
	{
		return (NULL);
	}
	while (counter < length)
	{
		ptr[counter] = f(counter, s[counter]);
		counter++;
	}
	ptr[counter] = '\0';
	return (ptr);
}

/*#include <stdio.h>
static  char	ft_toupper_mapi(unsigned int i, char c)
{
	(void)i;
	return (char)ft_toupper((int)c);
}
int	main(void)
{
	char *s = "hello world!";
	char *result = ft_strmapi(s, ft_toupper_mapi);
	printf("%s\n", result);
	free(result);
	return (0);
}*/