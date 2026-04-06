#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "includes/cub3d.h"

extern int ft_parse_cub_file(char *filename, t_game *game);
extern void ft_free_game(t_game *game);

int main() {
    t_game game;
    memset(&game, 0, sizeof(t_game));
    game.floor_color = -1;
    game.ceiling_color = -1;

    printf("Parsing test_debug.cub...\n");
    int result = ft_parse_cub_file("test_debug.cub", &game);
    printf("Result: %d\n", result);
    
    if (result == 0) {
        printf("Success!\n");
        printf("North: %s\n", game.path_north ? game.path_north : "NULL");
        printf("South: %s\n", game.path_south ? game.path_south : "NULL");
        printf("Floor color: %d\n", game.floor_color);
        printf("Ceiling color: %d\n", game.ceiling_color);
    }

    ft_free_game(&game);
    return 0;
}
