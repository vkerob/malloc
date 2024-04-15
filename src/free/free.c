#include "../../include/mem.h"

void	free(void *ptr)
{
	t_data *data2 = data;
	(void)data2;
	t_user_space	*user_space_target;
	t_large_heap	*large_heap_target;
	t_heap			*heap_tmp;
	size_t			type;

	find_ptr(&user_space_target, &large_heap_target, ptr, &type);
	if (type == TINY || type == SMALL)
	{
		heap_tmp = (type == TINY) ? data->tiny_heap : data->small_heap;
		unlink_user_space(user_space_target);
		add_free_area_and_defragment(user_space_target);
		if (data->error == true)
		{
			free_all();
			return ;
		}
		delete_user_space_or_block(&heap_tmp, user_space_target);
	}
	else
	{
		unlink_large_heap(large_heap_target);
		delete_large_heap(large_heap_target);
	}
	if (data->tiny_heap == NULL && data->small_heap == NULL && data->large_heap == NULL)
	{
		munmap(data, sizeof(t_data));
		data = NULL;
	}
}