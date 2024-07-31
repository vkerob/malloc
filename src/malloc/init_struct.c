#include "../../include/mem.h"
#include <unistd.h>

void	*align_address(void *ptr)
{
    uintptr_t addr = (uintptr_t)ptr;

    if (addr % MEN_ALLIGN != 0)
        addr += MEN_ALLIGN - (addr % MEN_ALLIGN); // align the address
    return (void *)addr;
}


void	initialize_data(t_data **data)
{
	struct rlimit	rlimit;

	// initialize the data struct data and heap tiny, small

	if (getrlimit(RLIMIT_AS, &rlimit) == -1)
		return ;

	if (ALLIGN_DATA >= rlimit.rlim_max)
		return ;

	*data = (t_data *)mmap(NULL, ALLIGN_DATA + ALLIGN_HEAP * 2 , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (*data == MAP_FAILED)
		return ;

	(*data)->rlimit = rlimit;
	(*data)->error = false;

	(*data)->tiny_heap = (t_heap *)(*data + ALLIGN_DATA);
	initialize_heap(&(*data)->tiny_heap, TINY_SIZE);

	(*data)->small_heap = (t_heap *)((*data)->tiny_heap + ALLIGN_HEAP);
	initialize_heap(&(*data)->small_heap, SMALL_SIZE);

	(*data)->large_heap = NULL;
}


void	initialize_heap(t_heap **heap, size_t type_size)
{
	// initialize the heap

	(*heap)->start = NULL;
	(*heap)->size = type_size;
}


void	initialize_large_heap(t_large_heap **new_large_heap, t_large_heap *large_heap_prev, size_t size)
{
	// initialize the large heap

	if (sizeof(t_large_heap) + size >= data->rlimit.rlim_max)
	{
		data->error = true;
		return ;
	}

	(*new_large_heap) = mmap(NULL, ALLIGN_LARGE_HEAP + size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (*new_large_heap == MAP_FAILED)
	{
		data->error = true;
		return ;
	}

	// initialize the new node large_heap
	(*new_large_heap)->start = (void *)(*new_large_heap) + ALLIGN_LARGE_HEAP;
	(*new_large_heap)->size_allocated = size;

	// link the new node large_heap
	link_large_heap((*new_large_heap), large_heap_prev);
}


static void	initialize_chunk(t_block *block, size_t size)
{
	// initialize the used user space

	// add new chunk
	block->chunk = (void *)block + ALLIGN_BLOCK;
	block->chunk->start = (void *)block->chunk + ALLIGN_CHUNK;
	block->chunk->size_allocated = size;
	block->chunk->parent_block = block;
	block->chunk->next = NULL;
	block->chunk->prev = NULL;

	// The size to withdraw is the size needed for alignment. 
	// For example, if size = 1, size_to_withdraw = 48 (chunk metadata) + 16 (1 user space + 15 padding) = 64.
	int size_to_withdraw = (size_t)align_address((void *)block + ALLIGN_BLOCK + ALLIGN_CHUNK + size) - (size_t)block - ALLIGN_BLOCK;
	block->free_size = block->free_size - size_to_withdraw;
	block->chunk->size_after = block->free_size;
	data->chunk_start = block->chunk->start;
}

void	allocate(t_heap *heap, size_t size, size_t type_size)
{
	// allocate a new block in the heap passed as argument and initialize the used user space

	t_block	*block = NULL;
	t_block	*block_prev = NULL;

	// find the last block
	block = heap->start;

	if (block != NULL)
	{
		while (block->next)
			block = block->next;
		block_prev = block;			// set the previous block to the last block
		block = block->next;
	}

	if (type_size >= data->rlimit.rlim_max)
	{
		data->error = true;
		return ;
	}

	// allocate the block
	block = mmap(NULL, type_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (block == MAP_FAILED)
	{
		data->error = true;
		return ;
	}

	// link the block
	if (block_prev != NULL)
	{
		block->prev = block_prev;
		block->prev->next = block;
	}
	else
	{
		heap->start = block;
		block->prev = NULL;
	}
	block->next = NULL;

	// initialize the block
	block->parent_heap = heap;
	block->free_size = type_size - ALLIGN_BLOCK;

	block->size_after = 0;
	initialize_chunk(block, size);
}
