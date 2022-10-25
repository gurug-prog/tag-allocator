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

void* Block_toPayload(const Block* self)
{
    return (char*)self + BLOCK_STRUCT_SIZE;
}

void* Block_next(const Block* self)
{
    return (Block*)
        ((char*)self + BLOCK_STRUCT_SIZE + self->currBlockSize);
}

size_t Block_getCurrBlockSize(const Block* self)
{
    return self->currBlockSize;
}

size_t Block_getPrevBlockSize(const Block* self)
{
    return self->prevBlockSize;
}

bool Block_isBusy(const Block* self)
{
    return self->isBusy;
}

bool Block_isFirst(const Block* self)
{
    return self->isFirst;
}

bool Block_isLast(const Block* self)
{
    return self->isLast;
}

void Block_init(Block* self, size_t size)
{
    self->currBlockSize = size;
    self->prevBlockSize = 0;
    self->isBusy = false;
    self->isFirst = true;
    self->isLast = true;
}
