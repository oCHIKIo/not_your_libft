/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:36:59 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/10 21:41:27 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dt;
	char	*st;

	dt = (char *)dest;
	st = (char *)src;
	if (st < dt)
	{
		while (n > 0)
		{
			dt[n - 1] = st[n - 1];
			n--;
		}
	}
	else
	{
		ft_memcpy(dt, st, n);
	}
	return (dt);
}
