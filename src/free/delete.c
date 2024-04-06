#include "../../include/mem.h"


static void	delete_block(t_heap **heap, t_block *block, size_t type, size_t page_size)
{
	// free user_space and free_area
	munmap(block->user_space, sizeof(t_user_space));
	
	// unlink block
	if (block->prev != NULL)
		block->prev->next = block->next;
	else
		(*heap)->start_block = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
	munmap(block, sizeof(t_block) + page_size * type);
	block = NULL;

	// free heap if not used
	if ((*heap)->start_block == NULL)
	{
		munmap((*heap), sizeof(t_heap));
		(*heap) = NULL;
	}
}

void	delete_user_space_or_block(t_heap *heap, t_user_space *user_space, size_t type, size_t page_size)
{
	if (heap->free_area->free_size == page_size * type)
	{
		if (type == TINY)
			delete_block(&(data->tiny_heap), user_space->parent_block, type, page_size);
		else if (type == SMALL)
			delete_block(&(data->small_heap), user_space->parent_block, type, page_size);
	}
	else
		munmap(user_space->start_user_space, user_space->size_allocated);
}

void	delete_heap_large(t_heap_large *heap_large, size_t page_size)
{
	munmap(heap_large->start_user_space, heap_large->size_allocated);
	munmap(heap_large, sizeof(t_heap_large) + page_size * LARGE);
	heap_large = NULL;
	if (data->large_heap == NULL)
	{
		munmap(data->large_heap, sizeof(t_heap_large));
		data->large_heap = NULL;
	}
}