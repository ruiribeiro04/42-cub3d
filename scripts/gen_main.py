#!/usr/bin/env python3
"""Generate src/main.c and src/utils/debug.c for Task 2 (scaffold)."""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 11:00:00'
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

# === src/main.c (3 functions) ===
w(f'{ROOT}/src/main.c', header('main.c') + """
#include "cub3d.h"
#include <libft.h>
#include <ft_printf.h>

/* Validates command-line arguments. Returns 0 on success, -1 on
 * error (message already printed). */
static int\tvalidate_args(int argc, char **argv)
{
\t(void)argv;
\tif (argc != 2)
\t\treturn (cub_error_int("Usage: ./cub3D <map.cub>"));
\treturn (0);
}

/* Prints the parsed configuration to stdout. This is a temporary
 * verification aid that will be replaced by the graphics engine
 * in a later task. */
static void\tprint_config(t_config *cfg)
{
\tft_printf("=== cub3D Configuration ===\\n");
\tft_printf("NO texture: %s\\n", cfg->textures.north);
\tft_printf("SO texture: %s\\n", cfg->textures.south);
\tft_printf("WE texture: %s\\n", cfg->textures.west);
\tft_printf("EA texture: %s\\n", cfg->textures.east);
\tft_printf("Floor:      %d,%d,%d\\n",
\t\tcfg->floor.r, cfg->floor.g, cfg->floor.b);
\tft_printf("Ceiling:    %d,%d,%d\\n",
\t\tcfg->ceiling.r, cfg->ceiling.g, cfg->ceiling.b);
\tft_printf("Map:        %dx%d\\n", cfg->map.width, cfg->map.height);
\tft_printf("Player:     (%d, %d) facing %c\\n",
\t\t(int)cfg->player.x, (int)cfg->player.y, cfg->player.direction);
}

/* Entry point. Validates args, parses the .cub file, and (for
 * now) prints the configuration. Graphics will be added later. */
int\tmain(int argc, char **argv)
{
\tt_config\t*cfg;

\tif (validate_args(argc, argv) < 0)
\t\treturn (1);
\tcfg = parse_cub_file(argv[1]);
\tif (!cfg)
\t\treturn (1);
\tprint_config(cfg);
\tfree_config(cfg);
\treturn (0);
}
""")

print("main.c generated.")
