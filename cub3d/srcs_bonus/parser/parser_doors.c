#include "cub3d.h"

void	*ft_calloc(size_t nmemb, size_t size);

static int	ft_allocate_door_map(t_game *game)
{
    int	y;

    game->door_map = malloc(sizeof(t_door **) * game->map_height);
    if (!game->door_map)
        return (1);
    y = 0;
    while (y < game->map_height)
    {
        game->door_map[y] = ft_calloc(game->map_width, sizeof(t_door *));
        if (!game->door_map[y])
            return (1); // O ft_free_game tratará de limpar o que foi alocado
        y++;
    }
    return (0);
}

int	ft_parse_doors(t_game *game)
{
    int	y;
    int	x;
    int	i;

    game->door_count = 0;
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'D')
                game->door_count++;
            x++;
        }
        y++;
    }
    if (game->door_count == 0)
    {
        game->doors = NULL;
        game->door_map = NULL;
        return (0);
    }
    if (ft_allocate_door_map(game))
        return (1);
    game->doors = malloc(sizeof(t_door) * game->door_count);
    if (!game->doors)
        return (1);
    i = 0;
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'D')
            {
                game->doors[i].x = x;
                game->doors[i].y = y;
                game->doors[i].state = DOOR_CLOSED;
                game->doors[i].progress = 0.0f;
                game->doors[i].tex.img = NULL;
                game->door_map[y][x] = &game->doors[i];
                i++;
            }
            x++;
        }
        y++;
    }
    // Carregar a textura UMA VEZ usando a tua função existente
    if (ft_load_texture(game, &game->doors[0].tex, "textures/door.xpm"))
        return (1);
    // Partilhar o ponteiro da textura com todas as outras portas (poupa RAM e loads)
    i = 1;
    while (i < game->door_count)
    {
        game->doors[i].tex = game->doors[0].tex;
        i++;
    }
    return (0);
}