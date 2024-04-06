#include "../../include/mem.h"

void	free_free_area(t_free_space *free_area)
{
	t_free_space	*tmp;

	while (free_area)
	{
		tmp = free_area->next;
		free(free_area);
		free_area = tmp;
	}
}

void	free_user_space(t_user_space *user_space)
{
	t_user_space	*tmp;

	while (user_space)
	{
		tmp = user_space->next;
		free(user_space);
		user_space = tmp;
	}
}

void	free_heap(t_heap *heap)
{
	t_block	*block;
	t_block	*tmp;

	block = heap->start_block;
	while (block)
	{
		tmp = block->next;
		free_user_space(block->user_space);
		free(block);
		block = tmp;
	}
	free_free_area(heap->free_area);
	free(heap);
}

void	free_heap_large(t_heap_large *heap)
{
	t_heap_large	*tmp;

	while (heap)
	{
		tmp = heap->next;
		free(heap->start_user_space);
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
		free_heap_large(data->large_heap);
	free(data);
}