#include "../../include/mem.h"
#include <unistd.h>

t_data	*data = NULL;

void	*malloc(size_t size)
{
	size_t			pagesize = getpagesize();
	int				size_block = sizeof(t_mem_block);
	void			*start_user_space_tmp;

	if (data == NULL)
		initialize_data(&data);
	if (size <= pagesize * SMALL - size_block)
	{
		if (size <= pagesize * TINY - size_block)
		{
			start_user_space_tmp = find_free_space(data->tiny, size);
			if (start_user_space_tmp == NULL)
				allocate(data, &(data->tiny), size, TINY);
		}
		else
		{
			start_user_space_tmp = find_free_space(data->small, size);
			if (start_user_space_tmp == NULL)
				allocate(data, &(data->small), size, SMALL);
		}
		if (start_user_space_tmp != NULL)
			return (start_user_space_tmp);
	}
	else
		allocate_large(data, size);
	if (data->error)
		return (NULL);
	return (data->start_user_space);
}