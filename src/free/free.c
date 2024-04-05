#include "../../include/mem.h"

void	free(void *ptr)
{
	t_user_space	*user_space_tmp;
	t_heap_large	*heap_large_tmp;
	size_t			page_size = getpagesize();
	size_t			type;

	find_ptr(&user_space_tmp, &heap_large_tmp, ptr, &type);
	if (user_space_tmp)
	{
		delink_user_space(user_space_tmp);
		add_free_area_and_defragment(user_space_tmp);
		if (data->error)
		{
			free_all();
			return ;
		}
		delete_user_space_or_block(user_space_tmp, type, page_size);
	}
	else
	{
		delink_heap_large(heap_large_tmp);
		delete_heap_large(heap_large_tmp, page_size);
	}
}