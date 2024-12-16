#include "../../includes/malloc.h"

bool	search_free_space(t_heap *heap, size_t size)
{
	t_block	*block;

	// this function try to find a free space in the heap passed as argument
	// if it doesn't find a free space, it returns false

	if (heap == NULL)
		return (NULL);

	block = heap->start;

	while (block)
	{
		// if in the block there is enough space to allocate the size
		if (block->free_size >= size)
		{
			// if after the block there is enough space to allocate the size
			if (set_after_block(block, size))
				return (true);
			// if after a chunk in the block there is enough space to allocate the size
			else if (set_after_chunk(block, size))
				return (true);
		}
	
		block = block->next;
	}

	return (false);
}
