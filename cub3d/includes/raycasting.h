#ifndef RAYCASTING_H
# define RAYCASTING_H

int		ft_raycasting(t_game *game);
void	ft_raycasting_init_ray(t_game *game, float angle);
void	ft_raycasting_calc_step(t_game *game);
void	ft_raycasting_perform_dda(t_game *game);
void	ft_raycasting_calc_wall_height(t_game *game, float angle);
void	ft_raycasting_draw_column(t_game *game, int col);
int		ft_raycasting_is_wall(t_game *game, int x, int y);

#endif