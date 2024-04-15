#include "../../include/mem.h"

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

void	link_user_space(t_user_space *user_space, t_user_space *user_space_prev)
{
	user_space->next = NULL;
	user_space->prev = user_space_prev;
	if (user_space_prev)
		user_space_prev->next = user_space;
	else
		user_space->parent_block->user_space = user_space;
}
