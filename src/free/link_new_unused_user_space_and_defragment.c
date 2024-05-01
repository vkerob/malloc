#include "../../include/mem.h"

void link_new_unused_user_space_and_defragment(t_user_space *used_user_space)
{
	size_t			size;

	size = (size_t)align_address(used_user_space->start_user_space + used_user_space->size_allocated) - (size_t)used_user_space->start_user_space;
	used_user_space->parent_block->free_size += ALLIGN_USER_SPACE + size;
	if (used_user_space == used_user_space->parent_block->used_user_space)
		used_user_space->parent_block->size_after += ALLIGN_USER_SPACE + size;
}
