/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

static char	*extract_sprite_path(const char *line)
{
	const char	*p;
	char		*path;
	size_t		len;

	p = line + 2;
	skip_spaces(&p);
	if (*p == '\0')
	{
		cub_error("Missing sprite texture path");
		return (NULL);
	}
	len = ft_strlen(p);
	while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t'))
		len--;
	path = (char *)malloc(len + 1);
	if (!path)
	{
		cub_error("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(path, p, len + 1);
	return (path);
}

int	parse_sprite_line(const char *line, t_config *cfg)
{
	char	*path;

	if (cfg->has_sprite)
		return (cub_error_int("Duplicate SP identifier"));
	if (line[2] != ' ' && line[2] != '\t')
		return (cub_error_int("SP id must be followed by ws"));
	path = extract_sprite_path(line);
	if (!path)
		return (-1);
	cfg->sprite_texture = path;
	cfg->has_sprite = 1;
	return (0);
}
