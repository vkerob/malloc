#include "../../include/mem.h"

void	free(void *ptr)
{
	t_user_space	*user_space_used;
	t_large_heap	*large_heap_used;
	t_heap			**heap_tmp; 		// we change the pointer of used_user_space so we need a tmp
	t_block			*block_tmp;			// same as above
	size_t			type = 0;

	find_used_user_space_ptr(&user_space_used, &large_heap_used, ptr, &type);
	if (type == TINY || type == SMALL)
	{
		heap_tmp = (type == TINY) ? &(data->tiny_heap) : &(data->small_heap);
		unlink_used_user_space(user_space_used);
		block_tmp = user_space_used->parent_block;
		link_new_unused_user_space_and_defragment(user_space_used);
		check_if_block_is_unused(heap_tmp, block_tmp);
	}
	else if (type == LARGE)
	{
		unlink_large_heap(large_heap_used);
		delete_large_heap(large_heap_used);
	}
	else
	{
		write(1, "Error: double free\n", 20);
		return ;
	}
	if (data->tiny_heap == NULL && data->small_heap == NULL && data->large_heap == NULL)
	{
		munmap(data, sizeof(t_data));
		data = NULL;
	}
}