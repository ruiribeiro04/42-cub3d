#include "cub3d.h"

# include <string.h>

char **ft_get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = strdup("111111111111111");
    map[1] = strdup("100000000000001");
    map[2] = strdup("100000000000001");
    map[3] = strdup("100000100000001");
    map[4] = strdup("100000000000001");
    map[5] = strdup("100000010000001");
    map[6] = strdup("100001000000001");
    map[7] = strdup("100000000000001");
    map[8] = strdup("100000000000001");
    map[9] = strdup("111111111111111");
    map[10] = NULL;
    return map;
}
