#include "cub3d.h"

void move_player(t_player *player)
{
    int speed = 3;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up)
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->x -= cos_angle * speed;
        player->y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        player->x += sin_angle * speed;
        player->y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        player->x -= sin_angle * speed;
        player->y += cos_angle * speed;
    }
}