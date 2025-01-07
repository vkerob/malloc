#include "../../includes/malloc.h"

void	link_large_heap(t_large_heap *new_large_heap, t_large_heap *large_heap_prev)
{
	new_large_heap->next = NULL;

	if (large_heap_prev != NULL)
	{
		new_large_heap->prev = large_heap_prev;
		large_heap_prev->next = new_large_heap;
	}
	else
	{
		data->large_heap = new_large_heap;
		new_large_heap->prev = NULL;
	}

}

void	link_chunk(t_chunk *chunk, t_chunk *chunk_prev)
{
	chunk->next = chunk_prev->next;
	pthread_mutex_unlock(&lock);
	ft_printf("chunk->next = %p\n", chunk->next);
	pthread_mutex_lock(&lock);
	chunk->prev = chunk_prev;

	if (chunk_prev)
		chunk_prev->next = chunk;
	else
		chunk->parent_block->chunk = chunk;

}
