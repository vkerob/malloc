#include "../../include/mem.h"

t_data	*data = NULL;

void	*malloc(size_t size)
{
	size_t			pagesize = getpagesize();
	int				size_block = sizeof(t_mem_block);
	bool			space_found = false;

	if (data == NULL)
		initialize_data(&data);
	if (size <= pagesize * SMALL - size_block)
	{
		if (size <= pagesize * TINY - size_block)
		{
			space_found = find_free_space(data->tiny, size);
			if (space_found == false)
				allocate(&(data->tiny), size, TINY);
		}
		else
		{
			space_found = find_free_space(data->small, size);
			if (space_found == false)
				allocate(&(data->small), size, SMALL);
		}
	}
	else
		allocate_large(size);
	if (data->error)
		return (NULL);
	return (data->return_user_space);
}