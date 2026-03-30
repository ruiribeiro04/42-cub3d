#include "cub3d.h"

void	ft_handle_door_interaction(t_game *game)
{
    int		map_x;
    int		map_y;
    t_door	*door;
    float	dir_x;
    float	dir_y;
    float	dist;
    float	dot;
    float	dx;
    float	dy;

    if (!game->door_map) // <--- ADICIONAR ESTA SEGURANÇA
        return ;
    dir_x = cos(game->player.angle);
    dir_y = sin(game->player.angle);
    map_x = (int)((game->player.x + dir_x * BLOCK * DOOR_INTERACT_DIST) / BLOCK);
    map_y = (int)((game->player.y + dir_y * BLOCK * DOOR_INTERACT_DIST) / BLOCK);

    if (map_y >= 0 && map_y < game->map_height && map_x >= 0 && map_x < game->map_width)
    {
        door = game->door_map[map_y][map_x];
        if (door)
        {
            dx = (door->x * BLOCK + BLOCK / 2) - game->player.x;
            dy = (door->y * BLOCK + BLOCK / 2) - game->player.y;
            dist = sqrt(dx * dx + dy * dy);
            if (dist == 0)
                return ;
            dot = (dx * dir_x + dy * dir_y) / dist;
            
            // Se o jogador estiver "quase" de frente para a porta (ângulo < 60 graus)
            if (dot > 0.2f)
            {
                if (door->state == DOOR_CLOSED)
                    door->state = DOOR_OPENING;
                else if (door->state == DOOR_OPEN)
                    door->state = DOOR_CLOSING;
            }
        }
    }
}

void	ft_update_doors(t_game *game, double delta_time)
{
    int	i;

    i = 0;
    while (i < game->door_count)
    {
        if (game->doors[i].state == DOOR_OPENING)
        {
            game->doors[i].progress += DOOR_SPEED * delta_time;
            if (game->doors[i].progress >= 1.0f)
            {
                game->doors[i].progress = 1.0f;
                game->doors[i].state = DOOR_OPEN;
            }
        }
        else if (game->doors[i].state == DOOR_CLOSING)
        {
            game->doors[i].progress -= DOOR_SPEED * delta_time;
            if (game->doors[i].progress <= 0.0f)
            {
                game->doors[i].progress = 0.0f;
                game->doors[i].state = DOOR_CLOSED;
            }
        }
        i++;
    }
}