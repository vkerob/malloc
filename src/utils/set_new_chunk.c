#include "../../include/mem.h"

static void	set_new_chunk_after_block(t_block *block, size_t size, size_t size_to_add_to_align_address)
{
	// we set a new chunk after the block passed as argument

	t_chunk	*new_chunk;

	new_chunk = (void *)block + ALIGN_BLOCK;
	new_chunk->parent_block = block;
	block->free_size -= size + ALIGN_CHUNK + size_to_add_to_align_address;
	new_chunk->size_after = block->size_after - size - size_to_add_to_align_address - ALIGN_CHUNK;
	block->size_after = 0;

	new_chunk->next =  block->chunk;
	new_chunk->prev = NULL;
	
	if (block->chunk)
		block->chunk->prev = new_chunk;

	block->chunk = new_chunk;

	new_chunk->start = (void*)new_chunk + ALIGN_CHUNK;
	new_chunk->size_allocated = size;

	data->chunk_start = new_chunk->start;
}


bool	set_after_block(t_block *block, size_t size)
{
	// if after a block there is enough space to allocate the size
	// we set a new chunk after the block and return true

	size_t	size_to_add_to_align_address;

	size_to_add_to_align_address = (size_t)align_address((void *)block + ALIGN_BLOCK + size) - (size_t)block - ALIGN_BLOCK - size;

	if (block->size_after >= size + size_to_add_to_align_address + ALIGN_CHUNK)
	{
		set_new_chunk_after_block(block, size, size_to_add_to_align_address);
		return (true);
	}

	return (false);
}


static void	set_new_chunk_after_chunk(t_chunk *prev_new_chunk, size_t size, size_t size_to_add_to_align_address)
{
	// we set a new chunk after the chunk passed as argument

	t_chunk	*new_chunk;


	new_chunk = prev_new_chunk->start + (size_t)align_address((void *)prev_new_chunk + prev_new_chunk->size_allocated) - (size_t)prev_new_chunk;
	new_chunk->parent_block = prev_new_chunk->parent_block;
	prev_new_chunk->parent_block->free_size -= size + ALIGN_CHUNK + size_to_add_to_align_address; // if size = 4 size_to_add_to_align_address = 12 with a 16 bytes alignement
	new_chunk->size_after = prev_new_chunk->size_after - size - size_to_add_to_align_address - ALIGN_CHUNK;
	prev_new_chunk->size_after = 0;
	new_chunk->start = (void*)new_chunk + ALIGN_CHUNK;

	link_chunk(new_chunk, prev_new_chunk);

	new_chunk->start = (void*)new_chunk + ALIGN_CHUNK;
	new_chunk->size_allocated = size;

	data->chunk_start = new_chunk->start;
}


bool	set_after_chunk(t_block *block, size_t size)
{
	// if after a chunk in the block there is enough space to allocate the size 
	// we set a new chunk after the chunk and return true

	t_chunk	*prev_new_chunk;
	size_t	size_to_add_to_align_address;

	prev_new_chunk = block->chunk;

	while (prev_new_chunk)
	{
		size_to_add_to_align_address = (size_t)align_address((void *)prev_new_chunk->start + ALIGN_CHUNK + size)
		- (size_t)prev_new_chunk->start - ALIGN_CHUNK - size;

		if (prev_new_chunk->size_after >= size + size_to_add_to_align_address + ALIGN_CHUNK)
		{
			set_new_chunk_after_chunk(prev_new_chunk, size, size_to_add_to_align_address);
			return (true);
		}

		prev_new_chunk = prev_new_chunk->next;
	}

	return (false);
}
