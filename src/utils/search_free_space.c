#include "../../include/mem.h"


// find the parent block of the user_space with the pointer ptr because the user_space is not directly linked to the heap
t_block	*find_parent_block(t_heap *heap, void *ptr)
{
	t_block	*block;

	block = heap->start_block;
	while (block)
	{
		// check if the pointer is between the start and the end of the user_space
		if (ptr >= block->user_space->start_user_space && ptr < block->user_space->start_user_space + heap->size)
			return (block);
		block = block->next;
	}
	return (NULL);
}


static void set_user_space(t_heap *heap, t_free_space *free_area, size_t size)
{
	t_user_space	*user_space = NULL;
	t_user_space	*user_space_prev = NULL;

	// find last user_space
	t_block	*block = find_parent_block(heap, free_area->start_free_space);
	if (block != NULL)
		user_space = block->user_space;
	while (user_space)
	{
		if (user_space->next == NULL)
			user_space_prev = user_space;
		user_space = user_space->next;
	}

	// allocate and set user_space
	user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (user_space == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	user_space->start_user_space = free_area->start_free_space;
	data->user_space_pointer = user_space->start_user_space;
	user_space->size_allocated = size;
	user_space->parent_block = block;

	// link user_space
	user_space->next = NULL;
	user_space->prev = user_space_prev;
	if (user_space_prev)
		user_space_prev->next = user_space;
	else
		block->user_space = user_space;
}

static void	reduce_free_area_and_set_user_space(t_heap *heap, t_free_space *free_area, size_t size)
{

	// set user space
	set_user_space(heap, free_area, size);
	if (data->error)
		return ;
	// reduce free area
	free_area->free_size -= size;
	free_area->start_free_space += size;
}

bool	search_free_space(t_heap *heap, size_t size)
{
	t_free_space	*free_area;

	if (heap == NULL)
		return (NULL);
	free_area = heap->free_area;
	while (free_area)
	{
		if (free_area->free_size >= size)
		{
			reduce_free_area_and_set_user_space(heap, free_area, size);
			return (true);
		}
		free_area = free_area->next;
	}
	return (false);
}