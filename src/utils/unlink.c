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

void	unlink_free_area(t_free_area *free_area)
{
	if (free_area->prev != NULL)
		free_area->prev->next = free_area->next;
	else
		free_area->parent_heap->free_area = free_area->next;
	if (free_area->next != NULL)
		free_area->next->prev = free_area->prev;
}

void	unlink_block(t_block *block)
{
	if (block->prev != NULL)
		block->prev->next = block->next;
	else
		block->parent_heap->start_block = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
}

void	unlink_user_space(t_user_space *user_space)
{
	if (user_space->prev != NULL)
		user_space->prev->next = user_space->next;
	else
		user_space->parent_block->user_space = user_space->next;
	if (user_space->next != NULL)
		user_space->next->prev = user_space->prev;
}
