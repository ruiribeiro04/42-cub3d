#include "../includes/cub3d.h"
#include "test_framework.h"
#include <limits.h>
#include <float.h>

/* Forward declarations for helper functions */
static int	create_test_map(const char *filename, const char *content);
static void	remove_test_map(const char *filename);

/* ========================================================================= */
/* TEXTURE PARSING TESTS - Every possible texture scenario                   */
/* ========================================================================= */

static int	test_texture_north_valid(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_north.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_north.cub", &game),
		"North texture should parse");
	assert_not_null(game.path_north, "North path set");
	assert_str_eq("./textures/north.xpm", game.path_north, "North path correct");

	ft_free_game(&game);
	remove_test_map("test_north.cub");
	return (0);
}

static int	test_texture_south_valid(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_south.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_south.cub", &game),
		"South texture should parse");
	assert_not_null(game.path_south, "South path set");
	assert_str_eq("./textures/south.xpm", game.path_south, "South path correct");

	ft_free_game(&game);
	remove_test_map("test_south.cub");
	return (0);
}

static int	test_texture_west_valid(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_west.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_west.cub", &game),
		"West texture should parse");
	assert_not_null(game.path_west, "West path set");
	assert_str_eq("./textures/west.xpm", game.path_west, "West path correct");

	ft_free_game(&game);
	remove_test_map("test_west.cub");
	return (0);
}

static int	test_texture_east_valid(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_east.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_east.cub", &game),
		"East texture should parse");
	assert_not_null(game.path_east, "East path set");
	assert_str_eq("./textures/east.xpm", game.path_east, "East path correct");

	ft_free_game(&game);
	remove_test_map("test_east.cub");
	return (0);
}

static int	test_texture_duplicate_north(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nNO ./textures/north2.xpm\n"
						"SO ./textures/south.xpm\nWE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\nF 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_dup_north.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_dup_north.cub", &game),
		"Duplicate north should fail");

	ft_free_game(&game);
	remove_test_map("test_dup_north.cub");
	return (0);
}

static int	test_texture_duplicate_south(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"SO ./textures/south2.xpm\nWE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\nF 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_dup_south.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_dup_south.cub", &game),
		"Duplicate south should fail");

	ft_free_game(&game);
	remove_test_map("test_dup_south.cub");
	return (0);
}

static int	test_texture_missing_north(void)
{
	t_game		game;
	const char	*map = "SO ./textures/south.xpm\nWE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\nF 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_no_north.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_north.cub", &game),
		"Missing north should fail");

	ft_free_game(&game);
	remove_test_map("test_no_north.cub");
	return (0);
}

static int	test_texture_missing_south(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nWE ./textures/west.xpm\n"
						"EA ./textures/east.xpm\nF 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_no_south.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_south.cub", &game),
		"Missing south should fail");

	ft_free_game(&game);
	remove_test_map("test_no_south.cub");
	return (0);
}

static int	test_texture_missing_west(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"EA ./textures/east.xpm\nF 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_no_west.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_west.cub", &game),
		"Missing west should fail");

	ft_free_game(&game);
	remove_test_map("test_no_west.cub");
	return (0);
}

static int	test_texture_missing_east(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nF 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_no_east.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_east.cub", &game),
		"Missing east should fail");

	ft_free_game(&game);
	remove_test_map("test_no_east.cub");
	return (0);
}

static int	test_texture_nonexistent_file(void)
{
	t_game		game;
	const char	*map = "NO ./textures/nonexistent.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_bad_tex.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_bad_tex.cub", &game),
		"Nonexistent texture should fail");

	ft_free_game(&game);
	remove_test_map("test_bad_tex.cub");
	return (0);
}

static int	test_texture_empty_path(void)
{
	t_game		game;
	const char	*map = "NO \nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_empty_path.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_empty_path.cub", &game),
		"Empty texture path should fail");

	ft_free_game(&game);
	remove_test_map("test_empty_path.cub");
	return (0);
}

static int	test_texture_path_with_spaces(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm   \nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_trailing_space.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_trailing_space.cub", &game),
		"Trailing spaces should be trimmed");
	assert_str_eq("./textures/north.xpm", game.path_north, "Path trimmed correctly");

	ft_free_game(&game);
	remove_test_map("test_trailing_space.cub");
	return (0);
}

/* ========================================================================= */
/* COLOR PARSING TESTS - Every possible color scenario                           */
/* ========================================================================= */

static int	test_color_floor_valid(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_floor.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_floor.cub", &game),
		"Floor color should parse");
	assert_int_eq(0xE46400, game.floor_color, "Floor color correct");

	ft_free_game(&game);
	remove_test_map("test_floor.cub");
	return (0);
}

static int	test_color_ceiling_valid(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_ceiling.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_ceiling.cub", &game),
		"Ceiling color should parse");
	assert_int_eq(0xE11E00, game.ceiling_color, "Ceiling color correct");

	ft_free_game(&game);
	remove_test_map("test_ceiling.cub");
	return (0);
}

static int	test_color_black(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 0,0,0\nC 0,0,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_black.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_black.cub", &game),
		"Black color should be accepted");
	assert_int_eq(0, game.floor_color, "Floor is black");
	assert_int_eq(0, game.ceiling_color, "Ceiling is black");

	ft_free_game(&game);
	remove_test_map("test_black.cub");
	return (0);
}

static int	test_color_white(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 255,255,255\nC 255,255,255\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_white.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_white.cub", &game),
		"White color should be accepted");
	assert_int_eq(0xFFFFFF, game.floor_color, "Floor is white");
	assert_int_eq(0xFFFFFF, game.ceiling_color, "Ceiling is white");

	ft_free_game(&game);
	remove_test_map("test_white.cub");
	return (0);
}

static int	test_color_comma_separated(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 191,119,47\nC 255,255,255\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_comma.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_comma.cub", &game),
		"Comma-separated RGB should parse");
	assert_int_eq(0xBF772F, game.floor_color, "Comma RGB correct");

	ft_free_game(&game);
	remove_test_map("test_comma.cub");
	return (0);
}

static int	test_color_space_separated(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 191 119 47\nC 255 255 255\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_space.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_space.cub", &game),
		"Space-separated RGB should parse");
	assert_int_eq(0xBF772F, game.floor_color, "Space RGB correct");

	ft_free_game(&game);
	remove_test_map("test_space.cub");
	return (0);
}

static int	test_color_duplicate_floor(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nF 100,100,100\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_dup_floor.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_dup_floor.cub", &game),
		"Duplicate floor should fail");

	ft_free_game(&game);
	remove_test_map("test_dup_floor.cub");
	return (0);
}

static int	test_color_duplicate_ceiling(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\nC 100,100,100\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_dup_ceil.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_dup_ceil.cub", &game),
		"Duplicate ceiling should fail");

	ft_free_game(&game);
	remove_test_map("test_dup_ceil.cub");
	return (0);
}

static int	test_color_missing_floor(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"C 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_no_floor.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_floor.cub", &game),
		"Missing floor should fail");

	ft_free_game(&game);
	remove_test_map("test_no_floor.cub");
	return (0);
}

static int	test_color_missing_ceiling(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_no_ceil.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_ceil.cub", &game),
		"Missing ceiling should fail");

	ft_free_game(&game);
	remove_test_map("test_no_ceil.cub");
	return (0);
}

static int	test_color_red_too_high(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 256,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_red_high.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_red_high.cub", &game),
		"Red > 255 should fail");

	ft_free_game(&game);
	remove_test_map("test_red_high.cub");
	return (0);
}

static int	test_color_green_too_high(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,256,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_green_high.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_green_high.cub", &game),
		"Green > 255 should fail");

	ft_free_game(&game);
	remove_test_map("test_green_high.cub");
	return (0);
}

static int	test_color_blue_too_high(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,256\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_blue_high.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_blue_high.cub", &game),
		"Blue > 255 should fail");

	ft_free_game(&game);
	remove_test_map("test_blue_high.cub");
	return (0);
}

static int	test_color_negative_red(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F -1,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_red_neg.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_red_neg.cub", &game),
		"Negative red should fail");

	ft_free_game(&game);
	remove_test_map("test_red_neg.cub");
	return (0);
}

static int	test_color_missing_values(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_missing_rgb.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_missing_rgb.cub", &game),
		"Missing RGB value should fail");

	ft_free_game(&game);
	remove_test_map("test_missing_rgb.cub");
	return (0);
}

static int	test_color_extra_values(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0,50\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_extra_rgb.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_extra_rgb.cub", &game),
		"Extra RGB value should fail");

	ft_free_game(&game);
	remove_test_map("test_extra_rgb.cub");
	return (0);
}

static int	test_color_non_numeric(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F abc,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_non_num.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_non_num.cub", &game),
		"Non-numeric RGB should fail");

	ft_free_game(&game);
	remove_test_map("test_non_num.cub");
	return (0);
}

/* ========================================================================= */
/* PLAYER PARSING TESTS - Every possible player scenario                         */
/* ========================================================================= */

static int	test_player_north(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_player_n.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_player_n.cub", &game),
		"North player should parse");

	ft_free_game(&game);
	remove_test_map("test_player_n.cub");
	return (0);
}

static int	test_player_south(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100S1\n111111\n";

	create_test_map("test_player_s.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_player_s.cub", &game),
		"South player should parse");

	ft_free_game(&game);
	remove_test_map("test_player_s.cub");
	return (0);
}

static int	test_player_east(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100E1\n111111\n";

	create_test_map("test_player_e.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_player_e.cub", &game),
		"East player should parse");

	ft_free_game(&game);
	remove_test_map("test_player_e.cub");
	return (0);
}

static int	test_player_west(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100W1\n111111\n";

	create_test_map("test_player_w.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_player_w.cub", &game),
		"West player should parse");

	ft_free_game(&game);
	remove_test_map("test_player_w.cub");
	return (0);
}

static int	test_player_no_player(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n110001\n111111\n";

	create_test_map("test_no_player.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_player.cub", &game),
		"No player should fail");

	ft_free_game(&game);
	remove_test_map("test_no_player.cub");
	return (0);
}

static int	test_player_multiple(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n10N001\n1100S1\n111111\n";

	create_test_map("test_multi_player.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_multi_player.cub", &game),
		"Multiple players should fail");

	ft_free_game(&game);
	remove_test_map("test_multi_player.cub");
	return (0);
}

/* ========================================================================= */
/* MAP VALIDATION TESTS - Every possible map scenario                           */
/* ========================================================================= */

static int	test_map_not_closed_top(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"011111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_open_top.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_open_top.cub", &game),
		"Open top should fail");

	ft_free_game(&game);
	remove_test_map("test_open_top.cub");
	return (0);
}

static int	test_map_not_closed_bottom(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111110\n";

	create_test_map("test_open_bottom.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_open_bottom.cub", &game),
		"Open bottom should fail");

	ft_free_game(&game);
	remove_test_map("test_open_bottom.cub");
	return (0);
}

static int	test_map_not_closed_left(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n110101\n101001\n1100N1\n111111\n";

	create_test_map("test_open_left.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_open_left.cub", &game),
		"Open left should fail");

	ft_free_game(&game);
	remove_test_map("test_open_left.cub");
	return (0);
}

static int	test_map_not_closed_right(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111011\n";

	create_test_map("test_open_right.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_open_right.cub", &game),
		"Open right should fail");

	ft_free_game(&game);
	remove_test_map("test_open_right.cub");
	return (0);
}

static int	test_map_invalid_char(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101X01\n1100N1\n111111\n";

	create_test_map("test_invalid_char.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_invalid_char.cub", &game),
		"Invalid character should fail");

	ft_free_game(&game);
	remove_test_map("test_invalid_char.cub");
	return (0);
}

static int	test_map_empty_line_in_map(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n\n101001\n1100N1\n111111\n";

	create_test_map("test_empty_line.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	/* Empty lines in map should be treated as spaces */
	assert_int_eq(0, ft_parse_cub_file("test_empty_line.cub", &game),
		"Empty line in map should be handled");

	ft_free_game(&game);
	remove_test_map("test_empty_line.cub");
	return (0);
}

static int	test_map_with_spaces(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n10 001\n1100N1\n111111\n";

	create_test_map("test_with_spaces.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_with_spaces.cub", &game),
		"Map with spaces should parse");

	ft_free_game(&game);
	remove_test_map("test_with_spaces.cub");
	return (0);
}

static int	test_map_space_adjacent_to_zero(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n10 001\n1100N1\n111111\n";

	create_test_map("test_space_adjacent.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_space_adjacent.cub", &game),
		"Space adjacent to 0 should fail");

	ft_free_game(&game);
	remove_test_map("test_space_adjacent.cub");
	return (0);
}

static int	test_map_irregular_shape(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100001\n101001\n1100N1\n111111\n";

	create_test_map("test_irregular.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_irregular.cub", &game),
		"Irregular map shape should parse");

	ft_free_game(&game);
	remove_test_map("test_irregular.cub");
	return (0);
}

/* ========================================================================= */
/* FILE FORMAT TESTS - Every possible file format scenario                       */
/* ========================================================================= */

static int	test_file_wrong_extension(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test.map", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test.map", &game),
		"Wrong extension should fail");

	ft_free_game(&game);
	remove_test_map("test.map");
	return (0);
}

static int	test_file_no_extension(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("testfile", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("testfile", &game),
		"No extension should fail");

	ft_free_game(&game);
	remove_test_map("testfile");
	return (0);
}

static int	test_file_empty(void)
{
	t_game		game;

	create_test_map("test_empty.cub", "");
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_empty.cub", &game),
		"Empty file should fail");

	ft_free_game(&game);
	remove_test_map("test_empty.cub");
	return (0);
}

static int	test_file_only_newlines(void)
{
	t_game		game;
	const char	*map = "\n\n\n\n";

	create_test_map("test_newlines.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_newlines.cub", &game),
		"Only newlines should fail");

	ft_free_game(&game);
	remove_test_map("test_newlines.cub");
	return (0);
}

static int	test_file_elements_different_order(void)
{
	t_game		game;
	const char	*map = "C 225,30,0\nF 220,100,0\nEA ./textures/east.xpm\n"
						"WE ./textures/west.xpm\nSO ./textures/south.xpm\n"
						"NO ./textures/north.xpm\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_order.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_order.cub", &game),
		"Different element order should parse");

	ft_free_game(&game);
	remove_test_map("test_order.cub");
	return (0);
}

static int	test_file_empty_lines_between_elements(void)
{
	t_game		game;
	const char	*map = "NO ./textures/north.xpm\n\n\nSO ./textures/south.xpm\n"
						"\nWE ./textures/west.xpm\n\nEA ./textures/east.xpm\n"
						"\n\nF 220,100,0\n\nC 225,30,0\n\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_empty_lines.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(0, ft_parse_cub_file("test_empty_lines.cub", &game),
		"Empty lines between elements should parse");

	ft_free_game(&game);
	remove_test_map("test_empty_lines.cub");
	return (0);
}

/* ========================================================================= */
/* ELEMENT IDENTIFIER TESTS - Every possible identifier scenario                  */
/* ========================================================================= */

static int	test_identifier_lowercase(void)
{
	t_game		game;
	const char	*map = "no ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_lower.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_lower.cub", &game),
		"Lowercase identifier should fail");

	ft_free_game(&game);
	remove_test_map("test_lower.cub");
	return (0);
}

static int	test_identifier_mixed_case(void)
{
	t_game		game;
	const char	*map = "No ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_mixed.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_mixed.cub", &game),
		"Mixed case identifier should fail");

	ft_free_game(&game);
	remove_test_map("test_mixed.cub");
	return (0);
}

static int	test_identifier_invalid(void)
{
	t_game		game;
	const char	*map = "XX ./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_invalid_id.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_invalid_id.cub", &game),
		"Invalid identifier should fail");

	ft_free_game(&game);
	remove_test_map("test_invalid_id.cub");
	return (0);
}

static int	test_identifier_missing_space(void)
{
	t_game		game;
	const char	*map = "NO./textures/north.xpm\nSO ./textures/south.xpm\n"
						"WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
						"F 220,100,0\nC 225,30,0\n"
						"111111\n100101\n101001\n1100N1\n111111\n";

	create_test_map("test_no_space.cub", map);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;

	assert_int_eq(1, ft_parse_cub_file("test_no_space.cub", &game),
		"Missing space after identifier should fail");

	ft_free_game(&game);
	remove_test_map("test_no_space.cub");
	return (0);
}

/* ========================================================================= */
/* Helper functions                                                            */
/* ========================================================================= */

static int	create_test_map(const char *filename, const char *content)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	if (content && *content)
		write(fd, content, strlen(content));
	close(fd);
	return (0);
}

static void	remove_test_map(const char *filename)
{
	unlink(filename);
}

/* ========================================================================= */
/* Main test runner                                                            */
/* ========================================================================= */

int	main(void)
{
	t_test_case	tests[] = {
		/* Texture tests */
		{"Texture - North Valid", test_texture_north_valid},
		{"Texture - South Valid", test_texture_south_valid},
		{"Texture - West Valid", test_texture_west_valid},
		{"Texture - East Valid", test_texture_east_valid},
		{"Texture - Duplicate North", test_texture_duplicate_north},
		{"Texture - Duplicate South", test_texture_duplicate_south},
		{"Texture - Missing North", test_texture_missing_north},
		{"Texture - Missing South", test_texture_missing_south},
		{"Texture - Missing West", test_texture_missing_west},
		{"Texture - Missing East", test_texture_missing_east},
		{"Texture - Nonexistent File", test_texture_nonexistent_file},
		{"Texture - Empty Path", test_texture_empty_path},
		{"Texture - Trailing Spaces", test_texture_path_with_spaces},

		/* Color tests */
		{"Color - Floor Valid", test_color_floor_valid},
		{"Color - Ceiling Valid", test_color_ceiling_valid},
		{"Color - Black", test_color_black},
		{"Color - White", test_color_white},
		{"Color - Comma Separated", test_color_comma_separated},
		{"Color - Space Separated", test_color_space_separated},
		{"Color - Duplicate Floor", test_color_duplicate_floor},
		{"Color - Duplicate Ceiling", test_color_duplicate_ceiling},
		{"Color - Missing Floor", test_color_missing_floor},
		{"Color - Missing Ceiling", test_color_missing_ceiling},
		{"Color - Red Too High", test_color_red_too_high},
		{"Color - Green Too High", test_color_green_too_high},
		{"Color - Blue Too High", test_color_blue_too_high},
		{"Color - Negative Red", test_color_negative_red},
		{"Color - Missing Values", test_color_missing_values},
		{"Color - Extra Values", test_color_extra_values},
		{"Color - Non-Numeric", test_color_non_numeric},

		/* Player tests */
		{"Player - North", test_player_north},
		{"Player - South", test_player_south},
		{"Player - East", test_player_east},
		{"Player - West", test_player_west},
		{"Player - No Player", test_player_no_player},
		{"Player - Multiple Players", test_player_multiple},

		/* Map validation tests */
		{"Map - Not Closed Top", test_map_not_closed_top},
		{"Map - Not Closed Bottom", test_map_not_closed_bottom},
		{"Map - Not Closed Left", test_map_not_closed_left},
		{"Map - Not Closed Right", test_map_not_closed_right},
		{"Map - Invalid Character", test_map_invalid_char},
		{"Map - Empty Line in Map", test_map_empty_line_in_map},
		{"Map - With Spaces", test_map_with_spaces},
		{"Map - Space Adjacent to Zero", test_map_space_adjacent_to_zero},
		{"Map - Irregular Shape", test_map_irregular_shape},

		/* File format tests */
		{"File - Wrong Extension", test_file_wrong_extension},
		{"File - No Extension", test_file_no_extension},
		{"File - Empty", test_file_empty},
		{"File - Only Newlines", test_file_only_newlines},
		{"File - Elements Different Order", test_file_elements_different_order},
		{"File - Empty Lines Between Elements", test_file_empty_lines_between_elements},

		/* Identifier tests */
		{"Identifier - Lowercase", test_identifier_lowercase},
		{"Identifier - Mixed Case", test_identifier_mixed_case},
		{"Identifier - Invalid", test_identifier_invalid},
		{"Identifier - Missing Space", test_identifier_missing_space},
	};
	t_test_result	result = {0};

	result.total = sizeof(tests) / sizeof(tests[0]);
	run_test_suite("EXHAUSTIVE Parser Tests", tests, result.total);

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
