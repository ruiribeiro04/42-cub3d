#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **ft_split(char const *s, char c) {
    char **res = malloc(4 * sizeof(char *));
    res[0] = strdup("255");
    res[1] = strdup("200");
    res[2] = strdup("\n");
    res[3] = NULL;
    return res;
}

static int is_valid_number(char *str) {
    if (!str || !*str) return 0;
    while (*str) {
        if (*str < '0' || *str > '9') return 0;
        str++;
    }
    return 1;
}

int main() {
    char line[] = "C 255 200 \n";
    char **values = ft_split("bla", ' ');
    int result = 0;
    int i = 0;
    
    // Strip newlines from values
    while (!result && i < 3) {
        char *tmp = values[i];
        while (tmp && *tmp && *tmp != '\n') tmp++;
        if (*tmp == '\n') *tmp = '\0';
        i++;
    }

    printf("val0: '%s', val1: '%s', val2: '%s'\n", values[0], values[1], values[2]);
    printf("is_valid_number(values[2]) = %d\n", is_valid_number(values[2]));

    int cond = (!result && (!is_valid_number(values[0]) || !is_valid_number(values[1]) || !is_valid_number(values[2])));
    printf("condition = %d\n", cond);
    
    if (cond) {
        printf("Error: Color values must be numeric\n");
        result = 1;
    }
    printf("Result is %d\n", result);
    return 0;
}
