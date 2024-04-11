#include "../../include/mem.h"

static void	delete_block(t_heap **heap, t_block *block, size_t type, size_t page_size)
{
	t_free_space *free_area = (*heap)->free_area;

	// unlink block
	if (block->prev != NULL)
		block->prev->next = block->next;
	else
		(*heap)->start_block = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
	munmap(block, sizeof(t_block) + page_size * type);
	block = NULL;

	while (free_area != NULL)
	{
		if (free_area->free_size == page_size * type)
		{
			//unlink free_area
			if (free_area->prev != NULL)
				free_area->prev->next = free_area->next;
			else
				(*heap)->free_area = free_area->next;
			if (free_area->next != NULL)
				free_area->next->prev = free_area->prev;
			
			munmap(free_area, sizeof(t_free_space));
			free_area = NULL;
			break ;
		}
		free_area = free_area->next;
	}
	// free heap if not used
	if ((*heap)->start_block == NULL)
	{
		munmap((*heap), sizeof(t_heap));
		(*heap) = NULL;
	}
}

void	delete_user_space_or_block(t_heap *heap, t_user_space *user_space, size_t type, size_t page_size)
{
	t_block *block = user_space->parent_block;
		
	// unlink user_space
	if (user_space->prev != NULL)
		user_space->prev->next = user_space->next;
	else
		block->user_space = user_space->next;
	if (user_space->next != NULL)
		user_space->next->prev = user_space->prev;
	// free user_space
	munmap(user_space, sizeof(t_user_space));

	if (block->user_space == NULL)
		delete_block(&heap, block, type, page_size);
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