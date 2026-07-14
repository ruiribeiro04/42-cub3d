/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:20:34 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 19:39:05 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_elem = ft_lstnew(content);
		if (!new_elem)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}

/*
#include <stdio.h>
#include <string.h>

// Function to apply to each node content
void	*to_uppercase(void *content)
{
	char *original = (char *)content;
	char *result = strdup(original);
	int i = 0;
	
	if (!result)
		return (NULL);
	
	while (result[i])
	{
		if (result[i] >= 'a' && result[i] <= 'z')
			result[i] = result[i] - 32;
		i++;
	}
	
	return (result);
}

// Delete function for content
void	del_content(void *content)
{
	free(content);
}

// Helper function to print list
void	print_list(t_list *lst, char *label)
{
	t_list *current = lst;
	int i = 0;
	
	printf("%s:\n", label);
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
	t_list *node1 = ft_lstnew(strdup("first node"));
	t_list *node2 = ft_lstnew(strdup("second node"));
	t_list *node3 = ft_lstnew(strdup("third node"));
	
	// Build the list
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);
	
	// Print the original list
	print_list(list, "Original list");
	
	// Create a new list by mapping the original list
	t_list *new_list = ft_lstmap(list, to_uppercase, del_content);
	
	// Print the new list
	print_list(new_list, "New list (uppercase)");
	
	// Free both lists
	ft_lstclear(&list, del_content);
	ft_lstclear(&new_list, del_content);
	
	return (0);
}
*/
