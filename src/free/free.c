#include "../../include/mem.h"

void	free(void *ptr)
{
	t_user_space	*used_user_space;
	t_large_heap	*used_large_heap;
	t_heap			**heap_tmp; 		// we change the pointer of used_user_space so we need a tmp
	t_block			*block_tmp;			// same as above
	size_t			type = 0;

	pthread_mutex_lock(&lock);
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&lock);
		return ;
	}
	data->user_space_pointer = NULL;
	find_used_user_space_ptr(&used_user_space, &used_large_heap, ptr, &type);
	if (type == TINY_SIZE || type == SMALL_SIZE)
	{
		heap_tmp = (type == TINY_SIZE) ? &(data->tiny_heap) : &(data->small_heap);
		unlink_used_user_space(used_user_space);
		block_tmp = used_user_space->parent_block;
		link_new_unused_user_space_and_defragment(used_user_space);
		check_if_block_is_unused(heap_tmp, block_tmp);
	}
	else if (type == LARGE)
	{
		unlink_large_heap(used_large_heap);
		delete_large_heap(used_large_heap);
	}
	else
	{
		write(1, "Error: double free\n", 20);
		pthread_mutex_unlock(&lock);
		return ;
	}
	if (data->tiny_heap == NULL && data->small_heap == NULL && data->large_heap == NULL)
	{
		munmap(data, sizeof(t_data));
		data = NULL;
		pthread_mutex_unlock(&lock);
		pthread_mutex_destroy(&lock);
	}
	else
		pthread_mutex_unlock(&lock);
}

