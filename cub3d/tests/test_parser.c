#include "../includes/cub3d.h"
#include "test_framework.h"

/* Test helper functions */
static void	cleanup_test_files(void);
static int	create_test_map(const char *filename, const char *content);
static void	remove_test_map(const char *filename);

/* Test valid map parsing */
static int	test_valid_map_parsing(void)
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

	create_test_map("test_valid.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_valid.cub", &game),
		"Valid map should parse successfully");
	assert_not_null(game.path_north, "North texture should be set");
	assert_not_null(game.path_south, "South texture should be set");
	assert_not_null(game.path_west, "West texture should be set");
	assert_not_null(game.path_east, "East texture should be set");
	assert_int_eq(0xE46400, game.floor_color, "Floor color should be 0xE46400");
	assert_int_eq(0xE11E00, game.ceiling_color, "Ceiling color should be 0xE11E00");
	assert_not_null(game.map, "Map should be loaded");
	assert_true(game.player.x > 0, "Player X should be set");
	assert_true(game.player.y > 0, "Player Y should be set");

	ft_free_game(&game);
	remove_test_map("test_valid.cub");
	return (0);
}

/* Test black color (0,0,0) is accepted */
static int	test_black_color_accepted(void)
{
	t_game		game;
	const char	*test_map = "NO ./textures/north.xpm\n"
						"SO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\n"
						"F 0,0,0\n"
						"C 0,0,0\n"
						"111111\n"
						"100101\n"
						"101001\n"
						"1100N1\n"
						"111111\n";

	create_test_map("test_black.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_black.cub", &game),
		"Black color map should parse successfully");
	assert_int_eq(0, game.floor_color, "Floor color should be 0 (black)");
	assert_int_eq(0, game.ceiling_color, "Ceiling color should be 0 (black)");

	ft_free_game(&game);
	remove_test_map("test_black.cub");
	return (0);
}

/* Test comma-separated RGB values */
static int	test_comma_separated_rgb(void)
{
	t_game		game;
	const char	*test_map = "NO ./textures/north.xpm\n"
						"SO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\n"
						"F 191,119,47\n"
						"C 255,255,255\n"
						"111111\n"
						"100101\n"
						"101001\n"
						"1100N1\n"
						"111111\n";

	create_test_map("test_commas.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_commas.cub", &game),
		"Comma-separated RGB should parse successfully");
	assert_int_eq(0xBF772F, game.floor_color, "Floor color should match comma-separated value");
	assert_int_eq(0xFFFFFF, game.ceiling_color, "Ceiling color should be white");

	ft_free_game(&game);
	remove_test_map("test_commas.cub");
	return (0);
}

/* Test missing texture */
static int	test_missing_texture(void)
{
	t_game		game;
	const char	*test_map = "NO ./textures/north.xpm\n"
						"SO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\n"
						"F 220,100,0\n"
						"C 225,30,0\n"
						"111111\n"
						"100101\n"
						"101001\n"
						"1100N1\n"
						"111111\n";

	create_test_map("test_missing_tex.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_missing_tex.cub", &game),
		"Missing texture should fail parsing");

	remove_test_map("test_missing_tex.cub");
	return (0);
}

/* Test duplicate texture */
static int	test_duplicate_texture(void)
{
	t_game		game;
	const char	*test_map = "NO ./textures/north.xpm\n"
						"NO ./textures/north2.xpm\n"
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

	create_test_map("test_dup_tex.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_dup_tex.cub", &game),
		"Duplicate texture should fail parsing");

	ft_free_game(&game);
	remove_test_map("test_dup_tex.cub");
	return (0);
}

/* Test duplicate color */
static int	test_duplicate_color(void)
{
	t_game		game;
	const char	*test_map = "NO ./textures/north.xpm\n"
						"SO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\n"
						"F 220,100,0\n"
						"F 100,100,100\n"
						"C 225,30,0\n"
						"111111\n"
						"100101\n"
						"101001\n"
						"1100N1\n"
						"111111\n";

	create_test_map("test_dup_color.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_dup_color.cub", &game),
		"Duplicate color should fail parsing");

	ft_free_game(&game);
	remove_test_map("test_dup_color.cub");
	return (0);
}

/* Test invalid RGB range */
static int	test_invalid_rgb_range(void)
{
	t_game		game;
	const char	*test_map = "NO ./textures/north.xpm\n"
						"SO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\n"
						"F 220,100,0\n"
						"C 300,30,0\n"
						"111111\n"
						"100101\n"
						"101001\n"
						"1100N1\n"
						"111111\n";

	create_test_map("test_invalid_rgb.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_invalid_rgb.cub", &game),
		"Invalid RGB range should fail parsing");

	ft_free_game(&game);
	remove_test_map("test_invalid_rgb.cub");
	return (0);
}

/* Test map not closed */
static int	test_map_not_closed(void)
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
						"111110\n";

	create_test_map("test_not_closed.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_not_closed.cub", &game),
		"Map not closed should fail parsing");

	ft_free_game(&game);
	remove_test_map("test_not_closed.cub");
	return (0);
}

/* Test no player */
static int	test_no_player(void)
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
						"110001\n"
						"111111\n";

	create_test_map("test_no_player.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_player.cub", &game),
		"No player should fail parsing");

	ft_free_game(&game);
	remove_test_map("test_no_player.cub");
	return (0);
}

/* Test multiple players */
static int	test_multiple_players(void)
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
						"10N001\n"
						"1100S1\n"
						"111111\n";

	create_test_map("test_multi_player.cub", test_map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_multi_player.cub", &game),
		"Multiple players should fail parsing");

	ft_free_game(&game);
	remove_test_map("test_multi_player.cub");
	return (0);
}

/* Helper function implementations */
static int	create_test_map(const char *filename, const char *content)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	write(fd, content, strlen(content));
	close(fd);
	return (0);
}

static void	remove_test_map(const char *filename)
{
	unlink(filename);
}

/* Main test runner */
int	main(void)
{
	t_test_case	tests[] = {
		{"Valid Map Parsing", test_valid_map_parsing},
		{"Black Color Accepted", test_black_color_accepted},
		{"Comma-Separated RGB", test_comma_separated_rgb},
		{"Missing Texture", test_missing_texture},
		{"Duplicate Texture", test_duplicate_texture},
		{"Duplicate Color", test_duplicate_color},
		{"Invalid RGB Range", test_invalid_rgb_range},
		{"Map Not Closed", test_map_not_closed},
		{"No Player", test_no_player},
		{"Multiple Players", test_multiple_players},
	};
	t_test_result	result = {0};

	result.total = sizeof(tests) / sizeof(tests[0]);
	run_test_suite("Parser Tests", tests, result.total);

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
