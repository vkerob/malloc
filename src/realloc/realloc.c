#include "../../include/mem.h"


void	*realloc(void *ptr, size_t size)
{
	if (size <= data->page_size * SMALL)
	{
		if (size <= data->page_size * TINY)
		{
			// find the area or allocate a new one
			find_new_area_or_allocate(data->tiny_heap, size, TINY);
			if (data->error == false)
				// copy the old data to the new area and free the old area
				find_old_area_copy_and_free(ptr, size);
		}
		else
		{
			find_new_area_or_allocate(data->small_heap, size, SMALL);
			if (data->error == false)
				find_old_area_copy_and_free(ptr, size);
		}
	}
	else
	{
		allocate_large(size);
		if (data->error == false)
			find_old_area_copy_and_free(ptr, size);
	}
	if (data->error == false)
		return (data->user_space_pointer);
	// error detected, free all allocated memory
	free_all();
	return (NULL);
}