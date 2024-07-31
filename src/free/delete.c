#include "../../include/mem.h"

void	check_if_block_is_unused(t_heap **heap, t_block **parent_block_chunk)
{
	if ((*parent_block_chunk)->chunk == NULL && (*parent_block_chunk)->next != NULL)
	{
		unlink_block((*parent_block_chunk));
		munmap((*parent_block_chunk), (*heap)->size);
	}
}

void	delete_large_heap(t_large_heap *large_heap_used)
{
	munmap(large_heap_used, large_heap_used->size_allocated + ALLIGN_LARGE_HEAP);

	if (data->large_heap == NULL)
	{
		munmap(data->large_heap, sizeof(t_large_heap));
		data->large_heap = NULL;
	}
}
