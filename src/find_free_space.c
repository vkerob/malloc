#include "../include/mem.h"

static void set_user_space(t_mem_block *block, size_t size)
{
	t_user_space	*user_space;
	t_user_space	*user_space_prev = NULL;

	// find last user_space
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
	user_space->start_user_space = block->free_area->start_free_space;
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

static void	reduce_free_area_and_set_user_space(t_free_space *free_area, t_mem_block *block, size_t size)
{
	// delete free area if no space left
	if (free_area->free_size - size == 0)
	{
		free_area->prev->next = free_area->next;
		free_area->next->prev = free_area->prev;
		munmap(free_area, sizeof(t_free_space));
	}
	else
	{
		// set user space
		set_user_space(block, size);
		if (data->error)
			return ;
		// reduce free area
		free_area->free_size -= size;
		free_area->start_free_space += size;

	}
}

bool	find_free_space(t_heap *heap, size_t size)
{
	t_mem_block		*block;
	t_free_space	*free_area;

	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{
		free_area = block->free_area;
		while (free_area)
		{
			if (free_area->free_size >= size)
			{
				reduce_free_area_and_set_user_space(free_area, block, size);
				return (true);
			}
			free_area = free_area->next;
		}
		block = block->next;
	}
	return (false);
}