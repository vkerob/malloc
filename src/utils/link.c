#include "../../includes/malloc.h"


void link_chunk_after_block(t_block *block, t_chunk *new_chunk)
{
	new_chunk->next =  block->chunk;
	new_chunk->prev = NULL;
	
	if (block->chunk)
		block->chunk->prev = new_chunk;

	block->chunk = new_chunk;
}


void link_chunk_after_chunk(t_chunk *new_chunk, t_chunk *prev_new_chunk)
{
	new_chunk->next =  prev_new_chunk->next;
	new_chunk->prev = prev_new_chunk;

	if (prev_new_chunk->next)
		prev_new_chunk->next->prev = new_chunk;

	prev_new_chunk->next = new_chunk;
}
