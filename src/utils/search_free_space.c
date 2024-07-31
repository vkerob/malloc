#include "../../include/mem.h"

static void	set_new_used_user_space(void *space, size_t size, size_t size_to_add_to_align_address, int is_block)
{
	t_chunk	*new_chunk, *prev_new_chunk;
	t_block *block;

	if (is_block) 
	{
		block = (t_block *)space;
		new_chunk = (void *)block + ALLIGN_BLOCK;
		new_chunk->parent_block = block;
		block->free_size -= size + ALLIGN_CHUNK + size_to_add_to_align_address;
		new_chunk->size_after = block->size_after - size - size_to_add_to_align_address - ALLIGN_CHUNK;
		block->size_after = 0;

		new_chunk->next =  block->chunk;
		new_chunk->prev = NULL;
		
		if (block->chunk)
			block->chunk->prev = new_chunk;
		block->chunk = new_chunk;
	} 
	else 
	{
		prev_new_chunk = (t_chunk *)space;
		new_chunk = prev_new_chunk->start + (size_t)align_address((void *)prev_new_chunk + prev_new_chunk->size_allocated) - (size_t)prev_new_chunk;
		new_chunk->parent_block = prev_new_chunk->parent_block;
		prev_new_chunk->parent_block->free_size -= size + ALLIGN_CHUNK + size_to_add_to_align_address; // if size = 4 size_to_add_to_align_address = 12 with a 16 bytes alignement
		new_chunk->size_after = prev_new_chunk->size_after - size - size_to_add_to_align_address - ALLIGN_CHUNK;
		prev_new_chunk->size_after = 0;
		new_chunk->start = (void*)new_chunk + ALLIGN_CHUNK;

		link_chunk(new_chunk, prev_new_chunk);
	}

	new_chunk->start = (void*)new_chunk + ALLIGN_CHUNK;
	new_chunk->size_allocated = size;

	data->chunk_start = new_chunk->start;
}

bool	search_free_space(t_heap *heap, size_t size)
{
	t_block	*block;
	t_chunk	*prev_new_chunk;
	size_t	size_to_add_to_align_address;


	if (heap == NULL)
		return (NULL);
	block = heap->start;
	while (block)
	{

		// if in the block there is enough space to allocate the size
		if (block->free_size >= size)
		{
			// if after the block there is enough space to allocate the size
			size_to_add_to_align_address = (size_t)align_address((void *)block + ALLIGN_BLOCK + size) - (size_t)block - ALLIGN_BLOCK - size;

			if (block->size_after >= size + size_to_add_to_align_address + ALLIGN_CHUNK)
			{
				set_new_used_user_space(block, size, size_to_add_to_align_address, 1); // block->chunk = new_chunk
				return (true);
			}

			// if after a chunk there is enough space to allocate the size
			prev_new_chunk = block->chunk;
			while (prev_new_chunk)
			{
				size_to_add_to_align_address = (size_t)align_address((void *)prev_new_chunk->start + ALLIGN_CHUNK + size)
				- (size_t)prev_new_chunk->start - ALLIGN_CHUNK - size;

				if (prev_new_chunk->size_after >= size + size_to_add_to_align_address + ALLIGN_CHUNK)
				{
					set_new_used_user_space(prev_new_chunk, size, size_to_add_to_align_address, 0);
					return (true);
				}

				prev_new_chunk = prev_new_chunk->next;
			}
		}
		block = block->next;
	}
	return (false);
}
