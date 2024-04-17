#include "../../include/mem.h"

static void	delete_block_and_free_heap_if_Empty(t_heap **heap, t_block *block)
{
	t_free_area *free_area = (*heap)->free_area;

	unlink_block(block);
	munmap(block, sizeof(t_block) + (*heap)->size);
	block = NULL;

	// free a node of free_area if block is empty
	while (free_area != NULL)
	{
		if (free_area->free_size == (*heap)->size)
		{
			//unlink free_area
			unlink_free_area(free_area);
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
		
	unlink_user_space(user_space);
	munmap(user_space, sizeof(t_user_space));
	if (block->user_space == NULL)
		delete_block_and_free_heap_if_Empty(heap, block);
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