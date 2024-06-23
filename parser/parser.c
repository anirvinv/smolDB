#ifndef PARSER
#define PARSER

#include "parser.h"

#include <stdio.h>
#include <string.h>

int count_tokens(char* buffer, int len) {
    int num_tokens = 0;
    char* dup = strndup(buffer, len);

    char* rest = dup;
    while (strtok_r(rest, " ", &rest)) {
        num_tokens++;
    }
    free(dup);
    return num_tokens;
}

int parse_input(char* buffer, int len, ParserResult* pr) {
    int num_tokens = count_tokens(buffer, len);
    pr->len = num_tokens;
    if (num_tokens == 0) return 1;
    // printf("num_tokens: %d\n", num_tokens);
    pr->tokens = (char**)malloc(num_tokens * sizeof(char*));

    // the last character has a newline, so we need to remove it
    buffer[len - 1] = '\0';

    char* rest = buffer;
    for (int i = 0; i < num_tokens; i++) {
        pr->tokens[i] = strtok_r(rest, " ", &rest);
    }
    return 0;
}

int free_parsed_result(ParserResult* ptr) {
    if (ptr->len) free(ptr->tokens);
}

#endif  // !1
