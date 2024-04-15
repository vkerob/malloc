#include "../../include/mem.h"

//------------------------------------------------------------------set_user_space------------------------------------------------------------------//

// find the parent block of a pointer for set parent_block in user_space and set user_space in block
static t_block	*find_new_user_space_parent_block(t_heap *heap, void *ptr)
{
	t_block	*block;

	block = heap->start_block;
	while (block)
	{
		// check if the pointer is between the start and the end of the user space block
		if (ptr >= (void *)block->user_space + sizeof(t_user_space) && ptr < (void *)block->user_space + heap->size)
			return (block);
		block = block->next;
	}
	return (NULL);
}

static void set_user_space(t_free_area *free_area, size_t size)
{
	t_user_space	*user_space = NULL;
	t_user_space	*user_space_prev = NULL;

	// send the new user_space to the parent block (free_area->start_free_area is the start of the user_space)
	t_block	*block = find_new_user_space_parent_block(free_area->parent_heap, free_area->start_free_area);
	if (block != NULL)
		user_space = block->user_space;

	// find last user_space
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
	user_space->start_user_space = free_area->start_free_area;
	user_space->ptr_defragment = free_area->start_free_area;
	data->user_space_pointer = user_space->start_user_space;
	user_space->size_allocated = size;
	user_space->parent_block = block;

	// link user_space
	link_user_space(user_space, user_space_prev);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------//

static void	set_user_space_and_reduce_free_area(t_free_area *free_area, size_t size)
{

	// set user space
	set_user_space(free_area, size);
	if (data->error)
		return ;

	// reduce free area
	free_area->free_size -= size;
	if (free_area->free_size != 0)
		free_area->start_free_area += size;
	else
		free_area->start_free_area = NULL;

}

// search for a free space in the heap free_area
bool	search_free_space(t_heap *heap, size_t size)
{
	t_free_area	*free_area;

	if (heap == NULL)
		return (NULL);
	free_area = heap->free_area;
	while (free_area)
	{
		if (free_area->free_size >= size)
		{
			set_user_space_and_reduce_free_area(free_area, size);
			return (true);
		}
		free_area = free_area->next;
	}
	return (false);
}