#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine.c"
#include "parser.c"

int main() {
    printf("Welcome to smoldb\n");

    char* buff = malloc(1);
    size_t len = 1;

    while (true) {
        getline(&buff, &len, stdin);
        if (strcmp(buff, "exit\n") == 0) break;

        ParserResult result;
        parse_input(buff, strlen(buff), &result);

        execute_statement(&result);

        free_parsed_result(&result);
    }

    free(buff);

    return 0;
}