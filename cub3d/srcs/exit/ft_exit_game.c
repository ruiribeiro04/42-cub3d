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
	ft_putstr_fd("GANHASTE POCKET ES O MAIOR PLAYER DO SERVER", STDOUT_FILENO);
	// exit(EXIT_SUCCESS);
	return (0);
}
