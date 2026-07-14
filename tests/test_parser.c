/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 10:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Lightweight unit-test runner for the parser module.                          */
/* Run with: ./test_parser                                                     */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int      g_tests_run = 0;
static int      g_tests_passed = 0;
static int      g_tests_failed = 0;

/* Records the result of a single test case.                                   */
static void     record(int passed, const char *name)
{
        g_tests_run++;
        if (passed)
        {
                g_tests_passed++;
                printf("  [PASS] %s\n", name);
        }
        else
        {
                g_tests_failed++;
                printf("  [FAIL] %s\n", name);
        }
}

/* Asserts that a valid .cub file parses successfully and the basic fields are   */
/* populated correctly.                                                         */
static void     test_valid_minimal(void)
{
        t_config        *cfg;

        printf("Test: valid minimal map\n");
        cfg = parse_cub_file("maps/valid_minimal.cub");
        if (!cfg)
        {
                record(0, "valid_minimal: parse");
                return ;
        }
        record(cfg->has_north == 1, "valid_minimal: has_north");
        record(cfg->has_south == 1, "valid_minimal: has_south");
        record(cfg->has_west == 1, "valid_minimal: has_west");
        record(cfg->has_east == 1, "valid_minimal: has_east");
        record(cfg->has_floor == 1, "valid_minimal: has_floor");
        record(cfg->has_ceiling == 1, "valid_minimal: has_ceiling");
        record(cfg->has_player == 1, "valid_minimal: has_player");
        record(cfg->map.height == 5, "valid_minimal: map height");
        record(cfg->map.width == 5, "valid_minimal: map width");
        record(cfg->player.direction == 'N', "valid_minimal: player direction");
        record(cfg->player.x == 3.0, "valid_minimal: player x");
        record(cfg->player.y == 3.0, "valid_minimal: player y");
        free_config(cfg);
}

/* Asserts that the example map from the subject parses cleanly.                */
static void     test_valid_subject_example(void)
{
        t_config        *cfg;

        printf("Test: valid subject example map\n");
        cfg = parse_cub_file("maps/valid_subject.cub");
        record(cfg != NULL, "valid_subject: parse");
        if (cfg)
        {
                record(cfg->has_player == 1, "valid_subject: has_player");
                record(cfg->map.height > 0, "valid_subject: map height");
                record(cfg->map.width > 0, "valid_subject: map width");
                free_config(cfg);
        }
}

/* Each invalid case must return NULL.                                         */
static void     test_invalid_case(const char *path, const char *label)
{
        t_config        *cfg;

        printf("Test: %s\n", label);
        cfg = parse_cub_file(path);
        record(cfg == NULL, label);
        if (cfg)
                free_config(cfg);
}

/* Verifies all the malformed .cub cases under maps/invalid_*.cub.              */
static void     test_invalid_cases(void)
{
        test_invalid_case("maps/invalid_no_extension",
                "invalid: missing .cub extension");
        test_invalid_case("maps/invalid_wrong_ext.txt",
                "invalid: wrong extension");
        test_invalid_case("maps/invalid_missing_texture.cub",
                "invalid: missing NO texture");
        test_invalid_case("maps/invalid_dup_texture.cub",
                "invalid: duplicate NO texture");
        test_invalid_case("maps/invalid_bad_color_value.cub",
                "invalid: color value > 255");
        test_invalid_case("maps/invalid_bad_color_format.cub",
                "invalid: color format bad");
        test_invalid_case("maps/invalid_unclosed_map.cub",
                "invalid: map not closed");
        test_invalid_case("maps/invalid_no_spawn.cub",
                "invalid: no player spawn");
        test_invalid_case("maps/invalid_two_spawns.cub",
                "invalid: two player spawns");
        test_invalid_case("maps/invalid_unknown_id.cub",
                "invalid: unknown element id");
        test_invalid_case("maps/invalid_bad_texture_path.cub",
                "invalid: texture path does not exist");
        test_invalid_case("maps/invalid_junk_after_texture.cub",
                "invalid: junk after texture path");
        test_invalid_case("maps/invalid_no_map.cub",
                "invalid: no map at all");
        test_invalid_case("maps/invalid_invalid_char_in_map.cub",
                "invalid: invalid char in map");
        test_invalid_case("maps/invalid_missing_floor.cub",
                "invalid: missing F color");
        test_invalid_case("maps/invalid_missing_ceiling.cub",
                "invalid: missing C color");
        test_invalid_case("maps/this_file_does_not_exist.cub",
                "invalid: file does not exist");
}

/* Verifies colors are correctly parsed.                                       */
static void     test_color_values(void)
{
        t_config        *cfg;

        printf("Test: color values\n");
        cfg = parse_cub_file("maps/valid_colors.cub");
        if (!cfg)
        {
                record(0, "valid_colors: parse");
                return ;
        }
        record(cfg->floor.r == 220 && cfg->floor.g == 100 && cfg->floor.b == 0,
                "valid_colors: floor RGB");
        record(cfg->ceiling.r == 225 && cfg->ceiling.g == 30 && cfg->ceiling.b == 0,
                "valid_colors: ceiling RGB");
        free_config(cfg);
}

/* Verifies the player's direction-to-angle mapping.                            */
static void     test_player_angles(void)
{
        t_config        *cfg;
        const char      *files[4];
        char            dirs[4];
        int                     i;

        printf("Test: player angles\n");
        files[0] = "maps/spawn_n.cub";
        files[1] = "maps/spawn_s.cub";
        files[2] = "maps/spawn_e.cub";
        files[3] = "maps/spawn_w.cub";
        dirs[0] = 'N';
        dirs[1] = 'S';
        dirs[2] = 'E';
        dirs[3] = 'W';
        i = 0;
        while (i < 4)
        {
                cfg = parse_cub_file(files[i]);
                if (cfg)
                {
                        record(cfg->player.direction == dirs[i],
                                "spawn direction matches");
                        free_config(cfg);
                }
                else
                {
                        record(0, "spawn direction file failed to parse");
                }
                i++;
        }
}

int     main(void)
{
        setvbuf(stdout, NULL, _IONBF, 0);
        fprintf(stderr, "DEBUG: starting main\n");
        printf("============================================================\n");
        printf("  cub3D parser — unit tests\n");
        printf("============================================================\n\n");
        fprintf(stderr, "DEBUG: calling test_valid_minimal\n");
        test_valid_minimal();
        fprintf(stderr, "DEBUG: calling test_valid_subject_example\n");
        test_valid_subject_example();
        fprintf(stderr, "DEBUG: calling test_color_values\n");
        test_color_values();
        fprintf(stderr, "DEBUG: calling test_player_angles\n");
        test_player_angles();
        fprintf(stderr, "DEBUG: calling test_invalid_cases\n");
        test_invalid_cases();
        printf("\n------------------------------------------------------------\n");
        printf("  Total: %d | Passed: %d | Failed: %d\n",
                g_tests_run, g_tests_passed, g_tests_failed);
        printf("------------------------------------------------------------\n");
        if (g_tests_failed > 0)
                return (1);
        return (0);
}
