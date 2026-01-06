#include "cub3d.h"

int draw_loop(t_game *game)
{
    t_player *player = &game->player;

    move_player(player);
    clear_image(game);

    if (DEBUG)
    {
        draw_square(player->x, player->y, 10, 0x00FF00, game);
        draw_map(game);
    }

    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;

    while (i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

int	main(void)
{
	t_game	game;

	//if (ft_init_game == 1)
	//	ft_error_exit(game, "PC Desligou-se, Mano");
	/*
	1. Initi Game Struct
	2. Parsing do Mapa
	3. Load das Texturas
	4. Init do Player
	5. Init do MLX
	6. Game Loop
	7. Free Game
	*/

	init_game(&game);
    
    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
	return (0);
}