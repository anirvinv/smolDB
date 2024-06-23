#ifndef PARSER_H
#define PARSER_H

#include "parse_structures.h"

int count_tokens(char* buffer, int len);
int parse_input(char* buffer, int len, ParserResult* buff);
int free_parsed_result(ParserResult* parsed_res_ptr);

#endif  // !PARSER_H