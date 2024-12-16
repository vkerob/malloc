#include "../../includes/malloc.h"

void	free_heap(t_heap *heap)
{
	t_block	*block;
	t_block	*tmp;

	block = heap->start;

	while (block)
	{
		tmp = block->next;
		free(block);
		block = tmp;
	}

	free(heap);
}

void	free_large_heap(t_large_heap *heap)
{
	t_large_heap	*tmp;

	while (heap)
	{
		tmp = heap->next;
		free(heap->start);
		free(heap);
		heap = tmp;
	}
}

void	free_all(void)
{
	if (data->tiny_heap)
		free_heap(data->tiny_heap);

	if (data->small_heap)
		free_heap(data->small_heap);

	if (data->large_heap)
		free_large_heap(data->large_heap);

	if (data)
	{
		free(data);
		data = NULL;
	}
}
