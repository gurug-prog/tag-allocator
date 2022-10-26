#include <stdio.h>
#include <stdint.h>

#include "allocator.h"
#include "block.h"
#include "config.h"
#include "kernel.h"

#if ALLOCATOR_PAGE_SIZE > SIZE_MAX / ALLOCATOR_PAGE_SIZE
#undef ALLOCATOR_PAGE_SIZE
#define ALLOCATOR_PAGE_SIZE (SIZE_MAX / ALLOCATOR_PAGE_SIZE)
#endif
#define ARENA_SIZE ((size_t)ALLOCATOR_PAGE_SIZE * ALLOCATOR_ARENA_PAGES)

#define ARENA_BLOCK_SIZE_MAX (ARENA_SIZE - 2 * BLOCK_STRUCT_SIZE)

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
    if (size > ARENA_BLOCK_SIZE_MAX)
    {
        return NULL;
    }

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
    if (ptr == NULL) return;

    Block* currBlock = NULL;
    Block* neighbour = NULL;
    currBlock = Block_toHeader(ptr);
    Block_setIsBusy(currBlock, false);

    if (!Block_isLast(currBlock))
    {
        neighbour = Block_next(currBlock);
        if (!Block_isBusy(neighbour))
        {
            Block_merge(currBlock, neighbour);
        }
    }
    if (!Block_isFirst(currBlock))
    {
        neighbour = Block_prev(currBlock);
        if (!Block_isBusy(neighbour))
        {
            Block_merge(neighbour, currBlock);
        }
    }
}

void mem_show(char* message)
{
    const Block* block;

    printf("%s\n", message);
    if (arena == NULL)
    {
        printf("No memory allocated for arena.");
        return;
    }

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
    printf("\n");
}
