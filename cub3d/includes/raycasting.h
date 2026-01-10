#ifndef RAYCASTING_H
# define RAYCASTING_H

int	ft_raycasting_touch(float px, float py, t_game *game);
float	ft_raycasting_fixed_dist(float x2, float y2, t_game *game);
float	ft_raycasting_distance(float x, float y);
void	ft_raycasting_draw_line(t_game *game, float angle, int column);

#endif