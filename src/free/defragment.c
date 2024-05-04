#include "../../include/mem.h"

void defragment(t_user_space *used_user_space)
{
	size_t			size;

	size = (size_t)align_address(used_user_space->start_user_space + used_user_space->size_allocated) - (size_t)used_user_space->start_user_space;
	used_user_space->parent_block->free_size += ALLIGN_USER_SPACE + size;

	if (used_user_space == used_user_space->parent_block->used_user_space)
		used_user_space->parent_block->size_after += ALLIGN_USER_SPACE + size;
	else if (used_user_space->prev != NULL)
		used_user_space->prev->size_after += ALLIGN_USER_SPACE + size;
}
