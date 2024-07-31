#include "../../include/mem.h"

// try to find the chunk in the heap tiny or small
static t_chunk	*find_in_heap(t_heap *heap, void *ptr)
{
	t_block		*block_tmp;
	t_chunk	*chunk_tmp;

	if (heap == NULL)
		return (NULL);
	block_tmp = heap->start;
	while (block_tmp)
	{
		chunk_tmp = block_tmp->chunk;
		while (chunk_tmp)
		{
			if (chunk_tmp->start == ptr)
				return (chunk_tmp);
			chunk_tmp = chunk_tmp->next;
		}
		block_tmp = block_tmp->next;
	}
	return (NULL);
}

// try to find the chunk in the heap large
static t_large_heap	*find_in_large_heap(void *ptr)
{
	t_large_heap	*large_heap_tmp;
	
	large_heap_tmp = data->large_heap;
	while (large_heap_tmp)
	{
		if (large_heap_tmp->start == ptr)
			return (large_heap_tmp);
		large_heap_tmp = large_heap_tmp->next;
	}
	return (NULL);
}

// find the chunk in the heap tiny, small or large
void	find_chunk_ptr(t_chunk **chunk_tmp, t_large_heap **large_heap_tmp ,void *ptr, size_t *type)
{

	*chunk_tmp = find_in_heap(data->tiny_heap, ptr);
	if (*chunk_tmp)
	{
		*type = TINY_SIZE;
		return ;
	}
	*chunk_tmp = find_in_heap(data->small_heap, ptr);
	if (*chunk_tmp)
	{
		*type = SMALL_SIZE;
		return ;
	}
	*large_heap_tmp = find_in_large_heap(ptr);
	if (*large_heap_tmp)
	{
		*type = LARGE;
		return ;
	}
	else
		*type = 0;
}
