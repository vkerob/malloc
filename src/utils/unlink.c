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
		block->parent_heap->start_block = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
}

void	unlink_used_user_space(t_user_space *used_user_space)
{
	if (used_user_space->prev != NULL)
		used_user_space->prev->next = used_user_space->next;
	else
		used_user_space->parent_block->used_user_space = used_user_space->next;
	if (used_user_space->next != NULL)
		used_user_space->next->prev = used_user_space->prev;
}