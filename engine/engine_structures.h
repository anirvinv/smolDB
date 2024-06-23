#ifndef ENGINE_STRUCTURES_H
#define ENGINE_STRUCTURES_H

#include <stdint.h>

#define PAGE_SIZE 4096

typedef uint16_t page_number_t;

enum NodeType { ROOT = 1, INTERNAL, LEAF };

typedef struct BNodeHeader {
    uint8_t valid;

    // leaf, internal, or root
    uint8_t node_type;

    // file offset
    page_number_t id;

    // number of key, value pairs in node
    uint16_t num_cells;

    // parent offset
    uint16_t parent_id;

    uint16_t free_start;
    uint16_t free_end;

} BNodeHeader;

typedef struct BNode {
    BNodeHeader header;

    char data[PAGE_SIZE - sizeof(BNodeHeader)];  // 4096 - 12 = 4084
    /**
     * Cell structure:
     *
     * | key_size | value_size | key | value |
     */

} BNode;

typedef struct CellPointer {
    uint16_t offset;
    uint16_t size;
    uint16_t right_child_id;
} CellPointer;

#endif  // !ENGINE_STRUCTURES_H
