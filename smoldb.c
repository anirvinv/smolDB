#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine/engine.c"
#include "parser/parser.c"

int main() {
    printf("Welcome to smoldb\n");

    char* buff = malloc(1);
    size_t len = 1;
    FILE* fptr = fopen("btree.dat", "wr+");
    while (true) {
        printf("> ");
        getline(&buff, &len, stdin);

        if (strcmp(buff, "exit\n") == 0) break;

        ParserResult result;
        parse_input(buff, strlen(buff), &result);

        execute_statement(&result, fptr);

        free_parsed_result(&result);
    }

    free(buff);
    fclose(fptr);

    return 0;
}