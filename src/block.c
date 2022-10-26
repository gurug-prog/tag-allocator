#include "block.h"


void* Block_toPayload(const Block* self)
{
    return (char*)self + BLOCK_STRUCT_SIZE;
}

Block* Block_next(const Block* self)
{
    return (Block*)
        ((char*)self + BLOCK_STRUCT_SIZE + self->currBlockSize);
}

size_t Block_getCurrBlockSize(const Block* self)
{
    return self->currBlockSize;
}

void Block_setCurrBlockSize(Block* self, size_t size)
{
    self->currBlockSize = size;
}

size_t Block_getPrevBlockSize(const Block* self)
{
    return self->prevBlockSize;
}

void Block_setPrevBlockSize(Block* self, size_t size)
{
    self->prevBlockSize = size;
}

bool Block_isBusy(const Block* self)
{
    return self->isBusy;
}

void Block_setIsBusy(Block* self, bool value)
{
    self->isBusy = value;
}

bool Block_isFirst(const Block* self)
{
    return self->isFirst;
}

void Block_setIsFirst(Block* self, bool value)
{
    self->isFirst = value;
}

bool Block_isLast(const Block* self)
{
    return self->isLast;
}

void Block_setIsLast(Block* self, bool value)
{
    self->isLast = value;
}

void Block_init(Block* self, size_t size)
{
    self->currBlockSize = size;
    self->prevBlockSize = 0;
    self->isBusy = false;
    self->isFirst = true;
    self->isLast = true;
}
