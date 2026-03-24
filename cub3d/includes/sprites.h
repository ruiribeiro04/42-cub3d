#ifndef SPRITES_H
# define SPRITES_H

typedef struct s_spr_draw
{
	int	start_y;
	int	end_y;
	int	start_x;
	int	end_x;
	int	height;
}		t_spr_draw;

void	ft_draw_sprites(t_game *game);
int		ft_load_animation(t_game *game, t_sprite *sprite, char *base_path,
			int count);
void	ft_free_sprites(t_game *game);
void	update_sprite_state(t_game *game, double delta_time);
char	*ft_itoa(int num);
char	*ft_strjoin(char const *s1, char const *s2);

#endif