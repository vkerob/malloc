#include "../../include/mem.h"

void	unlink_large_heap(t_large_heap *large_heap)
{
	if (large_heap->prev != NULL)
		large_heap->prev->next = large_heap->next;
	else
		data->large_heap = large_heap->next;
	if (large_heap->next != NULL)
		large_heap->next->prev = large_heap->prev;
}

void	unlink_block(t_block *block)
{
	if (block->prev != NULL)
		block->prev->next = block->next;
	else
		block->parent_heap->start = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
}

void	unlink_chunk(t_chunk *chunk)
{
	if (chunk->prev != NULL)
		chunk->prev->next = chunk->next;
	else
		chunk->parent_block->chunk = chunk->next;
	if (chunk->next != NULL)
		chunk->next->prev = chunk->prev;
}