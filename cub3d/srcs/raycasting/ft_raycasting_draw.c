#include "cub3d.h"

static void	ft_raycasting_draw_ceiling(t_game *game, int col)
{
	int	y;

	y = 0;
	while (y < game->ray.draw_start && y < HEIGHT)
	{
		ft_put_pixel_to_img(game, col, y, game->ceiling_color);
		y++;
	}
}

static void	ft_raycasting_calc_tex_x(t_game *game, t_texture *tex)
{
	float	tex_coord;
	float	p;

	tex_coord = game->ray.wall_x;
	if (game->ray.hit_door && game->ray.hit_door->progress > 0.0f)
	{
		p = game->ray.hit_door->progress;
		if (tex_coord < p)
		{
			game->ray.tex_x = -1;
			return ;
		}
		tex_coord = (tex_coord - p) / (1.0f - p);
	}
	game->ray.tex_x = (int)(tex_coord * tex->width);
	if (game->ray.tex_x < 0)
		game->ray.tex_x = 0;
	if (game->ray.tex_x >= tex->width)
		game->ray.tex_x = tex->width - 1;
	if (game->ray.side == 0 && game->ray.dir_x > 0)
		game->ray.tex_x = tex->width - game->ray.tex_x - 1;
	if (game->ray.side == 1 && game->ray.dir_y < 0)
		game->ray.tex_x = tex->width - game->ray.tex_x - 1;
}

static void	ft_raycasting_draw_wall(t_game *game, int col)
{
	t_texture	*tex;
	int			y;
	float		step;
	float		tex_pos;
	int			tex_y;
	int			color;

	if (game->ray.hit_door && game->ray.hit_door->tex.img)
		tex = &game->ray.hit_door->tex;
	else
		tex = ft_get_wall_texture(game);
	ft_raycasting_calc_tex_x(game, tex);
	if (game->ray.tex_x < 0)
		return ;
	step = (float)tex->height / game->ray.wall_height;
	tex_pos = (game->ray.draw_start - HEIGHT / 2
			+ game->ray.wall_height / 2) * step;
	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		tex_pos += step;
		color = ft_get_texture_pixel(tex, game->ray.tex_x, tex_y);
		if (game->ray.side == 1)
			color = (color >> 1) & 0x7F7F7F;
		if ((color & 0x00FFFFFF) != 0)
			ft_put_pixel_to_img(game, col, y, color);
		y++;
	}
}

static void	ft_raycasting_draw_floor(t_game *game, int col)
{
	int	y;

	y = game->ray.draw_end;
	if (y < 0)
		y = 0;
	while (y < HEIGHT)
	{
		ft_put_pixel_to_img(game, col, y, game->floor_color);
		y++;
	}
}

void	ft_raycasting_draw_column(t_game *game, int col)
{
	ft_raycasting_draw_ceiling(game, col);
	ft_raycasting_draw_wall(game, col);
	ft_raycasting_draw_floor(game, col);
}
