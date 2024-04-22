#include "../../include/mem.h"


void	*realloc(void *ptr, size_t size)
{
	t_heap	**heap_tmp;
	int		type;

	if (size <= data->page_size * SMALL || size <= data->page_size * TINY)
	{
		heap_tmp = ((size <= data->page_size * SMALL) == (TINY * data->page_size)) ? &(data->tiny_heap) : &(data->small_heap);
		type = ((size <= data->page_size * SMALL) == (TINY * data->page_size)) ? TINY : SMALL;
		// find the area or allocate a new one
		find_new_area_or_allocate(heap_tmp, size, type);
		if (data->error == false)
			// copy the old data to the new area and free the old area
			find_old_area_copy_and_free(ptr, size);
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