/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:28:15 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 16:35:10 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}

/*
#include <stdio.h>

// Custom delete function
void	del_content(void *content)
{
	// For string content, we don't need to free it if it's a string literal
	// If it was dynamically allocated, we would free it here
	(void)content;
	printf("Content deleted\n");
}

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
	// Create a list with some nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	
	node1->next = node2;
	node2->next = node3;
	
	// Print the initial list
	printf("Initial list:\n");
	print_list(node1);
	
	// Delete the middle node (node2)
	printf("Deleting node2...\n");
	t_list *temp = node1->next;
	node1->next = node3;
	ft_lstdelone(temp, del_content);
	
	// Print the list after deletion
	printf("List after deletion:\n");
	print_list(node1);
	
	// Free remaining nodes
	while (node1)
	{
		temp = node1;
		node1 = node1->next;
		ft_lstdelone(temp, del_content);
	}
	
	return (0);
}
*/
