#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
                     "WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
                     "F 220,100,0\nC 225,30,0\n"
                     "111111\n100101\n101001\n1100N1\n111111\n";
    
    int fd = open("debug_test.cub", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    
    write(fd, map, strlen(map));
    close(fd);
    
    // Read it back
    FILE *f = fopen("debug_test.cub", "r");
    char line[256];
    printf("File contents:\n");
    while (fgets(line, sizeof(line), f)) {
        printf("  %s", line);
    }
    fclose(f);
    
    unlink("debug_test.cub");
    return 0;
}
