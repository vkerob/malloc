#include "../../include/mem.h"

static void	set_new_used_user_space(void *space, size_t size, size_t size_to_add_to_align_address, int is_block)
{
	t_user_space	*new_used_user_space, *before_new_used_user_space;
	t_block *block;

	if (is_block) 
	{
		block = (t_block *)space;
		new_used_user_space = (void *)block + ALLIGN_BLOCK;
		new_used_user_space->parent_block = block;
		block->free_size -= size + ALLIGN_USER_SPACE + size_to_add_to_align_address;
		new_used_user_space->size_after = block->size_after - size - size_to_add_to_align_address - ALLIGN_USER_SPACE;
		block->size_after = 0;

		new_used_user_space->next =  block->used_user_space;
		new_used_user_space->prev = NULL;
		
		if (block->used_user_space)
			block->used_user_space->prev = new_used_user_space;
		block->used_user_space = new_used_user_space;
	} 
	else 
	{
		before_new_used_user_space = (t_user_space *)space;
		new_used_user_space = before_new_used_user_space->start_user_space + (size_t)align_address((void *)before_new_used_user_space + before_new_used_user_space->size_allocated) - (size_t)before_new_used_user_space;
		new_used_user_space->parent_block = before_new_used_user_space->parent_block;
		before_new_used_user_space->parent_block->free_size -= size + ALLIGN_USER_SPACE + size_to_add_to_align_address; // if size = 4 size_to_add_to_align_address = 12 with a 16 bytes alignement
		new_used_user_space->size_after = before_new_used_user_space->size_after - size - size_to_add_to_align_address - ALLIGN_USER_SPACE;
		before_new_used_user_space->size_after = 0;
		new_used_user_space->start_user_space = (void*)new_used_user_space + ALLIGN_USER_SPACE;

		link_used_user_space(new_used_user_space, before_new_used_user_space);
	}

	new_used_user_space->start_user_space = (void*)new_used_user_space + ALLIGN_USER_SPACE;
	new_used_user_space->size_allocated = size;

	data->user_space_pointer = new_used_user_space->start_user_space;
}

bool	search_free_space(t_heap *heap, size_t size)
{
	t_block			*block;
	t_user_space	*before_new_used_user_space;
	size_t			size_to_add_to_align_address;


	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{

		// if in the block there is enough space to allocate the size
		if (block->free_size >= size)
		{
			// if after the block there is enough space to allocate the size
			size_to_add_to_align_address = (size_t)align_address((void *)block + ALLIGN_BLOCK + size) - (size_t)block - ALLIGN_BLOCK - size;
			if (block->size_after >= size + size_to_add_to_align_address + ALLIGN_USER_SPACE)
			{
				set_new_used_user_space(block, size, size_to_add_to_align_address, 1); // block->used_user_space = new_used_user_space
				return (true);
			}

			// if after a used_user_space there is enough space to allocate the size
			before_new_used_user_space = block->used_user_space;
			while (before_new_used_user_space)
			{
				size_to_add_to_align_address = (size_t)align_address((void *)before_new_used_user_space->start_user_space + ALLIGN_USER_SPACE + size) - (size_t)before_new_used_user_space->start_user_space - ALLIGN_USER_SPACE - size;
				if (before_new_used_user_space->size_after >= size + size_to_add_to_align_address + ALLIGN_USER_SPACE)
				{
					set_new_used_user_space(before_new_used_user_space, size, size_to_add_to_align_address, 0);
					return (true);
				}
				before_new_used_user_space = before_new_used_user_space->next;
			}
		}
		block = block->next;
	}
	return (false);
}
