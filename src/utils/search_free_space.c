#include "../../include/mem.h"

static void	set_new_used_user_space(t_user_space *before_new_used_user_space, size_t size, size_t size_to_add_to_align_address)
{
	t_user_space	*new_used_user_space;

	// allocate and set used_user_space
	new_used_user_space = before_new_used_user_space->start_user_space;
	new_used_user_space->start_user_space = (void*)new_used_user_space + ALLIGN_USER_SPACE;
	new_used_user_space->size_allocated = size;
	new_used_user_space->parent_block = before_new_used_user_space->parent_block;
	new_used_user_space->size_after = before_new_used_user_space->size_after - size - size_to_add_to_align_address - ALLIGN_USER_SPACE;
	new_used_user_space->next = new_used_user_space;
	new_used_user_space->prev = new_used_user_space;

	data->user_space_pointer = new_used_user_space->start_user_space;
	// link used_user_space
	link_used_user_space(new_used_user_space, before_new_used_user_space);
	if (data->error)
		return ;
	// reduce unused user space
	before_new_used_user_space->parent_block->free_size -= size + ALLIGN_USER_SPACE + size_to_add_to_align_address; // if size = 4 size_to_add_to_align_address = 12 with a 16 bytes alignement
	before_new_used_user_space->size_after = 0;
}

// search for a unused user space
bool	search_free_space(t_heap *heap, size_t size)
{
	t_block			*block;
	size_t			size_to_add_to_align_address;
	t_user_space	*before_new_used_user_space;


	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{
		if (block->free_size >= size)
		{
			size_to_add_to_align_address = (size_t)align_address((void *)block + ALLIGN_BLOCK + size) - (size_t)block - ALLIGN_BLOCK - size;
			if (block->size_after >= size + size_to_add_to_align_address + ALLIGN_USER_SPACE)
			{
				set_new_used_user_space(block->used_user_space, size, 0);
				return (true);
			}
			before_new_used_user_space = block->used_user_space;
			while (before_new_used_user_space)
			{
				size_to_add_to_align_address = (size_t)align_address((void *)before_new_used_user_space->start_user_space + ALLIGN_USER_SPACE + size) - (size_t)before_new_used_user_space->start_user_space - ALLIGN_USER_SPACE - size; // 
				if (before_new_used_user_space->size_after >= size + size_to_add_to_align_address + ALLIGN_USER_SPACE)
				{
					set_new_used_user_space(before_new_used_user_space, size, size_to_add_to_align_address);
					return (true);
				}
				before_new_used_user_space = before_new_used_user_space->next;
			}
		}
		block = block->next;
	}
	return (false);
}