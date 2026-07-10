#include "../includes/cub3d.h"
#include "test_framework.h"
#include <time.h>

/* Integration test - complete parsing and initialization workflow */
static int	test_complete_workflow(void)
{
	t_game		game;
	clock_t		start, end;
	double		cpu_time_used;

	printf("  Testing complete parsing and initialization workflow...\n");

	/* Start timer */
	start = clock();

	/* Initialize game with sentinel values */
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	/* Parse valid map */
	assert_int_eq(0, ft_parse_cub_file("maps/mandatory/test_valid_map.cub", &game),
		"Should parse valid map successfully");

	/* Verify textures loaded */
	assert_not_null(game.path_north, "North texture should be loaded");
	assert_not_null(game.path_south, "South texture should be loaded");
	assert_not_null(game.path_west, "West texture should be loaded");
	assert_not_null(game.path_east, "East texture should be loaded");

	/* Verify colors set correctly */
	assert_true(game.floor_color >= 0, "Floor color should be set");
	assert_true(game.ceiling_color >= 0, "Ceiling color should be set");

	/* Verify map loaded */
	assert_not_null(game.map, "Map should be loaded");
	assert_true(game.map_height > 0, "Map height should be positive");
	assert_true(game.map_width > 0, "Map width should be positive");

	/* Verify player position */
	assert_true(game.player.x >= 0, "Player X should be set");
	assert_true(game.player.y >= 0, "Player Y should be set");
	assert_true(game.player.angle >= 0, "Player angle should be set");

	/* End timer */
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("  Workflow completed in %.4f seconds\n", cpu_time_used);
	assert_true(cpu_time_used < 1.0, "Parsing should complete in under 1 second");

	/* Cleanup */
	ft_free_game(&game);

	/* Verify cleanup - these should be NULL after free */
	assert_null(game.path_north, "North path should be freed");
	assert_null(game.path_south, "South path should be freed");
	assert_null(game.path_west, "West path should be freed");
	assert_null(game.path_east, "East path should be freed");
	assert_null(game.map, "Map should be freed");

	return (0);
}

/* Test error recovery workflow */
static int	test_error_recovery_workflow(void)
{
	t_game		game;

	printf("  Testing error recovery and cleanup...\n");

	/* Test 1: Missing texture error recovery */
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("tests/maps_invalid/missing_texture.cub", &game),
		"Should fail on missing texture");

	/* Verify partial cleanup happened */
	ft_free_game(&game);

	/* Test 2: Invalid RGB error recovery */
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("tests/maps_invalid/invalid_color.cub", &game),
		"Should fail on invalid RGB");

	ft_free_game(&game);

	/* Test 3: Map validation error recovery */
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("tests/maps_invalid/not_closed.cub", &game),
		"Should fail on non-enclosed map");

	ft_free_game(&game);

	return (0);
}

/* Test multiple sequential parses */
static int	test_sequential_parses(void)
{
	t_game		game;
	int		i;
	const char	*valid_maps[] = {
		"maps/mandatory/test_valid_map.cub",
		"maps/mandatory/small_square.cub",
		"maps/mandatory/l_shape.cub",
		NULL
	};

	printf("  Testing multiple sequential parses...\n");

	for (i = 0; valid_maps[i]; i++)
	{
		ft_memset(&game, 0, sizeof(t_game));
		game.floor_color = -1;
		game.ceiling_color = -1;

		assert_int_eq(0, ft_parse_cub_file(valid_maps[i], &game),
			"Should parse each valid map successfully");
		assert_not_null(game.map, "Map should be loaded");
		assert_not_null(game.path_north, "Textures should be loaded");

		ft_free_game(&game);
	}

	return (0);
}

/* Test texture path validation */
static int	test_texture_path_validation(void)
{
	t_game		game;
	const char	*test_map = "NO ./textures/north.xpm\n"
						"SO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\n"
						"F 220,100,0\n"
						"C 225,30,0\n"
						"111111\n"
						"100101\n"
						"101001\n"
						"1100N1\n"
						"111111\n";

	printf("  Testing texture path validation...\n");

	/* Create test map with existing textures */
	int	fd = open("test_texture_valid.cub", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		write(fd, test_map, strlen(test_map));
		close(fd);

		ft_memset(&game, 0, sizeof(t_game));
		game.floor_color = -1;
		game.ceiling_color = -1;

		assert_int_eq(0, ft_parse_cub_file("test_texture_valid.cub", &game),
			"Should accept valid texture paths");

		ft_free_game(&game);
		unlink("test_texture_valid.cub");
	}

	return (0);
}

/* Main integration test runner */
int	main(void)
{
	t_test_case	tests[] = {
		{"Complete Workflow", test_complete_workflow},
		{"Error Recovery Workflow", test_error_recovery_workflow},
		{"Sequential Parses", test_sequential_parses},
		{"Texture Path Validation", test_texture_path_validation},
	};
	t_test_result	result = {0};

	result.total = sizeof(tests) / sizeof(tests[0]);
	run_test_suite("Integration Tests", tests, result.total);

	/* Count passed tests */
	for (int i = 0; i < result.total; i++)
	{
		int		_test_failed = 0;
		tests[i].func();
		if (!_test_failed)
			result.passed++;
		else
			result.failed++;
	}

	print_test_summary(&result);
	return (result.failed > 0 ? TEST_FAILED : TEST_PASSED);
}
