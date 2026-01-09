#include "cub3d.h"

float distance(float x, float y)
{
    return (sqrt(x * x + y * y));
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return (fix_dist);
}

bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;
    
    // Proteção básica para não ler fora do array do mapa
    if (y < 0 || y >= 10 || x < 0 || x >= 15) // Ajuste para tamanho real do mapa
        return (true);

    if (game->map[y][x] == '1')
        return (true);
    return (false);
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->x;
    float ray_y = player->y;

    while (!touch(ray_x, ray_y, game))
    {
        if (DEBUG)
            put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    if (!DEBUG)
    {
        float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
        // Evita divisão por zero
        if (dist == 0) 
            dist = 1; 

        float height = (BLOCK / dist) * (WIDTH / 2);
        int start_y = (HEIGHT - height) / 2;
        int end = start_y + height;
        
        while (start_y < end)
        {
            put_pixel(i, start_y, 255, game); // 255 é azul no formato int se bpp/endian permitir, ou muito escuro.
            start_y++;
        }
    }
}