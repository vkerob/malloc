#include "../include/mem.h"

void	initialize_data(t_data **data)
{
	*data = (t_data *)mmap(NULL, sizeof(t_data), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	(*data)->tiny = NULL;
	(*data)->small = NULL;
	(*data)->large = NULL;
	(*data)->error = false;
	(*data)->start_user_space = NULL;
}

void	initialize_heap(t_heap *heap, size_t size)
{
	heap->size = size;
	heap->count_blocks = 0;
	heap->start_block = NULL;
}

void	initialize_block(t_mem_block *block, size_t size, t_mem_block *block_prev)
{
	block->start_user_space = block + sizeof(t_mem_block);
	block->free_size = size;
	block->free_area = NULL;
	if (block_prev != NULL)
	{
		block->prev = block_prev;
		block->prev->next = block;
	}
	else
		block->prev = NULL;
	block->next = NULL;
}