#include <stdio.h>

#include "allocator.h"
#include "block.h"
#include "config.h"
#include "kernel.h"

#define ARENA_SIZE (ALLOCATOR_PAGE_SIZE * ALLOCATOR_ARENA_PAGES)

static Block* arena = NULL;

static int arenaAlloc()
{
    arena = kernel_mem_alloc(ARENA_SIZE);
    if (arena == NULL) return -1;

    return 0;
}

static void arenaInit()
{
    Block_init(arena, ARENA_SIZE - BLOCK_STRUCT_SIZE);
}

void* mem_alloc(size_t size)
{
    if (arena == NULL)
    {
        if (arenaAlloc() < 0) return NULL;
        arenaInit();
    }
    size = ROUND_BYTES(size);
    
    Block* block = NULL;
    for (block = arena;; block = Block_next(block))
    {
        if (!Block_isBusy(block) && Block_getCurrBlockSize(block) >= size)
        {
            Block_split(block, size);
            return Block_toPayload(block);
        }

        if (Block_isLast(block)) break;
    }


    return NULL;
}

void* mem_realloc(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

void mem_free(void* ptr)
{
    return free(ptr);
}

void mem_show()
{
    const Block* block;
    for (block = arena;; block = Block_next(block))
    {
        printf("%s %10zu %10zu%s%s\n",
            Block_isBusy(block) ? "busy" : "free",
            Block_getCurrBlockSize(block),
            Block_getPrevBlockSize(block),
            Block_isFirst(block) ? " first" : "",
            Block_isLast(block) ? " last" : ""
        );

        if (Block_isLast(block)) break;
    }
}
