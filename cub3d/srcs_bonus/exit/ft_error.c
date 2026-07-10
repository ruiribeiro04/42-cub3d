/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:20:57 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_error.c
 * @brief Error and cleanup helpers - free resources and print error messages.
 *
 * Contains functions that free game resources and report errors to the
 * user.
 */

#include "cub3d.h"

/**
 * @brief Free game resources and report an error to the user on stderr.
 *
 * If @p game is non-NULL, calls ft_free_game() on it first.  Always
 * prints "Error\\n<error_msg>\\n" to stderr (fd 2).  Returns 1 so
 * callers can use the idiom: return (ft_error(game, "msg"));
 *
 * @param game      Pointer to the game structure; may be NULL (NULL-safe).
 * @param error_msg Human-readable error description, printed after "Error\\n".
 * @return Always 1 to allow the return (ft_error(...)) idiom.
 */
/**
 * @ingroup exit
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
