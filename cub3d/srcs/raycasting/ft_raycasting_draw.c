#include "cub3d.h"

static void	ft_raycasting_draw_ceiling(t_game *game, int col)
{
	int	y;
	int	end;

	end = game->ray.draw_start;
	if (end > HEIGHT)
		end = HEIGHT;
	y = 0;
	while (y < end)
	{
		ft_put_pixel_to_img(game, col, y, CEILING_COLOR);
		y++;
	}
}

static void	ft_raycasting_draw_wall(t_game *game, int col)
{
	t_texture		*tex;
	int				y;
	int				tex_y;
	int				start;
	int				end;
	unsigned int	color;

	tex = ft_get_wall_texture(game);
	game->ray.tex_x = (int)(game->ray.wall_x * tex->width);
	if ((game->ray.side == 0 && game->ray.dir_x < 0)
    	|| (game->ray.side == 1 && game->ray.dir_y > 0))
    game->ray.tex_x = tex->width - game->ray.tex_x - 1;
	start = game->ray.draw_start;
	end = game->ray.draw_end;
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	y = start;
	while (y < end)
	{
		tex_y = ((y - game->ray.draw_start) * tex->height) / game->ray.wall_height;
		color = ft_get_texture_pixel(tex, game->ray.tex_x, tex_y);
		ft_put_pixel_to_img(game, col, y, color);
		y++;
	}
}

static void	ft_raycasting_draw_floor(t_game *game, int col)
{
	int	y;
	int	start;

	start = game->ray.draw_end;
	if (start < 0)
		start = 0;
	y = start;
	while (y < HEIGHT)
	{
		ft_put_pixel_to_img(game, col, y, FLOOR_COLOR);
		y++;
	}
}

void	ft_raycasting_draw_column(t_game *game, int col)
{
	ft_raycasting_draw_ceiling(game, col);
	ft_raycasting_draw_wall(game, col);
	ft_raycasting_draw_floor(game, col);
}