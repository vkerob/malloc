#include "../../include/mem.h"

void defragment(t_user_space *used_user_space)
{
	size_t			size;

	// size is equal 
	size = (size_t)align_address(used_user_space->start_user_space + used_user_space->size_allocated) - (size_t)used_user_space->start_user_space;
	used_user_space->parent_block->free_size += ALLIGN_USER_SPACE + size;

	// if it's the first user_space in the block we add the size after the start of the block
	if (used_user_space == used_user_space->parent_block->used_user_space)
		used_user_space->parent_block->size_after += ALLIGN_USER_SPACE + size + used_user_space->size_after;
	// else we add the size after the previous user_space
	else
		used_user_space->prev->size_after += ALLIGN_USER_SPACE + size + used_user_space->size_after;
}
