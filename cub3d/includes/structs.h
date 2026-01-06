#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;
}   t_player;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    void        *img;
    char        *data;
    int         bpp;
    int         size_line;
    int         endian;
    t_player    player;
    char        **map;
} t_game;


#endif