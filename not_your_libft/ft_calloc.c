/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:56:05 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 15:46:35 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number_blocks, size_t size)
{
	char	*ptr;

	ptr = malloc(number_blocks * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, number_blocks * size);
	return (ptr);
}
/*#include <stdio.h>
int main()
{
	char *ptr = ft_calloc(10, 10);
	printf("%s", ptr);
}*/