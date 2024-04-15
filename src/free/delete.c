#include "../../include/mem.h"

static void	delete_block(t_heap **heap, t_block *block)
{
	t_free_area *free_area = (*heap)->free_area;

	// unlink block
	if (block->prev != NULL)
		block->prev->next = block->next;
	else
		(*heap)->start_block = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
	munmap(block, sizeof(t_block) + (*heap)->size);
	block = NULL;

	while (free_area != NULL)
	{
		if (free_area->free_size == (*heap)->size)
		{
			//unlink free_area
			if (free_area->prev != NULL)
				free_area->prev->next = free_area->next;
			else
				(*heap)->free_area = free_area->next;
			if (free_area->next != NULL)
				free_area->next->prev = free_area->prev;
			
			munmap(free_area, sizeof(t_free_area));
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

void	delete_user_space_or_block(t_heap **heap, t_user_space *user_space)
{
	t_block *block = user_space->parent_block;
		
	// unlink user_space
	unlink_user_space(user_space);
	// free user_space
	munmap(user_space, sizeof(t_user_space));

	if (block->user_space == NULL)
		delete_block(heap, block);
}

void	delete_large_heap(t_large_heap *large_heap)
{
	
	munmap(large_heap, large_heap->size_allocated);
	large_heap = NULL;
	if (data->large_heap == NULL)
	{
		munmap(data->large_heap, sizeof(t_large_heap));
		data->large_heap = NULL;
	}
}