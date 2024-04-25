#include "../../include/mem.h"

static void	delete_block_and_free_heap_if_Empty(t_heap **heap, t_block *block)
{

	block->used_user_space = NULL;
	block->unused_user_space = NULL;
	unlink_block(block);
	munmap(block, (*heap)->size);

	// free heap if not used
	if ((*heap)->start_block == NULL)
	{
		munmap((*heap), sizeof(t_heap));
		(*heap) = NULL;
	}
}

void	check_if_block_is_unused(t_heap **heap, t_block *parent_block_used_user_space)
{
	if (parent_block_used_user_space->used_user_space == NULL)
		delete_block_and_free_heap_if_Empty(heap, parent_block_used_user_space);
}

void	delete_large_heap(t_large_heap *large_heap_used)
{
	
	munmap(large_heap_used, large_heap_used->size_allocated + sizeof(t_large_heap));
	if (data->large_heap == NULL)
	{
		munmap(data->large_heap, sizeof(t_large_heap));
		data->large_heap = NULL;
	}
}