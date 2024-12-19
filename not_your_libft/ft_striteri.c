/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:22:16 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 14:45:04 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	counter;

	if (!s || !f)
	{
		return ;
	}
	counter = 0;
	while (s[counter])
	{
		f(counter, &s[counter]);
		counter++;
	}
}
/*#include <stdio.h>
static void	ft_toupper_mapi(unsigned int i, char *c)
{
	(void)i;
	*c = (char)ft_toupper((int)(*c));
}
int	main(void)
{
	char s[] = "hello world!";
	ft_striteri(s, ft_toupper_mapi);
	printf("%s\n", s);
	return (0);
}*/