/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:16:47 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 10:57:43 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}
/*#include <stdio.h>
int	main(void)
{
	t_list  *header = NULL;
	t_list  *node1 = ft_lstnew("world!");
	t_list  *node2 = ft_lstnew("Hello");
	t_list  *node3 = ft_lstnew("world!");
	t_list  *node4 = ft_lstnew("Hello");

	ft_lstadd_front(&header, node1);
	ft_lstadd_front(&header, node2);
	ft_lstadd_front(&header, node3);
	ft_lstadd_front(&header, node4);

	printf("%d\n", ft_lstsize(header));

	free(node1);
	free(node2);
	free(node3);
	free(node4);
}*/