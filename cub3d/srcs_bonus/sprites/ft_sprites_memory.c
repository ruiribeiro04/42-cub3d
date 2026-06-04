/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:43 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_sprites_memory.c
 * @brief Allocate and free sprite resources.
 */

#include "cub3d.h"

static int	load_single_frame(t_game *g, t_sprite *sp, char *base, int i)
{
	char	*number;
	char	*path;
	char	*full_path;

	number = ft_itoa(i);
	path = ft_strjoin(base, number);
	full_path = ft_strjoin(path, ".xpm");
	free(number);
	free(path);
	if (ft_load_texture(g, &sp->frames[i], full_path))
	{
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

/**
 * @ingroup sprites
 */
int	ft_load_animation(t_game *game, t_sprite *sprite, char *base_path,
		int count)
{
	int	i;

	sprite->frames = malloc(sizeof(t_texture) * count);
	if (!sprite->frames)
		return (1);
	sprite->frame_count = count;
	sprite->current_frame = 0;
	sprite->anim_time = 0;
	i = 0;
	while (i < count)
	{
		if (load_single_frame(game, sprite, base_path, i))
			return (1);
		i++;
	}
	return (0);
}

static void	free_sprite_frames(t_game *game, t_sprite *sprite)
{
	int	j;

	j = 0;
	while (j < sprite->frame_count)
	{
		if (sprite->frames[j].img)
			mlx_destroy_image(game->mlx, sprite->frames[j].img);
		j++;
	/**
	 * @ingroup sprites
	 */
	}
	free(sprite->frames);
}

void	ft_free_sprites(t_game *game)
{
	int	i;

	if (game->z_buffer)
		free(game->z_buffer);
	if (game->sprites)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			if (game->sprites[i].frames)
				free_sprite_frames(game, &game->sprites[i]);
			i++;
		}
		free(game->sprites);
	}
}
