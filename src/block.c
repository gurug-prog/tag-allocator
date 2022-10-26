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

void Block_initDefault(Block* self)
{
    self->isBusy = false;
    self->isFirst = false;
    self->isLast = false;
}

void Block_split(Block* self, size_t size)
{
    Block* cuttedBlock = NULL;
    size_t oldSizeCurrBlock = Block_getCurrBlockSize(self);

    Block_setIsBusy(self, true);
    if (Block_getCurrBlockSize(self) >= size + BLOCK_STRUCT_SIZE)
    {
        Block_setCurrBlockSize(self, size);

        cuttedBlock = Block_next(self);
        Block_initDefault(cuttedBlock);
        Block_setCurrBlockSize(cuttedBlock,
            oldSizeCurrBlock - size - BLOCK_STRUCT_SIZE);
        Block_setPrevBlockSize(cuttedBlock, size);

        if (Block_isLast(self))
        {
            Block_setIsLast(self, false);
            Block_setIsLast(cuttedBlock, true);
        }
        else
        {
            Block_setPrevBlockSize(
                Block_next(cuttedBlock),
                Block_getCurrBlockSize(cuttedBlock));
        }
        
    }
}
