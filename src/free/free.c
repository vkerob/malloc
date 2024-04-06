#include "../../include/mem.h"

void	free(void *ptr)
{
	t_data *data2 = data;
	(void)data2;
	t_user_space	*user_space_tmp;
	t_heap_large	*heap_large_tmp;
	size_t			page_size = getpagesize();
	size_t			type;

	find_ptr(&user_space_tmp, &heap_large_tmp, ptr, &type);
	if (type == TINY)
	{
		delink_user_space(user_space_tmp);
		add_free_area_and_defragment(data->tiny_heap, user_space_tmp);
		if (data->error == true)
		{
			free_all();
			return ;
		}
		delete_user_space_or_block(data->tiny_heap, user_space_tmp, type, page_size);
	}
	else if (type == SMALL)
	{
		delink_user_space(user_space_tmp);
		add_free_area_and_defragment(data->small_heap, user_space_tmp);
		if (data->error == true)
		{
			free_all();
			return ;
		}
		delete_user_space_or_block(data->small_heap, user_space_tmp, type, page_size);
	}
	else
	{
		delink_heap_large(heap_large_tmp);
		delete_heap_large(heap_large_tmp, page_size);
	}
	if (data->tiny_heap == NULL && data->small_heap == NULL && data->large_heap == NULL)
	{
		munmap(data, sizeof(t_data));
		data = NULL;
	}
}