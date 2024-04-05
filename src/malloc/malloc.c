#include "../../include/mem.h"

t_data	*data = NULL;

void	*malloc(size_t size)
{
	size_t			pagesize = getpagesize();
	int				size_block = sizeof(t_mem_block);
	bool			space_found = false;

	if (data == NULL)
		initialize_data(&data);
	if (size <= pagesize * SMALL && data != NULL)
	{
		if (size <= pagesize * TINY)
		{
			space_found = find_free_space(data->tiny, size);
			if (space_found == false && data->error == false)
				allocate(&(data->tiny), size, TINY);
		}
		else
		{
			space_found = find_free_space(data->small, size);
			if (space_found == false && data->error == false)
				allocate(&(data->small), size, SMALL);
		}
	}
	else if (data != NULL)
		allocate_large(size);
	if (data->error == false)
		return (data->return_user_space);
	free_all();
	return (NULL);
}