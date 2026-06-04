/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:18:57 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_free_game.c
 * @brief Free all game resources on exit.
 */

#include "cub3d.h"

/**
 * @brief Frees the map allocated in memory
 * 
 * @param map Map that will be freed
 */
static void	ft_free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/**
 * @brief Frees variables in the `game` struct that are related to minilibx
 * 
 * @param game Game struct
 */
static void	ft_free_mlx(t_game *game)
{
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * @brief Frees the memory allocated for textures in `game` struct
 * 
 * @param game Game struct
 */
static void	ft_free_textures(t_game *game)
{
	if (game->tex_north.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_north.img);
	if (game->tex_south.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_south.img);
	if (game->tex_east.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_east.img);
	if (game->tex_west.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_west.img);
}

/**
 * @brief Frees the texture paths and sets them to `NULL` for memory safety
 * 
 * @param game Game struct
 */
static void	ft_free_config_paths(t_game *game)
{
	if (game->path_north)
	{
		free(game->path_north);
		game->path_north = NULL;
	}
	if (game->path_south)
	{
		free(game->path_south);
		game->path_south = NULL;
	}
	if (game->path_east)
	{
		free(game->path_east);
		game->path_east = NULL;
	}
	if (game->path_west)
	{
		free(game->path_west);
		game->path_west = NULL;
	}
}

/**
 * @brief Frees all allocated variables to safely exit
 * 
 * @param game Game struct
  * @ingroup error
 */
void	ft_free_game(t_game *game)
{
	if (!game)
		return ;
	ft_free_map(game->map);
	game->map = NULL;
	ft_free_textures(game);
	ft_free_config_paths(game);
	ft_free_mlx(game);
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
}
