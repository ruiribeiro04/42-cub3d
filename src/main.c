/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include "graphics.h"
#include "player.h"
#include <stdlib.h>
#include <libft.h>

static int	validate_args(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		return (cub_error_int("Usage: ./cub3D <map.cub>"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_game		game;

	if (validate_args(argc, argv) < 0)
		return (1);
	config = parse_cub_file(argv[1]);
	if (!config)
		return (1);
	player_init_direction(&config->player);
	ft_memset(&game, 0, sizeof(t_game));
	game.config = config;
	if (game_init(&game, config) < 0)
	{
		game_cleanup(&game);
		free_config(config);
		return (1);
	}
	game_run(&game);
	game_cleanup(&game);
	free_config(config);
	return (0);
}
