#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Welcome to smoldb\n");

    char* buff = malloc(1);
    size_t len = 1;

    while (true) {
        getline(&buff, &len, stdin);
        printf("%s", buff);
        if (strcmp(buff, "exit\n") == 0) break;
    }

    free(buff);

    return 0;
}