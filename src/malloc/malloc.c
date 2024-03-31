#include "../../include/mem.h"
#include <unistd.h>

void	*malloc(size_t size)
{
	write(1, "malloc\n", 7);
	size_t			pagesize = getpagesize();
	int				size_block = sizeof(t_mem_block);
	void			*start_user_space_tmp;
	static t_data	*data = NULL;
	t_heap			*heap;

	if (data == NULL)
		initialize_data(&data);
	if (size <= pagesize * SMALL - size_block)
	{
		if (size <= pagesize * TINY - size_block)
		{
			start_user_space_tmp = find_free_space(data->tiny, size);
			heap = data->tiny;
		}
		else
		{
			start_user_space_tmp = find_free_space(data->small, size);
			heap = data->small;
		}
		if (start_user_space_tmp == NULL)
			allocate(data, heap, size, TINY);
		else
			return (start_user_space_tmp);
	}
	else
		allocate_large(data, size);
	if (data->error)
		return (NULL);
	return (data->start_user_space);
}