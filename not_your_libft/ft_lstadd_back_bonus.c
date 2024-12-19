/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:42:03 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 11:18:35 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
/*#include <stdio.h>
int	main(void)
{
	t_list  *head = NULL;

	t_list  *node1 = ft_lstnew("lwla");
	t_list  *node2 = ft_lstnew("tanya");
	t_list  *node3 = ft_lstnew("la5ra");

	ft_lstadd_back(&head, node1);
	ft_lstadd_back(&head, node2);
	ft_lstadd_back(&head, node3);

	printf("%s -> %s -> %s\n",
		(char *)head->content,
		(char *)head->next->content,
		(char *)head->next->next->content );
}*/
