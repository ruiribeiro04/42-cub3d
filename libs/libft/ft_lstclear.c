/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:38:05 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 16:48:18 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
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
	t_list *list = NULL;
	
	// Create some nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	
	// Build the list
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);
	
	// Print initial list
	printf("Initial list:\n");
	print_list(list);
	
	// Clear the list
	printf("Clearing the list...\n");
	ft_lstclear(&list, del_content);
	
	// Print list after clearing
	printf("List after clearing:\n");
	print_list(list);
	
	// Confirm that the list pointer is now NULL
	printf("list pointer: %p (should be NULL)\n", list);
	
	return (0);
}
*/
