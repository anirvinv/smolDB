#ifndef ENGINE
#define ENGINE

#include "engine.h"

#include <stdio.h>
#include <string.h>

#include "../parser/parse_structures.h"

int execute_statement(ParserResult* ptr, FILE* fptr) {
    if (ptr->len == 3 && (strcmp(ptr->tokens[0], "insert") == 0 ||
                          strcmp(ptr->tokens[0], "i") == 0)) {
        insert(ptr->tokens[1], ptr->tokens[2], fptr);
    } else if (ptr->len == 3 && strcmp(ptr->tokens[0], "delete") == 0) {
        printf("Delete\n");
    } else if (ptr->len == 1 && strcmp(ptr->tokens[0], "dr") == 0) {
        BNode* root = read_node(fptr, 0);
        if (root == NULL) {
            perror("Root node does not exist\n");
            return 1;
        }
        display_node(root);
        free(root);
    } else {
        perror("Invalid statement\n");
        return 1;
    }
    return 0;
}

int insert(char* key, char* value, FILE* fptr) {
    // read root node

    BNode* root = read_node(fptr, 0);
    // if root is null, create a new root
    if (root == NULL) {
        root = create_leaf_node(0, 0);
    }

    if (add_tuple(root, key, value) == 1) {
        perror("Error adding tuple\n");
        return 1;
    }

    // if the node is full at this point, split it?

    // write root to file
    fseek(fptr, 0, SEEK_SET);
    fwrite(root, sizeof(BNode), 1, fptr);
    free(root);
    return 0;
}

int add_tuple(BNode* node, char* key, char* value) {
    // find the index to insert the tuple
    int index = 0;
    CellPointer* pointer;
    for (int i = 0; i < node->header.num_cells; i++) {
        pointer = (CellPointer*)(node->data + i * sizeof(CellPointer));
        if (strcmp(key, node->data + pointer->offset) > 0) {
            index++;
        } else {
            break;
        }
    }

    // move the cells to the right to make space for the new cell
    for (int i = node->header.num_cells; i > index; i--) {
        pointer = (CellPointer*)(node->data + (i - 1) * sizeof(CellPointer));
        memcpy(node->data + i * sizeof(CellPointer), pointer,
               sizeof(CellPointer));
    }

    // insert the new cell
    pointer = (CellPointer*)(node->data + index * sizeof(CellPointer));

    pointer->size = strlen(key) + strlen(value) + 2;
    pointer->offset = node->header.free_end - pointer->size;

    strcpy(node->data + pointer->offset, key);
    strcpy(node->data + pointer->offset + strlen(key) + 1, value);

    // update the metadata
    node->header.num_cells++;
    node->header.free_end -= pointer->size;

    return 0;
}

BNode* create_leaf_node(uint16_t id, uint16_t parent_id) {
    BNode* node = malloc(sizeof(BNode));
    node->header.valid = 1;
    node->header.node_type = LEAF;
    node->header.id = id;
    node->header.num_cells = 0;
    node->header.parent_id = parent_id;
    node->header.free_start = 0;  // data + free_start = first cell pointer
    node->header.free_end =
        PAGE_SIZE - sizeof(BNodeHeader);  // start of first cell

    return node;
}

BNode* read_node(FILE* fptr, page_number_t id) {
    fseek(fptr, id * PAGE_SIZE, SEEK_SET);
    BNode* node = malloc(sizeof(BNode));
    fread(node, sizeof(BNode), 1, fptr);

    // if the file pointer is at the end of the file, the node does not exist
    if (feof(fptr)) {
        free(node);
        return NULL;
    }

    return node;
}

void display_node(BNode* node) {
    // display the metadata of the node
    printf("Node ID: %d\n", node->header.id);
    printf("Node type: %d\n", node->header.node_type);
    printf("Number of cells: %d\n", node->header.num_cells);

    // display the cells in the node
    for (int i = 0; i < node->header.num_cells; i++) {
        CellPointer* pointer =
            (CellPointer*)(node->data + i * sizeof(CellPointer));
        printf("\tKey: %s\n", node->data + pointer->offset);
        printf("\tValue: %s\n", node->data + pointer->offset +
                                    strlen(node->data + pointer->offset) + 1);
    }
}

#endif  // !ENGINE