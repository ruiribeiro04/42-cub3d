#!/usr/bin/env python3
"""Generate clean main.c and run.c."""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 12:00:00'
    line4_name = name.ljust(51)
    by_content = f"{login} <{mail}>"
    line6_by = by_content.ljust(43)
    created_content = f"{created} by {login}"
    line8_created = created_content.ljust(41)
    updated_content = f"{updated} by {login}"
    line9_updated = updated_content.ljust(40)
    return (
        "/* ************************************************************************** */\n"
        "/*                                                                            */\n"
        "/*                                                        :::      ::::::::   */\n"
        f"/*   {line4_name}:+:      :+:    :+:   */\n"
        "/*                                                    +:+ +:+         +:+     */\n"
        f"/*   By: {line6_by}+#+  +:+       +#+        */\n"
        "/*                                                +#+#+#+#+#+   +#+           */\n"
        f"/*   Created: {line8_created}#+#    #+#             */\n"
        f"/*   Updated: {line9_updated}###   ########.fr       */\n"
        "/*                                                                            */\n"
        "/* ************************************************************************** */\n"
    )

def w(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path}")

# === src/graphics/run.c — game_run ===
w(f'{ROOT}/src/graphics/run.c', header('run.c') + """
#include "graphics.h"
#include <stdlib.h>

/* Registers all event hooks and enters the mlx main loop. */
int\tgame_run(t_game *game)
{
\tmlx_hook(game->win, 2, 1L << 0, hook_key_press, game);
\tmlx_hook(game->win, 3, 1L << 1, hook_key_release, game);
\tmlx_hook(game->win, 17, 0, hook_exit, game);
\tmlx_loop_hook(game->mlx, hook_loop, game);
\tmlx_loop(game->mlx);
\treturn (0);
}
""")

# === src/main.c — clean entry point with atexit cleanup ===
w(f'{ROOT}/src/main.c', header('main.c') + """
#include "cub3d.h"
#include "graphics/graphics.h"
#include "player/player.h"
#include <stdlib.h>
#include <libft.h>

/* Global game pointer for atexit cleanup. ESC/cross call exit(0)
 * which skips normal flow, so we register an atexit handler. */
static t_game\t*g_game = NULL;

/* Validates command-line arguments. */
static int\tvalidate_args(int argc, char **argv)
{
\t(void)argv;
\tif (argc != 2)
\t\treturn (cub_error_int("Usage: ./cub3D <map.cub>"));
\treturn (0);
}

/* atexit handler: frees all resources. */
static void\tcleanup(void)
{
\tif (g_game)
\t{
\t\tgame_cleanup(g_game);
\t\tif (g_game->config)
\t\t\tfree_config(g_game->config);
\t\tg_game = NULL;
\t}
}

/* Entry point: validate, parse, init, run. */
int\tmain(int argc, char **argv)
{
\tt_config\t*config;
\tt_game\t\tgame;

\tif (validate_args(argc, argv) < 0)
\t\treturn (1);
\tconfig = parse_cub_file(argv[1]);
\tif (!config)
\t\treturn (1);
\tplayer_init_direction(&config->player);
\tft_memset(&game, 0, sizeof(t_game));
\tgame.config = config;
\tg_game = &game;
\tatexit(cleanup);
\tif (game_init(&game, config) < 0)
\t\treturn (1);
\tgame_run(&game);
\treturn (0);
}
""")

print("main.c and run.c generated.")
