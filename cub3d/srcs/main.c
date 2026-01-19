#include "cub3d.h"

int	ft_draw_loop(t_game *game)
{
	ft_player_move(game);
	ft_clear_image(game, 0x00000000);
	if (ft_raycasting(game) == 1)
		ft_error(game, "Raycasting failed!");
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	if (ft_init_game(&game) == 1)
	    ft_error(&game, "Failed to Initialize the Game!");
	/*
	1. Init Game Struct ✅
	2. Parsing do Mapa
	3. Load das Texturas ✅
	4. Init do Player ✅
	5. Init do MLX ✅
	6. Game Loop ✅
	7. Free Game ✅
	*/
    
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, ft_input_key_press, &game);
	mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, ft_input_key_release, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, ft_exit_game, &game);
    
	mlx_loop_hook(game.mlx, ft_draw_loop, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game);
	return (0);
}
