/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:57:32 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 15:10:25 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	*lst = new;
	new->next = temp;
}

/*
#include <stdio.h>

// Helper function to print list
void	print_list(t_list *lst)
{
	t_list *current = lst;
	int i = 0;
	
	if (!current)
		printf("Empty list\n");
	
	while (current)
	{
		printf("Node %d: %s\n", i++, (char *)current->content);
		current = current->next;
	}
	printf("\n");
}

int	main(void)
{
	t_list *list = NULL;
	
	// Create some nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	
	// Initial empty list
	printf("Initial list:\n");
	print_list(list);
	
	// Add first node to front
	ft_lstadd_front(&list, node1);
	printf("After adding node1:\n");
	print_list(list);
	
	// Add second node to front
	ft_lstadd_front(&list, node2);
	printf("After adding node2:\n");
	print_list(list);
	
	// Add third node to front
	ft_lstadd_front(&list, node3);
	printf("After adding node3:\n");
	print_list(list);
	
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
