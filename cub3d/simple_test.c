#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

static int create_test_map(const char *filename, const char *content) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return 1;
    if (content && *content) write(fd, content, strlen(content));
    close(fd);
    return 0;
}

static void remove_test_map(const char *filename) {
    unlink(filename);
}

int main() {
    const char *map = "NO ./textures/north.xpm\nSO ./textures/south.xpm\n"
                     "WE ./textures/west.xpm\nEA ./textures/east.xpm\n"
                     "F 220,100,0\nC 225,30,0\n"
                     "111111\n100101\n101001\n1100N1\n111111\n";
    
    create_test_map("simple_test.cub", map);
    
    // Read and verify file contents
    FILE *f = fopen("simple_test.cub", "r");
    char line[256];
    int line_num = 0;
    
    printf("File contents:\n");
    while (fgets(line, sizeof(line), f)) {
        printf("  Line %d: %s", line_num++, line);
    }
    fclose(f);
    
    remove_test_map("simple_test.cub");
    return 0;
}
