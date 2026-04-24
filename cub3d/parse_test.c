#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "includes/cub3d.h"
#include "includes/libft.h"

int main()
{
	int fd = open("cub3D_leaks_maps_tester/invalid_maps/invalid_RGB_000.cub", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd))) {
		printf("READ: %s", line);
		free(line);
	}
	close(fd);
	return 0;
}
