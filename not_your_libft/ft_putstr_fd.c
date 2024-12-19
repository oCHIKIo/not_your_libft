/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:17:12 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/09 16:06:04 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
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
}
