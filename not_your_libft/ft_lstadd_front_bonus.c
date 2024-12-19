/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:21:22 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 11:19:44 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
	{
		return ;
	}
	new->next = *lst;
	*lst = new;
}
/*#include <stdio.h>
int	main(void)
{
	t_list  *head = NULL;

	t_list  *node1 = ft_lstnew("lwla");
	t_list  *node2 = ft_lstnew("tanya");
	t_list  *node3 = ft_lstnew("la5ra");

	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);

	printf("%s -> %s -> %s\n", (char *)head->content,
	(char *)head->next->content,
	(char *)head->next->next->content );
}*/
