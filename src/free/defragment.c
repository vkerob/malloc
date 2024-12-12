#include "../../include/mem.h"

void defragment(t_chunk *chunk)
{
	// defragment the chunk passed as argument
	// add the size of the chunk to the free size of the block
	// if it's the first chunk in the block we add the size after the start of the block
	// else we add the size after the previous chunk
	size_t			size;

	// size is equal 
	size = (size_t)align_address(chunk->start + chunk->size_allocated) - (size_t)chunk->start;
	chunk->parent_block->free_size += ALIGN_CHUNK + size;

	// if it's the first chunk in the block we add the size after the start of the block
	if (chunk == chunk->parent_block->chunk)
		chunk->parent_block->size_after += ALIGN_CHUNK + size + chunk->size_after;
	// else we add the size after the previous chunk
	else
		chunk->prev->size_after += ALIGN_CHUNK + size + chunk->size_after;

}
