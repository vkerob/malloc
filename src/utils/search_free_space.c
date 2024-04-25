#include "../../include/mem.h"

//------------------------------------------------------------------set_user_space------------------------------------------------------------------//

static void set_used_user_space(t_user_space *unused_user_space, size_t size)
{
	t_user_space	*used_user_space = unused_user_space->parent_block->used_user_space;
	t_user_space	*used_user_space_prev = NULL;

	// find last used_user_space
	while (used_user_space)
	{
		if (used_user_space->next == NULL)
			used_user_space_prev = used_user_space;
		used_user_space = used_user_space->next;
	}

	// allocate and set used_user_space
	used_user_space = align_address((t_user_space *)((void *)unused_user_space->start_user_space));
	used_user_space->start_user_space = used_user_space + sizeof(t_user_space);
	used_user_space->size_allocated = size;
	used_user_space->parent_block = unused_user_space->parent_block;

	data->user_space_pointer = used_user_space->start_user_space;
	// link used_user_space
	link_used_user_space(used_user_space, used_user_space_prev);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------//

static void	set_used_user_space_and_reduce_unused_user_space(t_user_space *unused_user_space, size_t size, size_t size_to_add)
{
	// set used user space
	set_used_user_space(unused_user_space, size);
	if (data->error)
		return ;
	// reduce unused user space
	unused_user_space->start_user_space += size + sizeof(t_user_space) + size_to_add;
	unused_user_space->size_allocated -= size + sizeof(t_user_space) + size_to_add;
	if (unused_user_space->size_allocated == 0)
	{
		unlink_unused_user_space(unused_user_space);
		unused_user_space = NULL;
	}
}

bool	check_if_align(size_t size)
{
	if (size % 16 == 0)
		return (true);
	return (false);
}

// search for a unused user space
bool	search_free_space(t_heap *heap, size_t size)
{
	t_block			*block;
	size_t			size_to_add;
	t_user_space	*unused_user_space;

	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{
		unused_user_space = block->unused_user_space;
		while (unused_user_space)
		{
			size_to_add = (size_t)align_address((void *)unused_user_space->start_user_space + sizeof(t_user_space) + size) - (size_t)unused_user_space->start_user_space - sizeof(t_user_space) - size; // 
			if (unused_user_space->size_allocated - size_to_add >= size) // size_allocated = remaining space
			{
				set_used_user_space_and_reduce_unused_user_space(unused_user_space, size, size_to_add);
				return (true);
			}
			unused_user_space = unused_user_space->next;
		}
		block = block->next;
	}
	return (false);
}