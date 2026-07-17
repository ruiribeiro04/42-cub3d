/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include "graphics.h"
#include "player.h"
#include <stdlib.h>
#include <libft.h>

static int	ft_validate_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
		return (ft_cub_error_int("Usage: ./cub3D <map.cub>"));
	if (!argv[1])
		return (ft_cub_error_int("Missing map argument"));
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		return (ft_cub_error_int("File must end with .cub"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_game		game;

	if (ft_validate_args(argc, argv) < 0)
		return (1);
	config = ft_parse_cub_file(argv[1]);
	if (!config)
		return (1);
	ft_player_init_direction(&config->player);
	ft_memset(&game, 0, sizeof(t_game));
	game.config = config;
	if (ft_game_init(&game, config) < 0)
	{
		ft_game_cleanup(&game);
		ft_free_config(config);
		return (1);
	}
	ft_game_run(&game);
	ft_game_cleanup(&game);
	ft_free_config(config);
	return (0);
}
