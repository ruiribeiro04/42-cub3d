/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <stdlib.h>
#include <libft.h>

/*
 * Frees a NULL-terminated array of strings, then the array itself.
 * NULL-safe. File-local: only used by ft_free_config().
 */
static void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_config	*ft_alloc_config(void)
{
	t_config	*cfg;

	cfg = (t_config *)malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	ft_memset(cfg, 0, sizeof(t_config));
	return (cfg);
}

static void	free_texture_paths(t_texture_paths *t)
{
	free(t->north);
	free(t->south);
	free(t->west);
	free(t->east);
}

void	ft_free_config(t_config *config)
{
	if (!config)
		return ;
	free_texture_paths(&config->textures);
	if (config->map.grid)
		free_str_array(config->map.grid);
	free(config->sprite_texture);
	free(config->door_texture);
	free(config->sprite_positions);
	free(config);
}
