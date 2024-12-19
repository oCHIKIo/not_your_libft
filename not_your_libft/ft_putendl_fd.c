/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:25:10 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 11:43:33 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	counter;

	counter = 0;
	if (fd < 0)
	{
		return ;
	}
	if (!s)
	{
		return ;
	}
	while (s[counter])
	{
		write(fd, &s[counter], 1);
		counter++;
	}
	write (fd, "\n", 1);
}
