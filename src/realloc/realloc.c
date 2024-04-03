#include "../../include/mem.h"


void	*realloc(void *ptr, size_t size)
{
	size_t		page_size = getpagesize();

	if (size <= page_size * TINY)
	{
		// find the area or allocate a new one
		find_new_area_or_allocate(data->tiny, size, TINY);			// find the area or allocate a new one
		// copy the old data to the new area and free the old area
		find_old_area_copy_and_free(ptr, size);
	}
	else if (size <= page_size * SMALL)
	{
		find_new_area_or_allocate(data->small, size, SMALL);
		find_old_area_copy_and_free(ptr, size);
	}
	else
	{
		allocate_large(size);
		find_old_area_copy_and_free(ptr, size);
	}
	if (data->error)
		return (NULL);
	return (data->return_user_space);
}