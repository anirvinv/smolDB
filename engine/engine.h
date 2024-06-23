#ifndef ENGINE_H
#define ENGINE_H

#include "../parser/parse_structures.h"
#include "engine_structures.h"

int insert(char* key, char* value, FILE* fptr);

int execute_statement(ParserResult* ptr, FILE* fptr);

int add_tuple(BNode* node, char* key, char* value);

BNode* create_leaf_node(uint16_t id, uint16_t parent_id);

BNode* read_node(FILE* fptr, page_number_t id);

void display_node(BNode* node);
#endif  // !ENGINE_H