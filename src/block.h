#include <stdbool.h>

#include "allocator_impl.h"

typedef struct Block Block;
struct Block
{
    size_t currBlockSize;
    size_t prevBlockSize;
    bool isBusy;
    bool isFirst;
    bool isLast;
};

#define BLOCK_STRUCT_SIZE   ROUND_BYTES(sizeof(struct Block))


void    Block_init              (Block* self, size_t size);

void*   Block_toPayload         (const Block* self);
Block*  Block_next              (const Block* self);
size_t  Block_getCurrBlockSize  (const Block* self);
size_t  Block_getPrevBlockSize  (const Block* self);
bool    Block_isBusy            (const Block* self);
bool    Block_isFirst           (const Block* self);
bool    Block_isLast            (const Block* self);
