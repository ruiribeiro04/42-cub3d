/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tabs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

static size_t	count_tabs(const char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t')
			count++;
		i++;
	}
	return (count);
}


static void	copy_expanded(char *out, const char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t')
		{
			out[j++] = ' ';
			out[j++] = ' ';
			out[j++] = ' ';
			out[j++] = ' ';
		}
		else
			out[j++] = line[i];
		i++;
	}
	out[j] = '\0';
}


char	*ft_expand_tabs(const char *line)
{
	size_t	tabs;
	size_t	new_len;
	char	*out;

	if (!line)
		return (NULL);
	tabs = count_tabs(line);
	new_len = ft_strlen(line) + tabs * (TAB_WIDTH - 1);
	out = (char *)malloc(new_len + 1);
	if (!out)
		return (NULL);
	copy_expanded(out, line);
	return (out);
}


int	ft_process_map_line(char **line)
{
	char	*expanded;

	expanded = ft_expand_tabs(*line);
	if (!expanded)
	{
		ft_cub_error("Memory allocation failed");
		free(*line);
		*line = NULL;
		return (-1);
	}
	free(*line);
	*line = expanded;
	if (ft_validate_map_line(expanded) < 0)
	{
		free(expanded);
		*line = NULL;
		return (-1);
	}
	return (0);
}
