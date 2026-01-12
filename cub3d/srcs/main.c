#include "cub3d.h"

int	ft_draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int		i;
    
	player = &game->player;
	ft_player_move_player(player);
	ft_clear_image(game, 0x00000000);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - (PI / 6);
	i = 0;
	while (i < WIDTH)
	{
	ft_raycasting_draw_line(game, start_x, i);
	start_x += fraction;
	i++;
	}
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
	3. Load das Texturas
	4. Init do Player
	5. Init do MLX
	6. Game Loop
	7. Free Game ✅
	*/
    
	mlx_hook(game.win, 2, 1L<<0, ft_input_key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, ft_input_key_release, &game);
    
	mlx_loop_hook(game.mlx, ft_draw_loop, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game);
	return (0);
}
