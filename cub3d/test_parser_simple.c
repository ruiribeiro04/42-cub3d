#include "includes/cub3d.h"
#include <stdio.h>

int main(void)
{
	t_game game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ft_parse_cub_file("test_map.cub", &game) == 0)
	{
		printf("✓ Parser succeeded!\n");
		printf("Textures:\n");
		printf("  NO: %s\n", game.path_north ? game.path_north : "(null)");
		printf("  SO: %s\n", game.path_south ? game.path_south : "(null)");
		printf("  WE: %s\n", game.path_west ? game.path_west : "(null)");
		printf("  EA: %s\n", game.path_east ? game.path_east : "(null)");
		printf("Colors:\n");
		printf("  Floor: 0x%X\n", game.floor_color);
		printf("  Ceiling: 0x%X\n", game.ceiling_color);
		printf("Player:\n");
		printf("  Position: (%.1f, %.1f)\n", game.player.x, game.player.y);
		printf("  Angle: %.2f\n", game.player.angle);
		printf("Map:\n");
		for (int i = 0; game.map[i]; i++)
			printf("  %s\n", game.map[i]);
		ft_free_game(&game);
		return (0);
	}
	printf("✗ Parser failed!\n");
	return (1);
}
