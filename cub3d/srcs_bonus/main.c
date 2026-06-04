/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:23:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Bonus entry point: parse arguments, init game, start the MLX loop.
 */

#include "cub3d.h"

/**
 * @ingroup graphics
 */
int	ft_draw_loop(t_game *game)
{
	ft_player_move(game);
	ft_clear_image(game, 0x00000000);
	if (ft_raycasting(game) == 1)
	{
		game->error_flag = true;
		return (1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map_file.cub>\n", STDERR_FILENO);
		return (1);
	}
	if (ft_init_game(&game, argv[1]) == 1)
	{
		ft_error(&game, "Failed to Initialize the Game!");
		return (1);
	}
	mlx_mouse_hide(game.mlx, game.win);
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, ft_input_key_press, &game);
	mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, ft_input_key_release,
		&game);
	mlx_hook(game.win, MOTION_NOTIFY, POINTER_MOTION_MASK, ft_input_mouse_move,
		&game);
	mlx_hook(game.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, ft_exit_game,
		&game);
	mlx_loop_hook(game.mlx, ft_draw_loop, &game);
	mlx_loop(game.mlx);
	if (game.error_flag)
		ft_putstr_fd("Error\nRaycasting failed!\n", STDERR_FILENO);
	ft_free_game(&game);
	return (0);
}
