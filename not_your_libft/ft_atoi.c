/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:17:55 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/15 00:22:53 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	ct;
	int	result;
	int	neg;

	ct = 0;
	result = 0;
	neg = 1;
	while (str[ct] == 32 || (str[ct] >= 9 && str[ct] <= 13))
		ct++;
	if (str[ct] == '+' || str[ct] == '-')
	{
		if (str[ct] == '-')
		{
			neg *= -1;
		}
		ct++;
	}
	while (str[ct] && (str[ct] >= '0' && str[ct] <= '9'))
	{
		result = result * 10 + (str[ct] - 48);
		ct++;
	}
	return (result * neg);
}
