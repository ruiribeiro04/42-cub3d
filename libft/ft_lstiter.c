/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:12:55 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:14:32 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	if (!lst || !f)
		return ;
	current = lst;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}

/*
#include <stdio.h>

// Example function to apply to each node
void	print_content(void *content)
{
	printf("Content: %s\n", (char *)content);
}

// Function to modify the content
void	uppercase_content(void *content)
{
	char *str = (char *)content;
	int i = 0;
	
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
}

int	main(void)
{
	t_list *list = NULL;
	
	// Create modified strings (so we can modify them)
	char str1[] = "first node";
	char str2[] = "second node";
	char str3[] = "third node";
	
	// Create some nodes
	t_list *node1 = ft_lstnew(str1);
	t_list *node2 = ft_lstnew(str2);
	t_list *node3 = ft_lstnew(str3);
	
	// Build the list
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);
	
	// Print initial contents
	printf("Initial list contents:\n");
	ft_lstiter(list, print_content);
	printf("\n");
	
	// Apply uppercase function to each node
	printf("Applying uppercase function...\n");
	ft_lstiter(list, uppercase_content);
	
	// Print modified contents
	printf("Modified list contents:\n");
	ft_lstiter(list, print_content);
	
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
