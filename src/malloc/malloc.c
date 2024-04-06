#include "../../include/mem.h"

t_data	*data = NULL;

void	*malloc(size_t size)
{
	size_t			page_size = getpagesize();

	if (data == NULL)
		initialize_data(&data);

	if (data == NULL)
		return NULL;

	if (size <= page_size * SMALL)
	{
		if (size <= page_size * TINY)
			allocate_or_found_space_not_found(&(data->tiny_heap), size, TINY);
		else
			allocate_or_found_space_not_found(&(data->small_heap), size, SMALL);
	}
	else
		allocate_large(size);

	if (data->error == false)
		return (data->user_space_pointer);

	free_all();
	return (NULL);
}
