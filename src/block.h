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

void* Block_toPayload(const Block *block)
{
    return (char*)block + BLOCK_STRUCT_SIZE;
}

void* Block_next(const Block *block)
{
    return (Block*)
        ((char*)block + BLOCK_STRUCT_SIZE + block->currBlockSize);
}

size_t Block_getCurrBlockSize(const Block *block)
{
    return block->currBlockSize;
}

size_t Block_getPrevBlockSize(const Block *block)
{
    return block->prevBlockSize;
}
