/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:58:01 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 11:10:18 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}
/*#include <stdio.h>
int	main(void)
{
	t_list  *head = NULL;
	t_list  *node1 = ft_lstnew("ABC");
	t_list  *node2 = ft_lstnew("123");
	t_list  *node3 = ft_lstnew("XYZ");



	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);



	t_list *temp = head;
	printf("LISTE KAMLA: ");
	while (temp != NULL)
	{
		printf("%s -> ", (char *)temp->content);
		temp = temp->next;
	}
	printf("NULL\n");



	t_list *last = ft_lstlast(head);
	printf("LAST NODE: %s\n", (char *)last->content);

	return (0);
}*/