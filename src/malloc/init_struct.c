#include "../../include/mem.h"
#include <unistd.h>

void *align_address(void *ptr)
{
    uintptr_t addr = (uintptr_t)ptr;

    if (addr % MEN_ALLIGN != 0)
        addr += MEN_ALLIGN - (addr % MEN_ALLIGN); // align the address
    return (void *)addr;
}

void	initialize_data(t_data **data)
{
	struct rlimit	rlimit;

	if (getrlimit(RLIMIT_AS, &rlimit) == -1)
		return ;
	if (sizeof(t_data) >= rlimit.rlim_max)
		return ;
	*data = (t_data *)mmap(NULL, sizeof(t_data), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (*data == MAP_FAILED)
		return ;
	(*data)->tiny_heap = NULL;
	(*data)->small_heap = NULL;
	(*data)->large_heap = NULL;
	(*data)->error = false;
	(*data)->user_space_pointer = NULL;
	(*data)->rlimit = rlimit;
}

static void	initialize_unused_user_space(t_block *block, size_t size, size_t type_size)
{
	t_user_space	*prev_unused_user_space;

	block->unused_user_space = align_address((t_user_space *)((void *)block + sizeof(t_block) + sizeof(t_user_space) + size));
	block->unused_user_space->start_user_space = align_address((void *)block->unused_user_space + sizeof(t_user_space));
	block->unused_user_space->size_allocated = (size_t)(type_size) - (size + sizeof(t_block) + sizeof(t_user_space) * 2);
	block->unused_user_space->parent_block = block;

	// link the unused_user_space
	block->unused_user_space->next = NULL;
	if (block->prev != NULL)
	{
		prev_unused_user_space = block->prev->unused_user_space;
		if (prev_unused_user_space == NULL)
		{
			block->unused_user_space->prev = NULL;
			return ;
		}
		while (prev_unused_user_space->next)
			prev_unused_user_space = prev_unused_user_space->next;
		block->unused_user_space->prev = prev_unused_user_space;
		prev_unused_user_space->next = block->unused_user_space;
	}
	else
		block->unused_user_space->prev = NULL;
}

static void	initialize_used_user_space(t_block *block, size_t size)
{
	// add new used_user_space
	block->used_user_space = align_address((t_user_space *)((void *)block + sizeof(t_block)));
	block->used_user_space->start_user_space = align_address((void *)block->used_user_space + sizeof(t_user_space));
	block->used_user_space->size_allocated = size;
	block->used_user_space->parent_block = block;
	block->used_user_space->next = NULL;
	block->used_user_space->prev = NULL;

	data->user_space_pointer = block->used_user_space->start_user_space;
}

void	initialize_block(t_heap *heap, size_t size, size_t type_size)
{
	t_block	*block = NULL;
	t_block	*block_prev = NULL;

	// find the last block
	block = heap->start_block;
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
		heap->start_block = block;
		block->prev = NULL;
	}
	block->next = NULL;

	// initialize the block
	block->parent_heap = heap;
	initialize_used_user_space(block, size);
	initialize_unused_user_space(block, size, type_size);
}

void	initialize_heap(t_heap **heap, size_t type_size)
{

	if (sizeof(t_heap) >= data->rlimit.rlim_max)
	{
		data->error = true;
		return ;
	}
	(*heap) = mmap(NULL, sizeof(t_heap), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (*heap == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	(*heap)->start_block = NULL;
	(*heap)->size = type_size;
}

void	initialize_large_heap(t_large_heap **new_large_heap, t_large_heap *large_heap_prev, size_t size)
{
	if (sizeof(t_large_heap) + size >= data->rlimit.rlim_max)
	{
		data->error = true;
		return ;
	}
	(*new_large_heap) = mmap(NULL, sizeof(t_large_heap) + size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (*new_large_heap == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	// initialize the new node large_heap
	(*new_large_heap)->start_user_space = (void *)(*new_large_heap) + sizeof(t_large_heap);
	(*new_large_heap)->size_allocated = size;

	// link the new node large_heap
	link_large_heap((*new_large_heap), large_heap_prev);
}
