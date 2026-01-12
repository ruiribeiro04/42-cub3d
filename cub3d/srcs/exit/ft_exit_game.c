#include "cub3d.h"

int    ft_exit_game(t_game *game)
{
    ft_free_game(game);
    ft_putstr_fd("GANHASTE POCKET ES O MAIOR PLAYER DO SERVER", STDOUT_FILENO);
    //exit(EXIT_SUCCESS);
    return (0);
}