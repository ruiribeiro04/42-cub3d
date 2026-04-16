#ifndef DOORS_H
# define DOORS_H

void	ft_free_doors(t_game *game);
int		ft_parse_doors(t_game *game);
int		ft_parse_and_load_doors(t_game *game);
void	ft_handle_door_interaction(t_game *game);
void	ft_update_doors(t_game *game, double delta_time);

#endif