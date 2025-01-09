#include "../../includes/malloc.h"

void	check_if_block_is_unused(t_heap **heap, t_block **parent_block_chunk)
{
	// check if the block is unused and free the block only if it's not the last block

	if ((*parent_block_chunk)->chunk == NULL && (*parent_block_chunk)->next != NULL)
	{
		unlink_block((*parent_block_chunk));
		munmap((*parent_block_chunk), (*heap)->size);
	}
}