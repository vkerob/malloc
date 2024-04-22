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
	used_user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (used_user_space == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	used_user_space->start_user_space = unused_user_space->start_user_space;
	used_user_space->size_allocated = size;
	used_user_space->parent_block = unused_user_space->parent_block;

	data->user_space_pointer = used_user_space->start_user_space;
	// link used_user_space
	link_used_user_space(used_user_space, used_user_space_prev);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------//

static void	set_used_user_space_and_reduce_free_area(t_user_space *unused_user_space, size_t size)
{

	// set used user space
	set_used_user_space(unused_user_space, size);
	if (data->error)
		return ;

	// reduce unused user space
	unused_user_space->start_user_space += size;
	unused_user_space->size_allocated -= size;
	if (unused_user_space->size_allocated == 0)
	{
		unlink_unused_user_space(unused_user_space);
		munmap(unused_user_space, sizeof(t_user_space));
		unused_user_space = NULL;
	}
}

// search for a unused user space
bool	search_free_space(t_heap *heap, size_t size)
{
	t_block			*block;
	t_user_space	*unused_user_space;

	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{
		unused_user_space = block->unused_user_space;
		while (unused_user_space)
		{
			if (unused_user_space->size_allocated >= size)
			{
				set_used_user_space_and_reduce_free_area(unused_user_space, size);
				return (true);
			}
			unused_user_space = unused_user_space->next;
		}
		block = block->next;
	}
	return (false);
}