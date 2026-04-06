#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../includes/cub3d.h"
#include "../libs/libft/libft.h"
#include "../libs/libft/42_get_next_line/get_next_line.h"

int main() {
    t_game game;
    const char *map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
                     "WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
                     "F 220,100,0\nC 225,30,0\n"
                     "111111\n100101\n101001\n1100N1\n111111\n";
    
    // Create test file
    int fd = open("trace_test.cub", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, map, strlen(map));
    close(fd);
    
    // Test parsing
    memset(&game, 0, sizeof(t_game));
    game.floor_color = -1;
    game.ceiling_color = -1;
    
    printf("Parsing trace_test.cub...\n");
    int result = ft_parse_cub_file("trace_test.cub", &game);
    printf("Parse result: %d\n", result);
    
    if (result == 0) {
        printf("Success!\n");
        printf("North: %s\n", game.path_north ? game.path_north : "NULL");
        printf("South: %s\n", game.path_south ? game.path_south : "NULL");
    }
    
    ft_free_game(&game);
    unlink("trace_test.cub");
    return 0;
}
