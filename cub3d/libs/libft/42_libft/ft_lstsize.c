/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:13:58 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:14:35 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	current = lst;
	if (!current)
		return (0);
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

/*
#include <stdio.h>

int	main(void)
{
	t_list *list = NULL;
	
	// Test with empty list
	printf("Size of empty list: %d\n", ft_lstsize(list));
	
	// Create and add some nodes
	t_list *node1 = ft_lstnew("Node 1");
	list = node1;
	printf("Size after adding 1 node: %d\n", ft_lstsize(list));
	
	t_list *node2 = ft_lstnew("Node 2");
	node1->next = node2;
	printf("Size after adding 2 nodes: %d\n", ft_lstsize(list));
	
	t_list *node3 = ft_lstnew("Node 3");
	node2->next = node3;
	printf("Size after adding 3 nodes: %d\n", ft_lstsize(list));
	
	t_list *node4 = ft_lstnew("Node 4");
	node3->next = node4;
	printf("Size after adding 4 nodes: %d\n", ft_lstsize(list));
	
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
