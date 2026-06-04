/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:01 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_exit_game.c
 * @brief Shutdown hooks for cleanly exiting the game.
 *
 * Provides the exit handler called by MLX events to terminate the
 * rendering loop and perform any final logging.
 */

#include "cub3d.h"

/**
 * @brief Exits the game cleanly by ending the MLX loop
 *
 * @param game Game struct
 * @return int Always returns 0 to indicate successful exit
 */
int	ft_exit_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	ft_putstr_fd("GANHASTE POCKET ES O MAIOR PLAYER DO SERVER",
		STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
