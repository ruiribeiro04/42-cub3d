#include "cub3d.h"

void	ft_draw_minimap(t_game *game)
{
	t_point	draw_pos;
	int		x;
	int		y;
	int		current_len;

	y = 0;
	while (y < game->map_height)
	{
		current_len = ft_strlen(game->map[y]);
		x = 0;
		while (x < game->map_width)
		{
			draw_pos.x = MAP_OFFSET_X + (x * MAP_TILE);
			draw_pos.y = MAP_OFFSET_Y + (y * MAP_TILE);
			if (x < current_len && game->map[y][x] == '1')
				ft_draw_rect(game, draw_pos, MAP_TILE, MAP_COLOR_WALL);
			else
				ft_draw_rect(game, draw_pos, MAP_TILE, MAP_COLOR_BG);
			x++;
		}
		y++;
	}
	/* Se apagarmos o (int), o mapa fica fluido,
	mas depois tem o bug de passar pelas paredes */
	draw_pos.x = MAP_OFFSET_X + ((int)(game->player.x / BLOCK) * MAP_TILE);
	draw_pos.y = MAP_OFFSET_Y + ((int)(game->player.y / BLOCK) * MAP_TILE);
	ft_draw_rect(game, draw_pos, MAP_TILE, MAP_COLOR_PLAYER);
}
