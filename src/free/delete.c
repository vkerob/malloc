#include "../../include/mem.h"


static void	delete_block(t_mem_block *block, size_t type, size_t page_size)
{
	// free user_space and free_area
	munmap(block->user_space, sizeof(t_user_space));
	munmap(block->free_area, sizeof(t_free_space));
	
	// unlink block
	if (block->prev != NULL)
		block->prev->next = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
	munmap(block, sizeof(t_mem_block) + page_size * type);
	block = NULL;

	// free heap if no not used
	if (data->tiny->start_block == NULL)
	{
		munmap(data->tiny, sizeof(t_heap));
		data->tiny = NULL;
	}
}

void	delete_user_space_or_block(t_user_space *user_space, size_t type, size_t page_size)
{
	if (user_space->parent_block->free_area->free_size == page_size * type)
		delete_block(user_space->parent_block, type, page_size);
	else
		munmap(user_space->start_user_space, user_space->size_allocated);
}

void	delete_heap_large(t_heap_large *heap_large, size_t page_size)
{
	munmap(heap_large->start_user_space, heap_large->size_allocated);
	munmap(heap_large, sizeof(t_heap_large) + page_size * LARGE);
	heap_large = NULL;
	if (data->large == NULL)
	{
		munmap(data->large, sizeof(t_heap_large));
		data->large = NULL;
	}
}