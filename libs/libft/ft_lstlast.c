/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:35:49 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 15:56:31 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (!current)
		return (NULL);
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

/*
#include <stdio.h>

int	main(void)
{
	t_list *list = NULL;
	t_list *last;
	
	// Test with empty list
	last = ft_lstlast(list);
	printf("Last node of empty list: %p\n\n", last);
	
	// Create and add some nodes
	t_list *node1 = ft_lstnew("First node");
	list = node1;
	
	last = ft_lstlast(list);
	printf("List with 1 node:\n");
	printf("Last node content: %s\n\n", (char *)last->content);
	
	t_list *node2 = ft_lstnew("Second node");
	node1->next = node2;
	
	last = ft_lstlast(list);
	printf("List with 2 nodes:\n");
	printf("Last node content: %s\n\n", (char *)last->content);
	
	t_list *node3 = ft_lstnew("Third node");
	node2->next = node3;
	
	last = ft_lstlast(list);
	printf("List with 3 nodes:\n");
	printf("Last node content: %s\n", (char *)last->content);
	
	// Free allocated memory
	while (list)
	{
		t_list *temp = list;
		list = list->next;
		free(temp);
	}
	
	return (0);
}
*/
