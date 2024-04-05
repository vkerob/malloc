#include "../../include/mem.h"

// allocates the heap passed as argument if it doesn't exist, a new block on him and allocates a new user space on the block of the size passed as argument 

void	allocate(t_heap **heap, size_t size, size_t type)
{
	t_mem_block		*block_tmp;
	t_mem_block		*block_prev = NULL;

	write(1, "allocate\n", 9);
	// allocates the heap if it doesn't exist
	if (*heap == NULL)
	{
		(*heap) = mmap(NULL, sizeof(t_heap), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (*heap == MAP_FAILED)
		{
			data->error = true;
			return ;
		}
		initialize_heap(*heap, type);
	}
	// allocates a new block
	block_tmp = (*heap)->start_block;
	if (block_tmp != NULL)
	{
		// find the last block
		while (block_tmp->next)
			block_tmp = block_tmp->next;
		block_prev = block_tmp;											// set the previous block to the last block
		block_tmp = block_tmp->next;
	}
	block_tmp = mmap(NULL, sizeof(t_mem_block) + getpagesize() * type, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (block_tmp == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	initialize_block(heap, block_tmp, size, block_prev, type);
}



void	allocate_large(size_t size)
{
	t_heap_large	*heap_large_tmp;
	t_heap_large	*heap_large_prev;

	heap_large_tmp = data->large;
	if (heap_large_tmp != NULL)
	{
		while (heap_large_tmp->next)
			heap_large_tmp = heap_large_tmp->next;
		heap_large_prev = heap_large_tmp;
		heap_large_tmp = heap_large_tmp->next;
	}
	heap_large_tmp = mmap(NULL, sizeof(t_heap_large) + getpagesize() * LARGE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (heap_large_tmp == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	heap_large_tmp->start_user_space = heap_large_tmp + sizeof(t_heap_large);
	heap_large_tmp->size_allocated = size;
	heap_large_tmp->next = NULL;
	heap_large_tmp->prev = heap_large_prev;
	if (heap_large_prev != NULL)
		heap_large_prev->next = heap_large_tmp;
}