/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:34:27 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 13:55:40 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*root;

	root = malloc(sizeof(t_list));
	if (!root)
		return (NULL);
	root->content = content;
	root->next = NULL;
	return (root);
}

/*
#include <stdio.h>

int	main(void)
{
	// Test with string content
	char *str = "Test content";
	t_list *node1 = ft_lstnew(str);
	
	printf("Node 1 content: %s\n", (char *)node1->content);
	printf("Node 1 next: %p\n\n", node1->next);
	
	// Test with integer content
	int *num = malloc(sizeof(int));
	*num = 42;
	
	t_list *node2 = ft_lstnew(num);
	printf("Node 2 content: %d\n", *(int *)node2->content);
	printf("Node 2 next: %p\n\n", node2->next);
	
	// Test with NULL content
	t_list *node3 = ft_lstnew(NULL);
	printf("Node 3 content: %p\n", node3->content);
	printf("Node 3 next: %p\n", node3->next);
	
	// Free allocated memory
	free(node1);
	free(num);
	free(node2);
	free(node3);
	
	return (0);
}
*/
