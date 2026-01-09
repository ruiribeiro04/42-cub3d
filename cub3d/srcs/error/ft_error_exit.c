#include "cub3d.h"

void	ft_free_game(t_game game)
{
	(void)game;
}

void	ft_error_exit(t_game game, char *error_msg)
{
	(void)error_msg;
	ft_free_game(game);
	//ft_putstr_fd("Error: ", STDERR_FILENO);
	//ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
