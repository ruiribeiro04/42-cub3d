/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:20:04 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file player.c
 * @brief Player state and movement update helpers.
 */

#include "cub3d.h"

static void	ft_player_rotate_player(t_player *player)
{
	float	rot;
	float	old_dir_x;
	float	old_plane_x;

	rot = 0.0f;
	if (player->left_rotate)
		rot = -ROTATE_SPEED;
	if (player->right_rotate)
		rot = ROTATE_SPEED;
	if (rot == 0.0f)
		return ;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}

static int	ft_player_check_collision(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	j;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			map_x = (int)(x + i * COLLISION_MARGIN);
			map_y = (int)(y + j * COLLISION_MARGIN);
			if (map_x < 0 || map_x >= game->map_width)
				return (1);
			if (map_y < 0 || map_y >= game->map_height)
				return (1);
			if (game->map[map_y][map_x] == '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	ft_player_move_forward_back(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->player.key_up)
	{
		new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
	if (game->player.key_down)
	{
		new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
}

static void	ft_player_move_strafe(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->player.key_left)
	{
		new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
	if (game->player.key_right)
	{
		new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
}

/**
 * @ingroup player
 */
void	ft_player_move(t_game *game)
{
	ft_player_rotate_player(&game->player);
	ft_player_move_forward_back(game);
	ft_player_move_strafe(game);
}
