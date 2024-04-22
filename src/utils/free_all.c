#include "../../include/mem.h"

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
		free_user_space(block->used_user_space);
		free_user_space(block->unused_user_space);
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
		free_large_heap(data->large_heap);
	free(data);
}