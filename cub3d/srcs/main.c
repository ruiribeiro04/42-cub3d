/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:20:32 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Entry point: parse arguments, init game, start the MLX loop.
 */

#include "cub3d.h"

/**
 * @ingroup graphics
 */
int	ft_draw_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_player_move(game);
	ft_clear_image(game, 0x00000000);
	if (ft_raycasting(game) == 1)
		ft_error(game, "Raycasting failed!");
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

static int	ft_key_press_hook(int keycode, void *param)
{
	return (ft_input_key_press(keycode, (t_game *)param));
}

static int	ft_key_release_hook(int keycode, void *param)
{
	return (ft_input_key_release(keycode, (t_game *)param));
}

static int	ft_exit_hook(void *param)
{
	return (ft_exit_game((t_game *)param));
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
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK,
		(int (*)())ft_key_press_hook, &game);
	mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK,
		(int (*)())ft_key_release_hook, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		(int (*)())ft_exit_hook, &game);
	mlx_loop_hook(game.mlx, (int (*)())ft_draw_loop, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game);
	return (0);
}
