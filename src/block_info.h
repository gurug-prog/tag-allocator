#include "block.h"

#define FULL_BLOCK_SIZE(block) \
    BLOCK_STRUCT_SIZE + Block_getCurrBlockSize(block)
