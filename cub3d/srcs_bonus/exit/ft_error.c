/**
 * @file ft_error.c
 * @brief Error and cleanup helpers - free resources and print error messages.
 *
 * Contains functions that free game resources and report errors to the
 * user.
 */

#include "cub3d.h"

/**
 * @brief Responsible for freeing the game and 
 * instructing the user what went wrong
 * 
 * @param game Game struct
 * @param error_msg Message to show to user
 * @return int Always returns 1 to indicate an error occurred
 */
int	ft_error(t_game *game, char *error_msg)
{
	if (game)
		ft_free_game(game);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}
